/* autogenerated with parsemap: do not edit. */
struct hc_dc_cu_bench_reg {
#define hc_dc_cu_bench_reg_dc_cache_unit_OFF 0x00000000
/* [0x00000000,0x00000400[ */ struct { struct dc_cache_unit_det d; uint32_t w[(0x00000100-sizeof(struct dc_cache_unit_det))/4]; } _dc_cache_unit[4];
#define hc_dc_cu_bench_reg_dc_cache_unit_common_OFF 0x00000400
/* [0x00000400,0x00000450[ */ struct { struct dc_cache_unit_common_det d; uint32_t w[(0x00000050-sizeof(struct dc_cache_unit_common_det))/4]; } _dc_cache_unit_common;
};
