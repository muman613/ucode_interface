/* autogenerated with parsecfg: do not edit. */

union vo_dac_mux_config1Reg {
 struct { uint32_t

 /* sorting 4 */
#define vo_dac_mux_config1_c5_SHIFT 0
#define vo_dac_mux_config1_c5_WIDTH 6
#define vo_dac_mux_config1_c6_SHIFT 8
#define vo_dac_mux_config1_c6_WIDTH 6
#define vo_dac_mux_config1_c7_SHIFT 16
#define vo_dac_mux_config1_c7_WIDTH 6
#define vo_dac_mux_config1_c8_SHIFT 24
#define vo_dac_mux_config1_c8_WIDTH 6

 c5:6, /*[5:0]  */
 hole0:2,
 c6:6, /*[13:8]  */
 hole1:2,
 c7:6, /*[21:16]  */
 hole2:2,
 c8:6, /*[29:24]  */
 hole3:2;
 } bits;

 uint32_t value;
};

union vo_dac_mux_config0Reg {
 struct { uint32_t

 /* sorting 4 */
#define vo_dac_mux_config0_c1_SHIFT 0
#define vo_dac_mux_config0_c1_WIDTH 6
#define vo_dac_mux_config0_c2_SHIFT 8
#define vo_dac_mux_config0_c2_WIDTH 6
#define vo_dac_mux_config0_c3_SHIFT 16
#define vo_dac_mux_config0_c3_WIDTH 6
#define vo_dac_mux_config0_c4_SHIFT 24
#define vo_dac_mux_config0_c4_WIDTH 6

 c1:6, /*[5:0]  */
 hole0:2,
 c2:6, /*[13:8]  */
 hole1:2,
 c3:6, /*[21:16]  */
 hole2:2,
 c4:6, /*[29:24]  */
 hole3:2;
 } bits;

 uint32_t value;
};

struct vo_dac_mux {
 union vo_dac_mux_config0Reg vo_dac_mux_config0; /* +0x00000000  */
 union vo_dac_mux_config1Reg vo_dac_mux_config1; /* +0x00000004  */
};
