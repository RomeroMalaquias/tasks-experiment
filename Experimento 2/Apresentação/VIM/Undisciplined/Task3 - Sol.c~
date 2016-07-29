/**
 * Test memory use
 */

void
memTest() {
	memTestUse(2,
	#ifdef TEST
	 0, 0
	#else 
	2, 1
	#endif
	);

}

/**
 * Test memory use.
 */

int
memTestUse(int mem_index, int lc_jump, int signal) {
    int returnValue = 1 +
	#ifdef FEAT_MZSCHEME
	2
	#ifdef HAVE_SETJMP_H
	/
	#else 
	*
	#endif
	(5 + 
	#ifdef USE_XSMP
	mem_index) * lc_jump
	#else 
	signal * lc_jump)
	#endif
	#else 
		
		#ifdef USE_XSMP		
			#ifdef FEAT_XCLIPBOARD
			 5 * (1 + memCheckCorrupted(2, 3, 3) + mem_index) * lc_jump // deveria ser um + no lugar de - memCheckCorrupted
			#else 
			 5 * (1 - memCheckCorrupted(2, 3, 3) - signal + lc_jump)
			#endif
		#else
		5 * (1 - memCheckCorrupted(2, 2, 7)
			#ifdef FEAT_XCLIPBOARD
			 + mem_index) * lc_jump
			#else 
			 - signal + lc_jump)
			#endif
		#endif
		
	#endif
	;

	return returnValue;

}

/**
 * Check if the memory was corrupted.
 */

int
memCheckCorrupted(int m, int lc_active, int lc_signal) {
    if (lc_signal != 0 && m != 0) {
		return -1;
	} else if (m != 0 && lc_signal > 0) {
		return 1;
	} else {
		return 0;
	}
}
