/* autogenerated with parsecfg: do not edit. */

union vo_chroma_scaler_down_v_processReg {
 struct { uint32_t

 /* sorting 3 */
#define vo_chroma_scaler_down_v_process_type_SHIFT 0
#define vo_chroma_scaler_down_v_process_type_WIDTH 1
#define vo_chroma_scaler_down_v_process_drop_pattern_SHIFT 8
#define vo_chroma_scaler_down_v_process_drop_pattern_WIDTH 8
#define vo_chroma_scaler_down_v_process_out_size_SHIFT 16
#define vo_chroma_scaler_down_v_process_out_size_WIDTH 12

 type:1, /*[0:0]  */
 hole0:7,
 drop_pattern:8, /*[15:8]  */
 out_size:12, /*[27:16]  */
 hole1:4;
 } bits;

 uint32_t value;
};

union vo_chroma_scaler_down_output_formatReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_chroma_scaler_down_output_format_submode_SHIFT 0
#define vo_chroma_scaler_down_output_format_submode_WIDTH 2
#define vo_chroma_scaler_down_output_format_in_bits_SHIFT 4
#define vo_chroma_scaler_down_output_format_in_bits_WIDTH 2

 submode:2, /*[1:0]  */
 hole0:2,
 in_bits:2, /*[5:4]  */
 hole1:26;
 } bits;

 uint32_t value;
};

union vo_chroma_scaler_down_input_formatReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_chroma_scaler_down_input_format_submode_SHIFT 0
#define vo_chroma_scaler_down_input_format_submode_WIDTH 2
#define vo_chroma_scaler_down_input_format_in_bits_SHIFT 4
#define vo_chroma_scaler_down_input_format_in_bits_WIDTH 2

 submode:2, /*[1:0]  */
 hole0:2,
 in_bits:2, /*[5:4]  */
 hole1:26;
 } bits;

 uint32_t value;
};

union vo_chroma_scaler_down_h_scale_factorsReg {
 struct { uint32_t

 /* sorting 1 */
#define vo_chroma_scaler_down_h_scale_factors_vo_chroma_scaler_down_h_scale_factor_0_SHIFT 0
#define vo_chroma_scaler_down_h_scale_factors_vo_chroma_scaler_down_h_scale_factor_0_WIDTH 16

 vo_chroma_scaler_down_h_scale_factor_0:16, /*[15:0]  */
 hole0:16;
 } bits;

 uint32_t value;
};

union vo_chroma_scaler_down_h_processReg {
 struct { uint32_t

 /* sorting 3 */
#define vo_chroma_scaler_down_h_process_type_SHIFT 0
#define vo_chroma_scaler_down_h_process_type_WIDTH 1
#define vo_chroma_scaler_down_h_process_drop_pattern_SHIFT 8
#define vo_chroma_scaler_down_h_process_drop_pattern_WIDTH 8
#define vo_chroma_scaler_down_h_process_out_size_SHIFT 16
#define vo_chroma_scaler_down_h_process_out_size_WIDTH 12

 type:1, /*[0:0]  */
 hole0:7,
 drop_pattern:8, /*[15:8]  */
 out_size:12, /*[27:16]  */
 hole1:4;
 } bits;

 uint32_t value;
};

union vo_chroma_scaler_down_h_confReg {
 struct { uint32_t

 /* sorting 4 */
#define vo_chroma_scaler_down_h_conf_output_size_SHIFT 0
#define vo_chroma_scaler_down_h_conf_output_size_WIDTH 12
#define vo_chroma_scaler_down_h_conf_taps_minus_1_SHIFT 16
#define vo_chroma_scaler_down_h_conf_taps_minus_1_WIDTH 4
#define vo_chroma_scaler_down_h_conf_phases_minus_1_SHIFT 20
#define vo_chroma_scaler_down_h_conf_phases_minus_1_WIDTH 4
#define vo_chroma_scaler_down_h_conf_init_phase_SHIFT 24
#define vo_chroma_scaler_down_h_conf_init_phase_WIDTH 5

 output_size:12, /*[11:0]  */
 hole0:4,
 taps_minus_1:4, /*[19:16]  */
 phases_minus_1:4, /*[23:20]  */
 init_phase:5, /*[28:24]  */
 hole1:3;
 } bits;

 uint32_t value;
};

union vo_chroma_scaler_down_h_coefficient_8_9_10_11Reg {
 struct { uint32_t

 /* sorting 4 */
#define vo_chroma_scaler_down_h_coefficient_8_9_10_11__8_SHIFT 0
#define vo_chroma_scaler_down_h_coefficient_8_9_10_11__8_WIDTH 8
#define vo_chroma_scaler_down_h_coefficient_8_9_10_11__9_SHIFT 8
#define vo_chroma_scaler_down_h_coefficient_8_9_10_11__9_WIDTH 8
#define vo_chroma_scaler_down_h_coefficient_8_9_10_11__10_SHIFT 16
#define vo_chroma_scaler_down_h_coefficient_8_9_10_11__10_WIDTH 8
#define vo_chroma_scaler_down_h_coefficient_8_9_10_11__11_SHIFT 24
#define vo_chroma_scaler_down_h_coefficient_8_9_10_11__11_WIDTH 8

