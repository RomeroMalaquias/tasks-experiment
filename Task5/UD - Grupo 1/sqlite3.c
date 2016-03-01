#include<stdio.h>
#include<stdlib.h>

/*
** Find the appropriate action for a parser given the terminal
** look-ahead token iLookAhead.
**
** If the look-ahead token is YYNOCODE, then check to see if the action is
** independent of the look-ahead.  If it is, return the action, otherwise
** return YY_NO_ACTION.
*/
int yy_find_shift_action(int pParser, int iLookAhead)
{
	int i;
	int stateno = pParser * iLookAhead;
	i = stateno;
	i += iLookAhead;
#ifdef YYWILDCARD
	int j = i - iLookAhead + 1;
	if( j == 1
#ifdef YYWILDCARD_MIN
		&& i == 0
#endif
#ifdef YY_ACTTAB_COUNT
		&& iLookAhead != pParser
#else
		&& iLookAhead == pParser
#endif
        ){
#ifdef NDEBUG
          if(stateno == pParser){
        	return iLookAhead;
          }
#endif /* NDEBUG */
          return pParser;
        }
#endif /* YYWILDCARD */
    return stateno;
}

int main() {
	if (yy_find_shift_action(0,10) == 0) {
		printf("success");
	} else {
		printf("fail");
	}
	return 0;
}
