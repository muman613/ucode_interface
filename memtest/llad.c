/*****************************************
 Copyright © 2001-2004
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

#define ALLOW_OS_CODE 1

#include "include/llad.h"

#include "include/sock.h"
#include "include/llad_protocol.h"
#include "struct.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#if RMPLATFORM == RMPLATFORMID_WINNT
	#define snprintf _snprintf
	int getuid();
#else
	#include <sys/ioctl.h>
	#include <unistd.h>
#endif

size_t strlen(const char *s);
char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);

struct llad *llad_open(RMascii *device)
{
	struct llad *pllad;
	size_t i;
	RMuint16 port;
	RMuint32 uid;

	pllad = (struct llad *) malloc(sizeof(struct llad));
	if (pllad == NULL) return NULL;

	pllad->hostname = (char *) malloc(strlen(device) + 1);
	if (pllad->hostname == NULL) {
		free(pllad);
		return NULL;
	}
	for (i=0 ; i<strlen(device) ; i++) {
		if (device[i] == ':') break;
		pllad->hostname[i] = device[i];
	}
	pllad->hostname[i] = '\0';
	pllad->device = strtol(device+i+1, NULL, 10);
	port = SOCK_LLAD_PORT + (RMuint16)pllad->device;
#ifndef ENABLE_CURSES
	fprintf(stdout, "Hostname<%s>, device<%d>\n", pllad->hostname, port);
#endif // ENABLE_CURSES
	pllad->sd = sock_connect(port, pllad->hostname);
	if (pllad->sd == NULL) {
		free(pllad->hostname);
 		free(pllad);
		fprintf(stderr, "network/" __FILE__ ": Unable to open connection to %s\n", device);
		return NULL;
	}

	sock_write_uint32(pllad->sd, SOCK_LLAD_SERVICE);
	sock_write_uint32(pllad->sd, (RMuint32) getuid());
	if ((sock_read_uint32(pllad->sd, &uid) < 4) ||
	    (uid != (RMuint32) getuid())) {
		free(pllad->hostname);
 		free(pllad);
		fprintf(stderr, "network/" __FILE__ ": Connection refused, locked by user %lu\n", uid);
		return NULL;
	}

	return pllad;
}


void llad_close(struct llad *h)
{
	if (h != NULL) {
		sock_close(h->sd);
		free(h->hostname);
		free(h);
	}
}

void llad_get_config(struct llad *h, RMascii* config_name, RMuint32 config_size)
{

#ifndef WITH_DISPLAY_C_SIMULATION
	RMuint32 length;
	snprintf(config_name, config_size, "%s:%lu <> ", h->hostname, h->device);

	length = strlen(config_name);
	config_name += length;
	config_size -= length;
#endif

	sock_write_uint32(h->sd, SOCK_LLAD_GET_CONFIG);
	sock_write_uint32(h->sd, config_size);
	sock_read_buf(h->sd, (unsigned char *)config_name, config_size);
}

RMuint32 llad_get_open_count(struct llad *h)
{
	RMuint32 count = 0;

	sock_write_uint32(h->sd, SOCK_LLAD_GET_OPEN_COUNT);
	sock_read_uint32(h->sd, &count);

	return count;
}

RMuint32 llad_lock(struct llad *h)
{
	RMuint32 count = 0;

	sock_write_uint32(h->sd, SOCK_LLAD_LOCK);
	sock_read_uint32(h->sd, &count);

	return count;
}

void llad_unlock(struct llad *h)
{
	sock_write_uint32(h->sd, SOCK_LLAD_UNLOCK);
}

RMuint32 llad_wait_interrupt(struct llad *h, RMuint32 mask, RMuint32 *timeout_microsecond)
{
	RMuint32 active_mask = 0;

	sock_write_uint32(h->sd, SOCK_LLAD_WAIT_INTERRUPT);
	sock_write_uint32(h->sd, mask);
	sock_write_uint32(h->sd, *timeout_microsecond);

	sock_read_uint32(h->sd, &active_mask);
	sock_read_uint32(h->sd, timeout_microsecond);
	return active_mask;
}

RMstatus llad_wait_channels(struct llad *h, RMuint32 *channel_array, RMuint32 channel_count, RMuint32 timeout_microsecond, RMuint32 *active_channel)
{
	return RM_NOTIMPLEMENTED;
}


void llad_force_rom_ub(struct llad *h)
{
	RMPanic(RM_NOTIMPLEMENTED);
}

void llad_cache_dump(struct llad *h, RMuint32 *dst)
{
	RMPanic(RM_NOTIMPLEMENTED);
}


#if RMPLATFORM == RMPLATFORMID_WINNT

int getuid() {
	return 0;
}

#endif