 _8:8, /*[7:0]  */
 _9:8, /*[15:8]  */
 _10:8, /*[23:16]  */
 _11:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_chroma_scaler_down_h_coefficient_4_5_6_7Reg {
 struct { uint32_t

 /* sorting 4 */
#define vo_chroma_scaler_down_h_coefficient_4_5_6_7__4_SHIFT 0
#define vo_chroma_scaler_down_h_coefficient_4_5_6_7__4_WIDTH 8
#define vo_chroma_scaler_down_h_coefficient_4_5_6_7__5_SHIFT 8
#define vo_chroma_scaler_down_h_coefficient_4_5_6_7__5_WIDTH 8
#define vo_chroma_scaler_down_h_coefficient_4_5_6_7__6_SHIFT 16
#define vo_chroma_scaler_down_h_coefficient_4_5_6_7__6_WIDTH 8
#define vo_chroma_scaler_down_h_coefficient_4_5_6_7__7_SHIFT 24
#define vo_chroma_scaler_down_h_coefficient_4_5_6_7__7_WIDTH 8

 _4:8, /*[7:0]  */
 _5:8, /*[15:8]  */
 _6:8, /*[23:16]  */
 _7:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_chroma_scaler_down_h_coefficient_12_13_14_15Reg {
 struct { uint32_t

 /* sorting 4 */
#define vo_chroma_scaler_down_h_coefficient_12_13_14_15__12_SHIFT 0
#define vo_chroma_scaler_down_h_coefficient_12_13_14_15__12_WIDTH 8
#define vo_chroma_scaler_down_h_coefficient_12_13_14_15__13_SHIFT 8
#define vo_chroma_scaler_down_h_coefficient_12_13_14_15__13_WIDTH 8
#define vo_chroma_scaler_down_h_coefficient_12_13_14_15__14_SHIFT 16
#define vo_chroma_scaler_down_h_coefficient_12_13_14_15__14_WIDTH 8
#define vo_chroma_scaler_down_h_coefficient_12_13_14_15__15_SHIFT 24
#define vo_chroma_scaler_down_h_coefficient_12_13_14_15__15_WIDTH 8

 _12:8, /*[7:0]  */
 _13:8, /*[15:8]  */
 _14:8, /*[23:16]  */
 _15:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_chroma_scaler_down_h_coefficient_0_1_2_3Reg {
 struct { uint32_t

 /* sorting 4 */
#define vo_chroma_scaler_down_h_coefficient_0_1_2_3__0_SHIFT 0
#define vo_chroma_scaler_down_h_coefficient_0_1_2_3__0_WIDTH 8
#define vo_chroma_scaler_down_h_coefficient_0_1_2_3__1_SHIFT 8
#define vo_chroma_scaler_down_h_coefficient_0_1_2_3__1_WIDTH 8
#define vo_chroma_scaler_down_h_coefficient_0_1_2_3__2_SHIFT 16
#define vo_chroma_scaler_down_h_coefficient_0_1_2_3__2_WIDTH 8
#define vo_chroma_scaler_down_h_coefficient_0_1_2_3__3_SHIFT 24
#define vo_chroma_scaler_down_h_coefficient_0_1_2_3__3_WIDTH 8

 _0:8, /*[7:0]  */
 _1:8, /*[15:8]  */
 _2:8, /*[23:16]  */
 _3:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_chroma_scaler_down_alphaReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_chroma_scaler_down_alpha_a0_SHIFT 0
#define vo_chroma_scaler_down_alpha_a0_WIDTH 8
#define vo_chroma_scaler_down_alpha_a_enable_SHIFT 16
#define vo_chroma_scaler_down_alpha_a_enable_WIDTH 1

 a0:8, /*[7:0]  */
 hole0:8,
 a_enable:1, /*[16:16]  */
 hole1:15;
 } bits;

 uint32_t value;
};

struct vo_chroma_scaler_down {
 union vo_chroma_scaler_down_h_confReg vo_chroma_scaler_down_h_conf; /* +0x00000000  */
 union vo_chroma_scaler_down_h_scale_factorsReg vo_chroma_scaler_down_h_scale_factors; /* +0x00000004  */
 uint32_t pad0[0x0018/4];
 union vo_chroma_scaler_down_h_coefficient_0_1_2_3Reg vo_chroma_scaler_down_h_coefficient_0_1_2_3; /* +0x00000020  */
 union vo_chroma_scaler_down_h_coefficient_4_5_6_7Reg vo_chroma_scaler_down_h_coefficient_4_5_6_7; /* +0x00000024  */
 union vo_chroma_scaler_down_h_coefficient_8_9_10_11Reg vo_chroma_scaler_down_h_coefficient_8_9_10_11; /* +0x00000028  */
 union vo_chroma_scaler_down_h_coefficient_12_13_14_15Reg vo_chroma_scaler_down_h_coefficient_12_13_14_15; /* +0x0000002c  */
 uint32_t pad1[0x0150/4];
 union vo_chroma_scaler_down_input_formatReg vo_chroma_scaler_down_input_format; /* +0x00000180  */
 union vo_chroma_scaler_down_output_formatReg vo_chroma_scaler_down_output_format; /* +0x00000184  */
 union vo_chroma_scaler_down_alphaReg vo_chroma_scaler_down_alpha; /* +0x00000188  */
 union vo_chroma_scaler_down_h_processReg vo_chroma_scaler_down_h_process; /* +0x0000018c  */
 union vo_chroma_scaler_down_v_processReg vo_chroma_scaler_down_v_process; /* +0x00000190  */
};
