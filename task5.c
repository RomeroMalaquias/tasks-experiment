#define YYNOCODE 1;
#define YY_ACTTAB_COUNT 1;
#define YYFALLBACK 1;
#define YYWILDCARD 1;
#define YY_SHIFT_MIN 2;
#define YYWILDCARD 3;
#define YY_SHIFT_MAX 10;

int yy_find_shift_action(
  int pParser,        /* The parser */
  int iLookAhead     /* The look-ahead token */
){
  int i = pParser;
  i += iLookAhead;
#ifdef YYWILDCARD
      {
        int j = i - iLookAhead + YYWILDCARD;
        if(
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
		  iLookAhead==YYWILDCARD
        ){
#ifndef NDEBUG
          if( pParser ){
        	  return 1;
          }
#endif /* NDEBUG */
          return pParser;
        }
      }
#endif /* YYWILDCARD */
    }
    return i;
  }else{
    return 0;
  }
}
