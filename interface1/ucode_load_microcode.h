/*
 *
 * Copyright (c) Sigma Designs, Inc. 2003. All rights reserved.
 *
 */

/**
	@file ucode_load_microcode.h
	@brief

	@author Christian Wolff
*/

#ifndef __UCODE_LOAD_MICROCODE_H__
#define __UCODE_LOAD_MICROCODE_H__

#ifdef __cplusplus
namespace ucode_utils {
#endif // __cplusplus


#ifndef WITH_UCODE_BOOTLOADER
RMstatus ucode_get_microcode_size(
	RMuint8 *ucode_data, // the data of the microcode's .bin file
	RMuint32 ucode_size, // size of data in bytes
	RMuint32 *low_offset,
	RMuint32 *high_offset);
#endif // WITH_UCODE_BOOTLOADER

RMstatus ucode_load_microcode(
	struct gbus *pGBus,
	RMuint32 PMem_Base,  // GBus byte address of RISC's PMem block
	RMuint32 DMem_Base,  // GBus byte address of RISC's DMem block
#ifdef WITH_UCODE_BOOTLOADER
	RMuint32 *DRAM_Base, // GBus byte address of DRAM segment for this microcode
	RMuint32 DMem_Width, // DMem width (in bit or byte)
	RMuint32 ucode_data, // GBus byte address of the microcode's .bin file in DRAM
#else
	RMuint32 DRAM_Base,  // GBus byte address of DRAM memory range for this microcode
	RMuint32 DMem_Width, // DMem width (in bit or byte)
	RMuint8 *ucode_data, // the data of the microcode's .bin file
#endif // WITH_UCODE_BOOTLOADER
	RMuint32 ucode_size);// size of data in bytes

RMstatus ucode_load_segment(struct gbus* pGBus,
	RMuint32 MemBase,
	RMuint32* pData,
	RMuint32 size);

#ifdef __cplusplus
}
#endif // __cplusplus


#endif  /* __UCODE_LOAD_MICROCODE_H__ */
