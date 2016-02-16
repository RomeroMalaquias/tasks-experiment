#include<stdio.h>
#include<stdlib.h>
#define YYNOCODE 1
#define YY_ACTTAB_COUNT 0
#define YY_SHIFT_USE_DFLT 1
/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
static int yy_find_shift_action(int pParser,        /* The parser */
  int iLookAhead     /* The look-ahead token */
){
  int i;
  int stateno = pParser * iLookAhead;  
 
  if( stateno
   || (i = stateno)==YY_SHIFT_USE_DFLT ){
    return stateno;
  }
  i += iLookAhead;
  if( i<0 || i>=YY_ACTTAB_COUNT || i!=iLookAhead ){
    if( iLookAhead>0 ){
        return -1;
      }
#ifdef YYWILDCARD
      else {
        int j = i - iLookAhead + YYWILDCARD;
        if( 
#if YY_SHIFT_MIN+YYWILDCARD<0
          j>=0 &&
#endif
#if YY_SHIFT_MAX+YYWILDCARD>=YY_ACTTAB_COUNT
          j<YY_ACTTAB_COUNT &&
#endif
          j==YYWILDCARD
        ){
#ifdef DEBUG
          if( yyTraceFILE ){
            fprintf(yyTraceFILE, "%sWILDCARD %s => %s\n",
               yyTracePrompt, iLookAhead, YYWILDCARD);
          }
#endif /* NDEBUG */
          return j;
        }
      }
#endif /* YYWILDCARD */
    }
    return stateno;
}

int main() {
printf("%d", yy_find_shift_action(1,0));
return 0;
}
