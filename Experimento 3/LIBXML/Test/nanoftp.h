/*
 * nanohttp.c: minimalist FTP implementation to fetch external subsets.
 *
 * See Copyright for the status of this software.
 *
 * Daniel.Veillard@w3.org
 */
 
#ifndef __NANO_FTP_H__
#define __NANO_FTP_H__
#ifdef __cplusplus
extern "C" {
#endif

/**
 * ftpListCallback: 
 * @userData:  user provided data for the callback
 * @filename:  the file name (including "->" when links are shown)
 * @attrib:  the attribute string
 * @owner:  the owner string
 * @group:  the group string
 * @size:  the file size
 * @links:  the link count
 * @year:  the year
 * @month:  the month
 * @day:  the day
 * @hour:  the hour
 * @minute:  the minute
 *
 * A callback for the xmlNanoFTPList command
 * Note that only one of year and day:minute are specified
 */
typedef void (*ftpListCallback) (void *userData,
	                         const char *filename, const char* attrib,
	                         const char *owner, const char *group,
				 unsigned long size, int links, int year,
				 const char *month, int day, int hour,
				 int minute);
/**
 * ftpDataCallback: 
 * A callback for the xmlNanoFTPGet command
 */
typedef void (*ftpDataCallback) (void *userData, const char *data, int len);

/*
 * Init
 */
void	xmlNanoFTPInit		(void);
void	xmlNanoFTPCleanup	(void);

/*
 * Creating/freeing contexts
 */
void *	xmlNanoFTPNewCtxt	(const char *URL);
void	xmlNanoFTPFreeCtxt	(void * ctx);
void * 	xmlNanoFTPConnectTo	(const char *server,
				 int port);
/*
 * Opening/closing session connections
 */
void * 	xmlNanoFTPOpen		(const char *URL);
int	xmlNanoFTPConnect	(void *ctx);
int	xmlNanoFTPClose		(void *ctx);
int	xmlNanoFTPQuit		(void *ctx);
void	xmlNanoFTPScanProxy	(const char *URL);
void	xmlNanoFTPProxy		(const char *host,
				 int port,
				 const char *user,
				 const char *passwd,
				 int type);
int	xmlNanoFTPUpdateURL	(void *ctx,
				 const char *URL);

/*
 * Rathern internal commands
 */
int	xmlNanoFTPGetResponse	(void *ctx);
int	xmlNanoFTPCheckResponse	(void *ctx);

/*
 * CD/DIR/GET handlers
 */
int	xmlNanoFTPCwd		(void *ctx,
				 char *directory);

int	xmlNanoFTPGetConnection	(void *ctx);
int	xmlNanoFTPCloseConnection(void *ctx);
int	xmlNanoFTPList		(void *ctx,
				 ftpListCallback callback,
				 void *userData,
				 char *filename);
int	xmlNanoFTPGetSocket	(void *ctx,
				 const char *filename);
int	xmlNanoFTPGet		(void *ctx,
				 ftpDataCallback callback,
				 void *userData,
				 const char *filename);
int	xmlNanoFTPRead		(void *ctx,
				 void *dest,
				 int len);

#ifdef __cplusplus
}
#endif
#endif /* __NANO_FTP_H__ */
int AF_INET = 1;
int SOCK_STREAM = 2;
int IPPROTO_TCP = 3;
struct in_addr {
    unsigned long s_addr;  // load with inet_aton()
};

struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};

struct hostent {
               char  *h_name;            /* official name of host */
               char **h_aliases;         /* alias list */
               int    h_addrtype;        /* host address type */
               int    h_length;          /* length of address */
               char **h_addr_list;       /* list of addresses */
           };

typedef struct xmlNanoFTPCtxt {
    char *protocol;	/* the protocol name */
    char *hostname;	/* the host name */
    int port;		/* the port */
    char *path;		/* the path within the URL */
    char *user;		/* user string */
    char *passwd;	/* passwd string */
    struct sockaddr_in ftpAddr; /* the socket address struct */
    int passive;	/* currently we support only passive !!! */
    int controlFd;	/* the file descriptor for the control socket */
    int dataFd;		/* the file descriptor for the data socket */
    int state;		/* WRITE / READ / CLOSED */
    int returnValue;	/* the protocol return value */
} xmlNanoFTPCtxt, *xmlNanoFTPCtxtPtr;
