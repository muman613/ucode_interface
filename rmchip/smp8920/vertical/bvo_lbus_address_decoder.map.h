/* autogenerated with parsemap: do not edit. */
struct bvo_lbus_address_decoder_mem {
#define bvo_lbus_address_decoder_mem_reset_OFF 0x00000000
/* [0x00000000,0x00000040[ */ struct { struct reset_det d; uint32_t w[(0x00000040-sizeof(struct reset_det))/4]; } _reset;
                              uint32_t pad0[192/4];
#define bvo_lbus_address_decoder_mem_dacmux_OFF 0x00000100
/* [0x00000100,0x00000108[ */ struct { struct dacmux_det d; uint32_t w[(0x00000008-sizeof(struct dacmux_det))/4]; } _dacmux;
#define bvo_lbus_address_decoder_mem_teletextram_OFF 0x00000108
/* [0x00000108,0x0000010c[ */ struct { struct teletextram_det d; uint32_t w[(0x00000004-sizeof(struct teletextram_det))/4]; } _teletextram;
                              uint32_t pad1[116/4];
#define bvo_lbus_address_decoder_mem_pads_fpd_OFF 0x00000180
/* [0x00000180,0x000001a0[ */ struct { struct pads_fpd_det d; uint32_t w[(0x00000020-sizeof(struct pads_fpd_det))/4]; } _pads_fpd;
#define bvo_lbus_address_decoder_mem_lvds_link_OFF 0x000001a0
/* [0x000001a0,0x000001c0[ */ struct { struct lvds_link_det d; uint32_t w[(0x00000020-sizeof(struct lvds_link_det))/4]; } _lvds_link;
                              uint32_t pad2[64/4];
#define bvo_lbus_address_decoder_mem_d0_cg_OFF 0x00000200
/* [0x00000200,0x00000220[ */ struct { struct d0_cg_det d; uint32_t w[(0x00000020-sizeof(struct d0_cg_det))/4]; } _d0_cg;
#define bvo_lbus_address_decoder_mem_d1_cg_OFF 0x00000220
/* [0x00000220,0x00000240[ */ struct { struct d1_cg_det d; uint32_t w[(0x00000020-sizeof(struct d1_cg_det))/4]; } _d1_cg;
#define bvo_lbus_address_decoder_mem_a0_cg_OFF 0x00000240
/* [0x00000240,0x00000260[ */ struct { struct a0_cg_det d; uint32_t w[(0x00000020-sizeof(struct a0_cg_det))/4]; } _a0_cg;
#define bvo_lbus_address_decoder_mem_a1_cg_OFF 0x00000260
/* [0x00000260,0x00000280[ */ struct { struct a1_cg_det d; uint32_t w[(0x00000020-sizeof(struct a1_cg_det))/4]; } _a1_cg;
                              uint32_t pad3[128/4];
#define bvo_lbus_address_decoder_mem_d0_OFF 0x00000300
/* [0x00000300,0x00000400[ */ struct { struct d0_det d; uint32_t w[(0x00000100-sizeof(struct d0_det))/4]; } _d0;
#define bvo_lbus_address_decoder_mem_d1_OFF 0x00000400
/* [0x00000400,0x00000500[ */ struct { struct d1_det d; uint32_t w[(0x00000100-sizeof(struct d1_det))/4]; } _d1;
#define bvo_lbus_address_decoder_mem_a0_OFF 0x00000500
/* [0x00000500,0x00000600[ */ struct { struct a0_det d; uint32_t w[(0x00000100-sizeof(struct a0_det))/4]; } _a0;
#define bvo_lbus_address_decoder_mem_a1_OFF 0x00000600
/* [0x00000600,0x00000700[ */ struct { struct a1_det d; uint32_t w[(0x00000100-sizeof(struct a1_det))/4]; } _a1;
#define bvo_lbus_address_decoder_mem_pads_digital_hdmi0_OFF 0x00000700
/* [0x00000700,0x00000780[ */ struct { struct pads_digital_hdmi0_det d; uint32_t w[(0x00000080-sizeof(struct pads_digital_hdmi0_det))/4]; } _pads_digital_hdmi0;
#define bvo_lbus_address_decoder_mem_pads_digital_hdmi1_OFF 0x00000780
/* [0x00000780,0x00000800[ */ struct { struct pads_digital_hdmi1_det d; uint32_t w[(0x00000080-sizeof(struct pads_digital_hdmi1_det))/4]; } _pads_digital_hdmi1;
#define bvo_lbus_address_decoder_mem_pads_hdmi_OFF 0x00000800
/* [0x00000800,0x00001000[ */ struct { struct pads_hdmi_det d; uint32_t w[(0x00000800-sizeof(struct pads_hdmi_det))/4]; } _pads_hdmi;
#define bvo_lbus_address_decoder_mem_teletextram_mem_OFF 0x00001000
/* [0x00001000,0x00001320[ */ struct { struct teletextram_mem_det d; uint32_t w[(0x00000320-sizeof(struct teletextram_mem_det))/4]; } _teletextram_mem;
                              uint32_t pad4[224/4];
#define bvo_lbus_address_decoder_mem_d0_mem_OFF 0x00001400
/* [0x00001400,0x00001700[ */ struct { struct d0_mem_det d; uint32_t w[(0x00000300-sizeof(struct d0_mem_det))/4]; } _d0_mem;
                              uint32_t pad5[256/4];
#define bvo_lbus_address_decoder_mem_d1_mem_OFF 0x00001800
/* [0x00001800,0x00001b00[ */ struct { struct d1_mem_det d; uint32_t w[(0x00000300-sizeof(struct d1_mem_det))/4]; } _d1_mem;
};
