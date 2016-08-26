#include <stdio.h>
#include <stdlib.h>

#define ALLOW_OS_CODE
#include "ucode_utils.h"

#ifdef _DEBUG
#define LOCALDBG DISABLE
#else
#define LOCALDBG DISABLE
#endif // _DEBUG

namespace ucode_utils {

static inline RMuint32 ucode_read_uint32(RMuint8 *addr)
{
	return RMbeBufToUint32(addr);
}

static inline RMuint32 ucode_read_uint16(RMuint8 *addr)
{
	return RMbeBufToUint16(addr);
}

// returns lowest and highest offset used in DRAM segments
RMstatus ucode_get_microcode_size(
	RMuint8 *ucode_data, // the data of the microcode's .bin file
	RMuint32 ucode_size, // size of data in bytes
	RMuint32 *low_offset,
	RMuint32 *high_offset)
{
	RMuint32 p = 0;
	RMuint32 start_address, end_address, type_descriptor, body_size;

	*low_offset = MaxRMuint32;
	*high_offset = 0;
	while (p < ucode_size) {
		body_size = ucode_read_uint32(ucode_data + p); p += 4;
		type_descriptor = ucode_read_uint32(ucode_data + p); p += 4;
		if (type_descriptor == 0x04) {  // DRAM segment
			start_address = ucode_read_uint32(ucode_data + p);
			end_address = start_address + (body_size - 8);
			if (start_address < *low_offset)  *low_offset  = start_address;
			if (end_address   > *high_offset) *high_offset = end_address;
		}
		p += (body_size - 4);
	}
	if (*high_offset == 0) *low_offset = 0;  // no DRAM used
	return RM_OK;
}

/**
 *
 */

RMstatus ucode_load_microcode(
    GBUS_PTR pGBus,
	RMuint32 PMem_Base,  // GBus byte address of RISC's PMem block
	RMuint32 DMem_Base,  // GBus byte address of RISC's DMem block
	RMuint32 DRAM_Base,  // GBus byte address of DRAM memory range for this microcode
	RMuint32 DMem_Width, // DMem width (in bit or byte)
	RMuint8 *ucode_data, // the data of the microcode's .bin file
	RMuint32 ucode_size) // size of data in bytes
{
	RMuint32 p = 0;
	RMuint32 PMEM_data;
	RMuint32 start_address, type_descriptor, body_size;
	RMuint32 i;

	RMDBGLOG((LOCALDBG, "Loading %ld bytes of microcode with pmem=%08lX, dmem=%08lX, dram=%08lX width=%ld\n",
             ucode_size, PMem_Base, DMem_Base, DRAM_Base, DMem_Width));

	while (p < ucode_size) {
		body_size = ucode_read_uint32(ucode_data + p); p += 4;
		type_descriptor = ucode_read_uint32(ucode_data + p); p += 4;
		//RMDBGLOG((LOCALDBG, "  Chunk type 0x%08lX, size %ld - 8\n", type_descriptor, body_size));
		switch (type_descriptor) {
		case 0x1:  // Write PMEM (32 bit wide), address is offset   by PMEM base
			start_address = ucode_read_uint32(ucode_data + p); p += 4;
			RMDBGLOG((LOCALDBG, "    PMem chunk %ld bytes to %08lX(%08lX)\n", body_size - 8, start_address, PMem_Base + start_address));

			/* segment start is not aligned */
			if (start_address & 2) {
				if (body_size != 8) { /* segment is not empty */
					PMEM_data = pGBus->gbus_read_uint32(PMem_Base + start_address - 2);
					PMEM_data = (PMEM_data & 0xFFFF0000) | ucode_read_uint16(ucode_data + p);
					p += 2;
					pGBus->gbus_write_uint32(PMem_Base  + start_address - 2, PMEM_data);
					body_size -= 2;
					start_address += 2;
				}
			}

			for (i = 0; i < (body_size - 8) / 4; i++, p+=4)
				pGBus->gbus_write_uint32(PMem_Base + start_address + 4 * i, ucode_read_uint32(ucode_data + p));

			/* segment end is not aligned */
			if (body_size & 2) {
				PMEM_data = pGBus->gbus_read_uint32(PMem_Base + start_address + (body_size - 8 - 2));
				PMEM_data = (ucode_read_uint16(ucode_data + p) << 16) | (PMEM_data & 0x0000FFFF);
				p += 2;
				pGBus->gbus_write_uint32(PMem_Base + start_address + (body_size - 8 - 2), PMEM_data);
			}
			break;
		case 0x2:  // Write DMEM (32 or 16 bit wide), address is offset / half offset to DMEM base
			start_address = ucode_read_uint32(ucode_data + p); p += 4;
			RMDBGLOG((LOCALDBG, "    DMem chunk %ld bytes to %08lX(%08lX)\n", body_size - 8, start_address, DMem_Base + start_address));
			switch (DMem_Width) {
			case 2:
			case 16:
				for (i = 0; i < (body_size - 8) / 2; i++, p+=2)
					pGBus->gbus_write_uint32(DMem_Base + 2 * (start_address + 2 * i), ucode_read_uint16(ucode_data + p));

				break;
			case 4:
			case 32:
				for (i = 0; i < (body_size - 8) / 4; i++, p+=4)
					pGBus->gbus_write_uint32(DMem_Base + start_address + 4 * i, ucode_read_uint32(ucode_data + p));

				break;
			default:
				return RM_ERROR;
			}
			break;
		case 0x4:  // Write DRAM (8 bit wide), address is offset to DRAM_Base
			start_address = ucode_read_uint32(ucode_data + p); p += 4;
			RMDBGLOG((LOCALDBG, "    DRAM chunk %ld bytes to %08lX(%08lX)\n", body_size - 8, start_address, DRAM_Base + start_address));
			pGBus->gbus_write_data8(DRAM_Base + start_address, ucode_data + p, body_size - 8);

			p += (body_size - 8);
			break;
		default:
			p += (body_size - 4); // skipping bytes
		}
	}
	return RM_OK;
}

}
