/*****************************************
 Copyright © 2001-2003	
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

#define ALLOW_OS_CODE
#include "rmdef/rmdef.h"

#include <stdlib.h>
#include <string.h>

void *RMMalloc(RMuint32 size) { return malloc(size); }
void RMFree(void *ptr) { free(ptr); }
void *RMCalloc(RMuint32 nmemb,RMuint32 size) { return calloc(nmemb,size); }
void *RMMemset(void *s, RMuint8 c, RMuint32 n) { return memset(s,c,n); }
void *RMMemcpy(void *dest,const void *src,RMuint32 n) { return memcpy(dest,src,n); }
RMint32 RMMemcmp(const void *s1, const void *s2,RMuint32 n) { return memcmp(s1,s2,n); }
