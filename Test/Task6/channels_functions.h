typedef struct BUFFER
{
	int buff;
} BUFFER;
typedef struct version
{
	int version;
} version;
typedef struct session
{
	version version;
} session;
typedef struct CHANNEL
{
	session session;
} CHANNEL;


int channel_open(CHANNEL *channel, const char *type_c, int window,int maxpacket, BUFFER *payload);
int channel_open_session1(CHANNEL *channel);
