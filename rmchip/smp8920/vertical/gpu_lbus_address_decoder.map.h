/* autogenerated with parsemap: do not edit. */
struct gpu_lbus_address_decoder_mem {
#define gpu_lbus_address_decoder_mem_hub_int_mmu_OFF 0x00000000
/* [0x00000000,0x00000500[ */ struct { struct hub_int_mmu_det d; uint32_t w[(0x00000500-sizeof(struct hub_int_mmu_det))/4]; } _hub_int_mmu;
                              uint32_t pad0[768/4];
#define gpu_lbus_address_decoder_mem_hub_int_reg_OFF 0x00000800
/* [0x00000800,0x00000880[ */ struct { struct hub_int_reg_det d; uint32_t w[(0x00000080-sizeof(struct hub_int_reg_det))/4]; } _hub_int_reg;
                              uint32_t pad1[63360/4];
#define gpu_lbus_address_decoder_mem_imgsys_bridge_OFF 0x00010000
/* [0x00010000,0x00020000[ */ struct { struct imgsys_bridge_det d; uint32_t w[(0x00010000-sizeof(struct imgsys_bridge_det))/4]; } _imgsys_bridge;
};
