/* autogenerated with parsemap: do not edit. */
struct tdmx_lbus_address_decoder_mem {
#define tdmx_lbus_address_decoder_mem_tdmx_ch8_block_OFF 0x00000000
/* [0x00000000,0x000f0000[ */ struct { struct tdmx_ch8_block_det d; uint32_t w[(0x000f0000-sizeof(struct tdmx_ch8_block_det))/4]; } _tdmx_ch8_block;
#define tdmx_lbus_address_decoder_mem_tdmx_sc0_OFF 0x000f0000
/* [0x000f0000,0x000f0200[ */ struct { struct tdmx_sc0_det d; uint32_t w[(0x00000200-sizeof(struct tdmx_sc0_det))/4]; } _tdmx_sc0;
#define tdmx_lbus_address_decoder_mem_tdmx_sc1_OFF 0x000f0200
/* [0x000f0200,0x000f0400[ */ struct { struct tdmx_sc1_det d; uint32_t w[(0x00000200-sizeof(struct tdmx_sc1_det))/4]; } _tdmx_sc1;
};
