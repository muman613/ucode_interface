#ifndef __UCODE_UTILS_H__
#define __UCODE_UTILS_H__

#include "rmdef/rmdef.h"
#include "remote_client/llad.h"
#include "remote_client/gbus.h"

namespace ucode_utils {
    RMstatus ucode_get_microcode_size(
        RMuint8 *ucode_data, // the data of the microcode's .bin file
        RMuint32 ucode_size, // size of data in bytes
        RMuint32 *low_offset,
        RMuint32 *high_offset);

    RMstatus ucode_load_microcode(
        GBUS_PTR pGBus,
        RMuint32 PMem_Base,  // GBus byte address of RISC's PMem block
        RMuint32 DMem_Base,  // GBus byte address of RISC's DMem block
        RMuint32 DRAM_Base,  // GBus byte address of DRAM memory range for this microcode
        RMuint32 DMem_Width, // DMem width (in bit or byte)
        RMuint8 *ucode_data, // the data of the microcode's .bin file
        RMuint32 ucode_size);// size of data in bytes
}

#endif // __UCODE_UTILS_H__
