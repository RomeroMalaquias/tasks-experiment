# Task 2
### Given the following modification to the f function prototype perform the necessary changes to the code.

##Task:
**Adicionar a funcionalidade fnprintf.**

A funcionalidade fnprintf estar� ativa quando a flag HAVE_FNPRINTF for definida (ex: #define HAVE_FNPRINTF).

Ela ter� prioridade sobre as outras fun��es (sprintf, snprintf), ou seja, quando a HAVE_FNPRINTF, as outras fun��es n�o dever�o aparecer no c�digo.

A fun��o fnprintf tem uma assinatura igual a snprintf(buf, sizeof(buf), "PORT %d,%d,%d,%d,%d,%d\r\n",adp[0] & 0xff, adp[1] & 0xff, adp[2] & 0xff, adp[3] & 0xff,portp[0] & 0xff, portp[1] & 0xff), mas no lugar do adp[2] ela recebe fnp[0] e no lugar do portp[0] recebe fnp[1].