# Task 3
### Add a new feature.

##Task:
**Adicionar a funcionalidade ...**

Devido a grande aceitação do Protocolo IPV6 tornou-se necessário o acréscimo desse protocolo em nosso sistema. Além disso, devido a novas parcerias é necessário adicionar o protocolo proprietário IPX. 
A função `evutil_ersatz_socketpair_(...)` verifica se o socket criado está utilizando o protocolo correto, (ex: `family == AF_INET`, quando o protocolo usado é o IPv4).
Adicione a função, verificações para os novos protocolos adicionados (IPv6 e IPX), seguindo os seguintes critérios:
Quando USE_AF_INET6 estiver definido (`#define USE_AF_INET6`), a função irá verificar a família para ipv6
Quando USE_AF_IPX estiver definido (`#define USE_AF_IPX`), a função irá verificar a família para IPX.
`AF_INET` é uma feature referente ao IPv4 Internet protocols.
`AF_INET6` é uma feature referente ao IPv6 Internet protocols.
`AF_IPX` é uma feature referente ao IPX - Novell protocols.
Uma das features `USE_AF_INET`, `USE_AF_INET6` ou `USE_AF_IPX` sempre vai estar definidas, mas não mais do que uma.

