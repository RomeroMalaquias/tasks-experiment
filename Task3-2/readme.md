# Task 3
### Given the following modification to the f function prototype perform the necessary changes to the code.

##Task:
**Adicionar a funcionalidade `fnprintf`.**

A funcionalidade fnprintf estará ativa quando a flag `HAVE_FNPRINTF` for definida (ex: `#define HAVE_FNPRINTF`).

Quando ela for definida, as outras funções (sprintf, snprintf) funções não deverão aparecer no código.

A função fnprintf tem uma assinatura igual a `snprintf(buf, sizeof(buf), "PORT %d,%d,%d,%d,%d,%d\r\n",adp[0] & 0xff, adp[1] & 0xff, adp[2] & 0xff, adp[3] & 0xff,portp[0] & 0xff, portp[1] & 0xff)`, mas no lugar do `adp[2]` ela recebe `fnp[0]` e no lugar do `portp[0]` recebe `fnp[1]`.
