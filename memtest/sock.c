/*****************************************
 Copyright © 2001-2004       
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

#define ALLOW_OS_CODE 1

#include "sock.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/time.h>
#include <errno.h>
#include <limits.h>
#include <string.h>

#ifdef __WIN32__
	#include <winsock.h>
#else
	#include <sys/socket.h>
	#include <unistd.h>
	#include <netinet/in.h>
	#include <netinet/tcp.h>
	#include <netdb.h>
	#include <arpa/inet.h>

	#undef fprintf
	#define fprintf(...)
#endif


struct sock {
	int sfd;
};

RMuint32 _sock_read(int sock_fd, char* buf, RMuint32 len);
RMuint32 _sock_write(int sock_fd, char* buf, RMuint32 len);


/* Converts ascii text to in_addr struct.
   NULL is returned if the address can not be found. */
static struct in_addr *atoaddr(char *address)
{
	struct hostent *host;
	static struct in_addr saddr;
	
	/* First try it as aaa.bbb.ccc.ddd. */
	saddr.s_addr = inet_addr(address);
	if ((int) saddr.s_addr != -1) {
		return &saddr;
	}
	host = gethostbyname(address);
	if (host != NULL) {
		return (struct in_addr *) *host->h_addr_list;
	}
	return NULL;
}

struct sock *sock_create(RMuint16 port, RMuint32 queue_size)
{
	struct sock *h;
	struct sockaddr_in address;
	int one = 1;

	/* Setup internet address information.
	   This is used with the bind() call */
	memset((char *) &address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = htonl(INADDR_ANY);

	h = (struct sock *) malloc(sizeof(struct sock));
	h->sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (h->sfd < 0) {
		perror("socket");
		free(h);
		return NULL;
	}

#ifdef __WIN32__
	setsockopt(h->sfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&one, sizeof(one));
	setsockopt(h->sfd, IPPROTO_TCP, TCP_NODELAY, (const char*)&one, sizeof(one));
#else
	setsockopt(h->sfd, SOL_SOCKET, SO_REUSEADDR, (void *)&one, sizeof(one));
	setsockopt(h->sfd, SOL_TCP, TCP_NODELAY, (void *)&one, sizeof(one));
#endif

	if (bind(h->sfd, (struct sockaddr *) &address, sizeof(address)) < 0) {
		perror("bind");
#ifdef __WIN32__
		closesocket(h->sfd);
#else
		close(h->sfd);
#endif
		free(h);
		return NULL;
	}
	
	listen(h->sfd, queue_size); /* accept only one connection */

	return h;
}

struct sock *sock_connect(RMuint16 port, RMascii *netaddress)
{
	struct in_addr *addr;
	struct sockaddr_in address;
	struct sock *h;
	int one = 1;

#ifdef __WIN32__
	// Start Winsock up
    struct WSAData wsaData;
	int nCode;
    if ((nCode = WSAStartup(MAKEWORD(1, 1), &wsaData)) != 0) {
		printf("WSAStartup() returned error code %s.", nCode);
        return NULL;
    }
#endif

	addr = atoaddr(netaddress);
	if (addr == NULL) {
		fprintf(stderr,"make_connection:  Invalid network address.\n");
		return NULL;
	}

	//fprintf(stdout, "Connecting to %s:%d\n", netaddress, port);
	memset((char *) &address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	address.sin_addr.s_addr = addr->s_addr;

	h = (struct sock *) malloc(sizeof(struct sock));
	h->sfd = socket(AF_INET, SOCK_STREAM, 0);

	// Set TCP_NODELAY so that little packets are sent immediately
#ifdef __WIN32__
	setsockopt(h->sfd, IPPROTO_TCP, TCP_NODELAY, (const char*)&one, sizeof(one));
#else
	setsockopt(h->sfd, SOL_TCP, TCP_NODELAY, (void *)&one, sizeof(one));
#endif
	if (connect(h->sfd, (struct sockaddr *) &address, sizeof(address)) < 0) {
		perror("connect");
		return NULL;
	}
	
	return h;
}

struct sock *sock_wait_connection(struct sock *listening_sock)
{
	struct sock *h;

	h = (struct sock *) malloc(sizeof(struct sock));

	fprintf(stderr, "wait for connection to socketfd is %d\n", listening_sock->sfd);
	while ((h->sfd = accept(listening_sock->sfd, NULL, NULL)) < 0) {
		/* Either a real error occured, or blocking was interrupted for
		   some reason.  Only abort execution if a real error occured. */
		if (errno != EINTR) {
			perror("accept");
			free(h);
			return NULL;
		} else {
			continue;    /* don't fork - do the accept again */
		}
	}
	fprintf(stderr, "connection accepted. socketfd is %d\n", h->sfd);
	
	return h;
}

struct sock *sock_wait_connection_with_timeout(struct sock *listening_sock, RMuint32 usecTimeout)
{
	struct sock *h;
    struct timeval timeout= {0,};	
    int r, nfds = 0;
    fd_set readfds, writefds, exceptfds;
	h = (struct sock *) malloc(sizeof(struct sock));

    timeout.tv_usec = usecTimeout;
	
