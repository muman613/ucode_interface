/*
Copyright (C) 2003  Sigma Designs, Inc.

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef __GBUS_H__
#define __GBUS_H__

#include <linux/version.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,0,0)
/* TODO: need to find the proper header inclusions ... */
typedef unsigned long RMuint32;
typedef unsigned short RMuint16;
typedef unsigned char RMuint8;
typedef char RMascii;
typedef int RMstatus;
typedef int RMbool;
#else
#ifdef RMBUILD_USE_HWLIB_V2 //#if (RMCHIP_ID==RMCHIP_ID_SMP8910)
#if defined(CONFIG_MIPS)
#include <asm/tango4/rmdefs.h>
#elif defined(CONFIG_ARM)
#include <mach/rmdefs.h>
#endif
#else // (RMCHIP_ID==RMCHIP_ID_SMP8910)
#include <asm/tango3/rmdefs.h>
#endif // (RMCHIP_ID==RMCHIP_ID_SMP8910)

#endif

struct gbus;
struct kc_tasklet_struct;
#define pGBus ((struct gbus *)1)

RMuint32 gbus_read_uint32(struct gbus *pgbus, RMuint32 byte_address);
RMuint16 gbus_read_uint16(struct gbus *pgbus, RMuint32 byte_address);
RMuint8 gbus_read_uint8(struct gbus *pgbus, RMuint32 byte_address);
void gbus_write_uint32(struct gbus *pgbus, RMuint32 byte_address, RMuint32 data);
void gbus_write_uint16(struct gbus *pgbus, RMuint32 byte_address, RMuint16 data);
void gbus_write_uint8(struct gbus *pgbus, RMuint32 byte_address, RMuint8 data);

#endif /* __GBUS_H__ */

