/*****************************************
 Copyright © 2001-2004       
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

#define ALLOW_OS_CODE 1

#include "../llad/include/dmacpy.h"

#include "sock.h"
#include "include/llad_server.h"
#include "include/llad_protocol.h"
#include "struct.h"

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#if RMPLATFORM != RMPLATFORMID_WINNT
	#include <unistd.h>
#endif

struct dmacpy *dmacpy_open(struct llad *h)
{
	struct dmacpy *pdmacpy;
	RMuint16 port;
	
	pdmacpy = (struct dmacpy *) malloc(sizeof(struct dmacpy));
	if (pdmacpy == NULL) return NULL;
	
	port = SOCK_LLAD_PORT + (RMuint16)h->device;
	pdmacpy->sd = sock_connect(port, h->hostname);
	if (pdmacpy->sd == NULL) {
		free(pdmacpy);
		fprintf(stderr, "network/" __FILE__ ": Unable to open connection to %s:%lu\n", h->hostname, h->device);
		return NULL;
	}
	pdmacpy->local_buf = NULL;
	pdmacpy->remote_buf = NULL;
	
	sock_write_uint32(pdmacpy->sd, SOCK_LLAD_SERVICE);

	return pdmacpy;
}

void dmacpy_close(struct dmacpy *h)
{
	if (h != NULL) {
		sock_close(h->sd);
		free(h);
	}
}

void dmacpy_get_info(struct dmacpy *h, RMuint32 *size, RMuint32 *physical_address)
{
	RMuint32 val;

	sock_write_uint32(h->sd, SOCK_DMACPY_GET_INFO);
	if (sock_read_uint32(h->sd, &val) == 4)
		*size = val;

	if (sock_read_uint32(h->sd, &val) == 4)
		*physical_address = val;
}


void dmacpy_write_data(struct dmacpy *h, RMuint32 offset, RMuint8 *data, RMuint32 size)
{
	sock_write_uint32(h->sd, SOCK_DMACPY_WRITE_DATA);
	sock_write_uint32(h->sd, offset);
	sock_write_uint32(h->sd, size);
	sock_write_buf(h->sd, data, size);
}

void dmacpy_read_data(struct dmacpy *h, RMuint32 offset, RMuint8 *data, RMuint32 size)
{
	sock_write_uint32(h->sd, SOCK_DMACPY_READ_DATA);
	sock_write_uint32(h->sd, offset);
	sock_write_uint32(h->sd, size);
	sock_read_buf(h->sd, data, size);
}
