/* autogenerated with parsemap: do not edit. */
struct ha_ipu_lbus_address_decoder_reg {
#define ha_ipu_lbus_address_decoder_reg_loop_rom_OFF 0x00000000
/* [0x00000000,0x00000800[ */ struct { struct loop_rom_det d; uint32_t w[(0x00000800-sizeof(struct loop_rom_det))/4]; } _loop_rom;
#define ha_ipu_lbus_address_decoder_reg_perf_monitor_OFF 0x00000800
/* [0x00000800,0x00000840[ */ struct { struct perf_monitor_det d; uint32_t w[(0x00000040-sizeof(struct perf_monitor_det))/4]; } _perf_monitor;
                              uint32_t pad0[192/4];
#define ha_ipu_lbus_address_decoder_reg_lbi_OFF 0x00000900
/* [0x00000900,0x0000090c[ */ struct { struct lbi_det d; uint32_t w[(0x0000000c-sizeof(struct lbi_det))/4]; } _lbi;
};
