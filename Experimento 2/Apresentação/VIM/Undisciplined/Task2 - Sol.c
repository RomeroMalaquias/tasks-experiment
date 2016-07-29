/*
 * Recursively expand one path component into all matching files and/or
 * directories.
 * "path" has backslashes before chars that are not to be expanded, starting
 * at "path + wildoff".
 * Return the number of matches found.
 */
    int
mch_expandpath(gap, path, flags)
    garray_T	*gap;
    char_u	*path;
    int		flags;		/* EW_* flags */
{
    return unix_expandpath(gap, path, 0, flags);
}

    static int
unix_expandpath(gap, path, wildoff, flags)
    garray_T	*gap;
    char_u	*path;
    int		wildoff;
    int		flags;		/* EW_* flags */
{
    char_u	*buf;
    char_u	*path_end;
    char_u	*p, *s, *e;
    int		start_len, c;
    char_u	*pat;
    DIR		*dirp;
    regmatch_T	regmatch;
    struct dirent *dp;
    int		starts_with_dot;
    int		matches;
    int		len;

    start_len = gap->ga_len;
    buf = alloc(STRLEN(path) + BASENAMELEN + 5);/* make room for file name */
    if (buf == NULL)
	return 0;

/*
 * Find the first part in the path name that contains a wildcard.
 * Copy it into buf, including the preceding characters.
 */
    p = buf;
    s = buf;
    e = NULL;
    path_end = path;
    while (*path_end != NUL)
    {
	/* May ignore a wildcard that has a backslash before it; it will
	 * be removed by rem_backslash() or file_pat_to_reg_pat() below. */
	if (path_end >= path + wildoff && rem_backslash(path_end))
	    *p++ = *path_end++;
	else if (*path_end == '/')
	{
	    if (e != NULL)
		break;
	    s = p + 1;
	}
	else if (path_end >= path + wildoff
			 && vim_strchr((char_u *)"*?[{~$", *path_end) != NULL)
	    e = p;
#ifdef FEAT_MBYTE
	if (has_mbyte)
	{
	    len = (*mb_ptr2len_check)(path_end);
	    STRNCPY(p, path_end, len);
	    p += len;
	    path_end += len;
	}
	else
#endif
	    *p++ = *path_end++;
    }
    e = p;
    *e = NUL;

    /* now we have one wildcard component between s and e */
    /* Remove backslashes between "wildoff" and the start of the wildcard
     * component. */
    for (p = buf + wildoff; p < s; ++p)
	if (rem_backslash(p))
	{
	    STRCPY(p, p + 1);
	    --e;
	    --s;
	}

    /* convert the file pattern to a regexp pattern */
    starts_with_dot = (*s == '.');
    pat = file_pat_to_reg_pat(s, e, NULL, FALSE);
    if (pat == NULL)
    {
	vim_free(buf);
	return 0;
    }

    /* compile the regexp into a program */
#ifdef MACOS_X /* Can/Should we use CASE_INSENSITIVE_FILENAME instead ?*/
    regmatch.rm_ic = TRUE;		/* Behave like Terminal.app */
#else
    regmatch.rm_ic = FALSE;		/* Don't ever ignore case */
#endif
    regmatch.regprog = vim_regcomp(pat, RE_MAGIC);
    vim_free(pat);

    if (regmatch.regprog == NULL)
    {
	vim_free(buf);
	return 0;
    }

    /* open the directory for scanning */
    c = *s;
    *s = NUL;
    dirp = opendir(*buf == NUL ? "." : (char *)buf);
    *s = c;

    /* Find all matching entries */
    if (dirp != NULL)
    {
	for (;;)
	{
	    dp = readdir(dirp);
	    if (dp == NULL)
		break;
	//Adição da função
		if ((dp->d_name[0] != '.' || starts_with_dot)
		    && 
		#ifdef WIN_64
			vim_regexec64(
		#else
			vim_regexec(
		#endif
		#ifdef WIN_32
			&regmatch
		#elif defined WIN_64
			&dp-d_name[0]
		#else
			starts_with_dot
		#endif
		, (char_u *)dp->d_name, 		
		#ifdef WIN_32
			(colnr_T)0)
		#else
			(colnr_T)1)
		#endif
		)
	    {
		STRCPY(s, dp->d_name);
		len = STRLEN(buf);
		STRCPY(buf + len, path_end);
		if (mch_has_exp_wildcard(path_end)) /* handle more wildcards */
		{
		    /* need to expand another component of the path */
		    /* remove backslashes for the remaining components only */
		    (void)unix_expandpath(gap, buf, len + 1, flags);
		}
		else
		{
		    /* no more wildcards, check if there is a match */
		    /* remove backslashes for the remaining components only */
		    if (*path_end != NUL)
			backslash_halve(buf + len + 1);
		    if (mch_getperm(buf) >= 0)	/* add existing file */
		    {
#if defined(MACOS_X) && defined(FEAT_MBYTE)
			size_t precomp_len = STRLEN(buf)+1;
			char_u *precomp_buf =
			    mac_precompose_path(buf, precomp_len, &precomp_len);
			if (precomp_buf)
			{
			    mch_memmove(buf, precomp_buf, precomp_len);
			    vim_free(precomp_buf);
			}
#endif
			addfile(gap, buf, flags);
		    }
		}
	    }
	}

	closedir(dirp);
    }

    vim_free(buf);
    vim_free(regmatch.regprog);

    matches = gap->ga_len - start_len;
    if (matches > 0)
	qsort(((char_u **)gap->ga_data) + start_len, matches,
						   sizeof(char_u *), pstrcmp);
    return matches;
}
#endif