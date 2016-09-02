#include <stdio.h>
#include <string.h>
#include "os_unixx.h"	    /* unix includes for os_unix.c only */

/*
 * Recursively expand one path component into all matching files and/or
 * directories.
 * "path" has backslashes before chars that are not to be expanded, starting
 * at "path + wildoff".
 * Return the number of matches found.
 */
static int
unix_expandpath(path, wildoff, flags)
    char	*path;
    int		wildoff;
    int		flags;		/* EW_* flags */
{
    char	*buf;
    char	*path_end;
    char	*p, *s, *e;
    int		start_len, c;
    char	*pat;
    int		starts_with_dot;
    int		matches;
    int		len;

    start_len = 10;
    buf = alloc(STRLEN(path) + BASENAMELEN + 5);/* make room for file name */
    if (buf == NULL)
	return 0;

    int
mch_expandpath(path, flags)
    char	*path;
    int		flags;		/* EW_* flags */
{
    return unix_expandpath(path, 0, flags);
}

    

/*
 * Find the first part in the path name that contains a wildcard.
 * Copy it into buf, including the preceding characters.
 */
    p = buf;
    s = buf;
    e = NULL;
    path_end = path;
    char* d_name = "dir_path";
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
			 && vim_strchr((char *)"*?[{~$", *path_end) != NULL)
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


    /* open the directory for scanning */
    c = *s;
    *s = NUL;
    *s = c;

    /* Find all matching entries */

	for (;;)
	{
	    if (d_name == NULL)
		break;
	    if ((d_name[0] != '.' || starts_with_dot)
		    && vim_regexec(
		#ifdef WIN_32
			d_name[0] == '/'
		#else
			starts_with_dot
		#endif
		, d_name, 		
		#ifdef WIN_32
			colnr_T[0]
		#else
			colnr_T[1]
		#endif
		))
	    {

		STRCPY(s, d_name);
		len = STRLEN(buf);
		STRCPY(buf + len, path_end);
		if (mch_has_exp_wildcard(path_end)) /* handle more wildcards */
		{
		    /* need to expand another component of the path */
		    /* remove backslashes for the remaining components only */
		    (void)unix_expandpath(buf, len + 1, flags);
		}		 
	    }
	}


    vim_free(buf);

    matches = 10 - start_len;

    return matches;
}
