#ifndef __VIDEO_MICROCODE_LABELS_H__
#define __VIDEO_MICROCODE_LABELS_H__

#ifdef UCODE_DEBUG

#if (RMCHIP_ID == RMCHIP_ID_SMP8760)
#include "ucode/8760/debug/video_microcode_SMP8760_labels.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8758)
#include "ucode/8758/debug/video_microcode_SMP8758_labels.h"
#endif

#else   // UCODE_DEBUG

#if (RMCHIP_ID == RMCHIP_ID_SMP8760)
#include "ucode/8760/release/video_microcode_SMP8760_labels.h"
#elif (RMCHIP_ID == RMCHIP_ID_SMP8758)
#include "ucode/8758/release/video_microcode_SMP8758_labels.h"
#endif

#endif // UCODE_DEBUG

#endif // __VIDEO_MICROCODE_LABELS_H__

