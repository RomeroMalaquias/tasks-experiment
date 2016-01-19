# Task 3
### Parenthesis / Operator. Forgetting any operand.

##Task:
**Decida em qual(is) configurações existe(m) erro(s).**

R: 
```
#define FEAT_MZSCHEME
#define HAVE_SYS_TIME_H
#define HAVE_GETTIMEOFDAY
```
os_unix-UD.c:32:21: error: storage size of 'start_tv' isn't known
     struct timeval  start_tv;