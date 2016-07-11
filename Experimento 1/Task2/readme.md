# Task 2
### Parenthesis / Operator. Forgetting any operand.

##Task:
**Decida em qual(is) configurações existe(m) erro(s).**

Foi encontrado um erro de sintaxe (parenteses, chaves, ponto e virgula faltando, ...) em uma das configurações do seguinte código.
Corrija o código fonte de forma que todas as configurações não apresentem erro de sintaxe.

R: 
```
#define FEAT_MZSCHEME
#define HAVE_SYS_TIME_H
#define HAVE_GETTIMEOFDAY
```
os_unix-UD.c: In function 'RealWaitForChar':
os_unix-UD.c:56:5: error: expected ')' before 'gettimeofday'
     gettimeofday(&start_tv, NULL);
     ^
os_unix-UD.c:65:1: error: expected expression before '}' token
 }
 ^