    FD_ZERO (&readfds);
    FD_ZERO (&writefds);
    FD_ZERO (&exceptfds);
    FD_SET (listening_sock->sfd, &readfds);
    nfds = listening_sock->sfd + 1;
	
    r = select(nfds, &readfds, &writefds, &exceptfds, &timeout);
    if (r < 0){
        if (errno != EINTR) {
            perror("accept");
        }
        free(h);
        return NULL;
    }
	
	
    if (!(FD_ISSET (listening_sock->sfd, &readfds))) {
        free(h);
        return NULL;
    }
	
    printf("About to try Accept\n");
    
	if ((h->sfd = accept(listening_sock->sfd, NULL, NULL)) < 0) {
		free(h);
		return NULL;
	}
    
	fprintf(stderr, "connection accepted. socketfd is %d\n", h->sfd);
	
	return h;
}


void sock_close(struct sock *h)
{
	if (h != NULL) {
#ifdef __WIN32__
		closesocket(h->sfd);
#else
		close(h->sfd);
#endif
		free(h);
#ifdef __WIN32__
		WSACleanup();
#endif
	}
}

RMint32 sock_read_buf(struct sock *h, RMuint8 *buf, RMuint32 count)
{
	size_t bytes_read = 0;
	int this_read;
	
	while (bytes_read < count) {
		do
			this_read = _sock_read(h->sfd, (char *)buf, count - bytes_read);
		while ((this_read < 0) && (errno == EINTR));

		if (this_read < 0)
 			return this_read;
		else if (this_read == 0)
			return bytes_read;

		bytes_read += this_read;
		buf += this_read;
	}

	return count;
}

RMint32 sock_write_buf(struct sock *h, RMuint8 *buf, RMuint32 count)
{
	size_t bytes_write = 0;
	int this_write;
	
	while (bytes_write < count) {
		do
			this_write = _sock_write(h->sfd, (char *)buf, count - bytes_write);
		while ((this_write < 0) && (errno == EINTR));

		if (this_write < 0)
			return this_write;
		else if (this_write == 0)
			return bytes_write;;
		
		bytes_write += this_write;
		buf += this_write;
	}

	return count;
}

RMint32 sock_read_uint32(struct sock *h, RMuint32 *val)
{
	RMuint8 buf[4];
	RMint32 rc;
	
	rc = sock_read_buf(h, buf, 4);

	*val = buf[0] + (buf[1] << 8) + (buf[2] << 16) + (buf[3] << 24);

	return rc;
}

RMint32 sock_write_uint32(struct sock *h, RMuint32 val)
{
	RMuint8 buf[4];

	buf[0] = (RMuint8)(val & 0xff);
	buf[1] = (RMuint8)((val >> 8)  & 0xff);
	buf[2] = (RMuint8)((val >> 16) & 0xff);
	buf[3] = (RMuint8)((val >> 24) & 0xff);

	return sock_write_buf(h, buf, 4);
}

RMint32 sock_write_2_uint32(struct sock *h, RMuint32 val1, RMuint32 val2)
{
	RMuint8 buf[8];

	buf[0] = (RMuint8)(val1 & 0xff);
	buf[1] = (RMuint8)((val1 >> 8)  & 0xff);
	buf[2] = (RMuint8)((val1 >> 16) & 0xff);
	buf[3] = (RMuint8)((val1 >> 24) & 0xff);
	buf[4] = (RMuint8)(val2 & 0xff);
	buf[5] = (RMuint8)((val2 >> 8)  & 0xff);
	buf[6] = (RMuint8)((val2 >> 16) & 0xff);
	buf[7] = (RMuint8)((val2 >> 24) & 0xff);

	return sock_write_buf(h, buf, 8);
}

RMint32 sock_write_3_uint32(struct sock *h, RMuint32 val1, RMuint32 val2, RMuint32 val3)
{
	RMuint8 buf[12];

	buf[0] = (RMuint8)(val1 & 0xff);
	buf[1] = (RMuint8)((val1 >> 8)  & 0xff);
	buf[2] = (RMuint8)((val1 >> 16) & 0xff);
	buf[3] = (RMuint8)((val1 >> 24) & 0xff);
	buf[4] = (RMuint8)(val2 & 0xff);
	buf[5] = (RMuint8)((val2 >> 8)  & 0xff);
	buf[6] = (RMuint8)((val2 >> 16) & 0xff);
	buf[7] = (RMuint8)((val2 >> 24) & 0xff);
	buf[8] = (RMuint8)(val3 & 0xff);
	buf[9] = (RMuint8)((val3 >> 8)  & 0xff);
	buf[10] = (RMuint8)((val3 >> 16) & 0xff);
	buf[11] = (RMuint8)((val3 >> 24) & 0xff);

	return sock_write_buf(h, buf, 12);
}

RMuint32 _sock_read(int sock_fd, char* buf, RMuint32 len)
{
#ifdef __WIN32__
	return recv(sock_fd, buf, len, 0);
#else
	return read(sock_fd, buf, len);
#endif
}

RMuint32 _sock_write(int sock_fd, char* buf, RMuint32 len)
{
#ifdef __WIN32__
	return send(sock_fd, buf, len, 0);
#else
	return write(sock_fd, buf, len);
#endif
}
