/* autogenerated with parsecfg: do not edit. */

union vo_lib_chroma_scaler_v_processReg {
 struct { uint32_t

 /* sorting 3 */
#define vo_lib_chroma_scaler_v_process_type_SHIFT 0
#define vo_lib_chroma_scaler_v_process_type_WIDTH 1
#define vo_lib_chroma_scaler_v_process_drop_pattern_SHIFT 8
#define vo_lib_chroma_scaler_v_process_drop_pattern_WIDTH 8
#define vo_lib_chroma_scaler_v_process_out_size_SHIFT 16
#define vo_lib_chroma_scaler_v_process_out_size_WIDTH 12

 type:1, /*[0:0]  */
 hole0:7,
 drop_pattern:8, /*[15:8]  */
 out_size:12, /*[27:16]  */
 hole1:4;
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_v_cr_scale_factorsReg {
 struct { uint32_t

 /* sorting 1 */
#define vo_lib_chroma_scaler_v_cr_scale_factors_vo_lib_chroma_scaler_v_cr_scale_factor_0_SHIFT 0
#define vo_lib_chroma_scaler_v_cr_scale_factors_vo_lib_chroma_scaler_v_cr_scale_factor_0_WIDTH 16

 vo_lib_chroma_scaler_v_cr_scale_factor_0:16, /*[15:0]  */
 hole0:16;
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_v_cr_confReg {
 struct { uint32_t

 /* sorting 4 */
#define vo_lib_chroma_scaler_v_cr_conf_output_size_SHIFT 0
#define vo_lib_chroma_scaler_v_cr_conf_output_size_WIDTH 12
#define vo_lib_chroma_scaler_v_cr_conf_taps_minus_1_SHIFT 16
#define vo_lib_chroma_scaler_v_cr_conf_taps_minus_1_WIDTH 4
#define vo_lib_chroma_scaler_v_cr_conf_phases_minus_1_SHIFT 20
#define vo_lib_chroma_scaler_v_cr_conf_phases_minus_1_WIDTH 4
#define vo_lib_chroma_scaler_v_cr_conf_init_phase_SHIFT 24
#define vo_lib_chroma_scaler_v_cr_conf_init_phase_WIDTH 5

 output_size:12, /*[11:0]  */
 hole0:4,
 taps_minus_1:4, /*[19:16]  */
 phases_minus_1:4, /*[23:20]  */
 init_phase:5, /*[28:24]  */
 hole1:3;
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_v_cr_coefficient_8_9_10_11Reg {
 struct { uint32_t

 /* sorting 4 */
#define vo_lib_chroma_scaler_v_cr_coefficient_8_9_10_11__8_SHIFT 0
#define vo_lib_chroma_scaler_v_cr_coefficient_8_9_10_11__8_WIDTH 8
#define vo_lib_chroma_scaler_v_cr_coefficient_8_9_10_11__9_SHIFT 8
#define vo_lib_chroma_scaler_v_cr_coefficient_8_9_10_11__9_WIDTH 8
#define vo_lib_chroma_scaler_v_cr_coefficient_8_9_10_11__10_SHIFT 16
#define vo_lib_chroma_scaler_v_cr_coefficient_8_9_10_11__10_WIDTH 8
#define vo_lib_chroma_scaler_v_cr_coefficient_8_9_10_11__11_SHIFT 24
#define vo_lib_chroma_scaler_v_cr_coefficient_8_9_10_11__11_WIDTH 8

 _8:8, /*[7:0]  */
 _9:8, /*[15:8]  */
 _10:8, /*[23:16]  */
 _11:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_v_cr_coefficient_4_5_6_7Reg {
 struct { uint32_t

 /* sorting 4 */
#define vo_lib_chroma_scaler_v_cr_coefficient_4_5_6_7__4_SHIFT 0
#define vo_lib_chroma_scaler_v_cr_coefficient_4_5_6_7__4_WIDTH 8
#define vo_lib_chroma_scaler_v_cr_coefficient_4_5_6_7__5_SHIFT 8
#define vo_lib_chroma_scaler_v_cr_coefficient_4_5_6_7__5_WIDTH 8
#define vo_lib_chroma_scaler_v_cr_coefficient_4_5_6_7__6_SHIFT 16
#define vo_lib_chroma_scaler_v_cr_coefficient_4_5_6_7__6_WIDTH 8
#define vo_lib_chroma_scaler_v_cr_coefficient_4_5_6_7__7_SHIFT 24
#define vo_lib_chroma_scaler_v_cr_coefficient_4_5_6_7__7_WIDTH 8

 _4:8, /*[7:0]  */
 _5:8, /*[15:8]  */
 _6:8, /*[23:16]  */
 _7:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_v_cr_coefficient_12_13_14_15Reg {
 struct { uint32_t

 /* sorting 4 */
#define vo_lib_chroma_scaler_v_cr_coefficient_12_13_14_15__12_SHIFT 0
#define vo_lib_chroma_scaler_v_cr_coefficient_12_13_14_15__12_WIDTH 8
#define vo_lib_chroma_scaler_v_cr_coefficient_12_13_14_15__13_SHIFT 8
#define vo_lib_chroma_scaler_v_cr_coefficient_12_13_14_15__13_WIDTH 8
#define vo_lib_chroma_scaler_v_cr_coefficient_12_13_14_15__14_SHIFT 16
#define vo_lib_chroma_scaler_v_cr_coefficient_12_13_14_15__14_WIDTH 8
#define vo_lib_chroma_scaler_v_cr_coefficient_12_13_14_15__15_SHIFT 24
#define vo_lib_chroma_scaler_v_cr_coefficient_12_13_14_15__15_WIDTH 8

 _12:8, /*[7:0]  */
 _13:8, /*[15:8]  */
 _14:8, /*[23:16]  */
 _15:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_v_cr_coefficient_0_1_2_3Reg {
 struct { uint32_t

 /* sorting 4 */
#define vo_lib_chroma_scaler_v_cr_coefficient_0_1_2_3__0_SHIFT 0
#define vo_lib_chroma_scaler_v_cr_coefficient_0_1_2_3__0_WIDTH 8
#define vo_lib_chroma_scaler_v_cr_coefficient_0_1_2_3__1_SHIFT 8
#define vo_lib_chroma_scaler_v_cr_coefficient_0_1_2_3__1_WIDTH 8
#define vo_lib_chroma_scaler_v_cr_coefficient_0_1_2_3__2_SHIFT 16
#define vo_lib_chroma_scaler_v_cr_coefficient_0_1_2_3__2_WIDTH 8
#define vo_lib_chroma_scaler_v_cr_coefficient_0_1_2_3__3_SHIFT 24
#define vo_lib_chroma_scaler_v_cr_coefficient_0_1_2_3__3_WIDTH 8

 _0:8, /*[7:0]  */
 _1:8, /*[15:8]  */
 _2:8, /*[23:16]  */
 _3:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_v_cb_scale_factorsReg {
 struct { uint32_t

 /* sorting 1 */
#define vo_lib_chroma_scaler_v_cb_scale_factors_vo_lib_chroma_scaler_v_cb_scale_factor_0_SHIFT 0
#define vo_lib_chroma_scaler_v_cb_scale_factors_vo_lib_chroma_scaler_v_cb_scale_factor_0_WIDTH 16

 vo_lib_chroma_scaler_v_cb_scale_factor_0:16, /*[15:0]  */
 hole0:16;
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_v_cb_confReg {
 struct { uint32_t

 /* sorting 4 */
#define vo_lib_chroma_scaler_v_cb_conf_output_size_SHIFT 0
#define vo_lib_chroma_scaler_v_cb_conf_output_size_WIDTH 12
#define vo_lib_chroma_scaler_v_cb_conf_taps_minus_1_SHIFT 16
#define vo_lib_chroma_scaler_v_cb_conf_taps_minus_1_WIDTH 4
#define vo_lib_chroma_scaler_v_cb_conf_phases_minus_1_SHIFT 20
#define vo_lib_chroma_scaler_v_cb_conf_phases_minus_1_WIDTH 4
#define vo_lib_chroma_scaler_v_cb_conf_init_phase_SHIFT 24
#define vo_lib_chroma_scaler_v_cb_conf_init_phase_WIDTH 5

 output_size:12, /*[11:0]  */
 hole0:4,
 taps_minus_1:4, /*[19:16]  */
 phases_minus_1:4, /*[23:20]  */
 init_phase:5, /*[28:24]  */
 hole1:3;
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_v_cb_coefficient_8_9_10_11Reg {
 struct { uint32_t

 /* sorting 4 */
#define vo_lib_chroma_scaler_v_cb_coefficient_8_9_10_11__8_SHIFT 0
#define vo_lib_chroma_scaler_v_cb_coefficient_8_9_10_11__8_WIDTH 8
#define vo_lib_chroma_scaler_v_cb_coefficient_8_9_10_11__9_SHIFT 8
#define vo_lib_chroma_scaler_v_cb_coefficient_8_9_10_11__9_WIDTH 8
#define vo_lib_chroma_scaler_v_cb_coefficient_8_9_10_11__10_SHIFT 16
#define vo_lib_chroma_scaler_v_cb_coefficient_8_9_10_11__10_WIDTH 8
#define vo_lib_chroma_scaler_v_cb_coefficient_8_9_10_11__11_SHIFT 24
#define vo_lib_chroma_scaler_v_cb_coefficient_8_9_10_11__11_WIDTH 8

 _8:8, /*[7:0]  */
 _9:8, /*[15:8]  */
 _10:8, /*[23:16]  */
 _11:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_v_cb_coefficient_4_5_6_7Reg {
 struct { uint32_t

 /* sorting 4 */
#define vo_lib_chroma_scaler_v_cb_coefficient_4_5_6_7__4_SHIFT 0
#define vo_lib_chroma_scaler_v_cb_coefficient_4_5_6_7__4_WIDTH 8
#define vo_lib_chroma_scaler_v_cb_coefficient_4_5_6_7__5_SHIFT 8
#define vo_lib_chroma_scaler_v_cb_coefficient_4_5_6_7__5_WIDTH 8
#define vo_lib_chroma_scaler_v_cb_coefficient_4_5_6_7__6_SHIFT 16
#define vo_lib_chroma_scaler_v_cb_coefficient_4_5_6_7__6_WIDTH 8
#define vo_lib_chroma_scaler_v_cb_coefficient_4_5_6_7__7_SHIFT 24
#define vo_lib_chroma_scaler_v_cb_coefficient_4_5_6_7__7_WIDTH 8

 _4:8, /*[7:0]  */
 _5:8, /*[15:8]  */
 _6:8, /*[23:16]  */
 _7:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_v_cb_coefficient_12_13_14_15Reg {
 struct { uint32_t

 /* sorting 4 */
#define vo_lib_chroma_scaler_v_cb_coefficient_12_13_14_15__12_SHIFT 0
#define vo_lib_chroma_scaler_v_cb_coefficient_12_13_14_15__12_WIDTH 8
#define vo_lib_chroma_scaler_v_cb_coefficient_12_13_14_15__13_SHIFT 8
#define vo_lib_chroma_scaler_v_cb_coefficient_12_13_14_15__13_WIDTH 8
#define vo_lib_chroma_scaler_v_cb_coefficient_12_13_14_15__14_SHIFT 16
#define vo_lib_chroma_scaler_v_cb_coefficient_12_13_14_15__14_WIDTH 8
#define vo_lib_chroma_scaler_v_cb_coefficient_12_13_14_15__15_SHIFT 24
#define vo_lib_chroma_scaler_v_cb_coefficient_12_13_14_15__15_WIDTH 8

 _12:8, /*[7:0]  */
 _13:8, /*[15:8]  */
 _14:8, /*[23:16]  */
 _15:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_v_cb_coefficient_0_1_2_3Reg {
 struct { uint32_t

 /* sorting 4 */
#define vo_lib_chroma_scaler_v_cb_coefficient_0_1_2_3__0_SHIFT 0
#define vo_lib_chroma_scaler_v_cb_coefficient_0_1_2_3__0_WIDTH 8
#define vo_lib_chroma_scaler_v_cb_coefficient_0_1_2_3__1_SHIFT 8
#define vo_lib_chroma_scaler_v_cb_coefficient_0_1_2_3__1_WIDTH 8
#define vo_lib_chroma_scaler_v_cb_coefficient_0_1_2_3__2_SHIFT 16
#define vo_lib_chroma_scaler_v_cb_coefficient_0_1_2_3__2_WIDTH 8
#define vo_lib_chroma_scaler_v_cb_coefficient_0_1_2_3__3_SHIFT 24
#define vo_lib_chroma_scaler_v_cb_coefficient_0_1_2_3__3_WIDTH 8

 _0:8, /*[7:0]  */
 _1:8, /*[15:8]  */
 _2:8, /*[23:16]  */
 _3:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_output_formatReg {
 struct { uint32_t

 /* sorting 1 */
#define vo_lib_chroma_scaler_output_format_vo_lib_chroma_scaler_output_format_submode_SHIFT 0
#define vo_lib_chroma_scaler_output_format_vo_lib_chroma_scaler_output_format_submode_WIDTH 2

 vo_lib_chroma_scaler_output_format_submode:2, /*[1:0]  */
 hole0:30;
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_input_formatReg {
 struct { uint32_t

 /* sorting 1 */
#define vo_lib_chroma_scaler_input_format_vo_lib_chroma_scaler_input_format_submode_SHIFT 0
#define vo_lib_chroma_scaler_input_format_vo_lib_chroma_scaler_input_format_submode_WIDTH 2

 vo_lib_chroma_scaler_input_format_submode:2, /*[1:0]  */
 hole0:30;
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_h_scale_factorsReg {
 struct { uint32_t

 /* sorting 1 */
#define vo_lib_chroma_scaler_h_scale_factors_vo_lib_chroma_scaler_h_scale_factor_0_SHIFT 0
#define vo_lib_chroma_scaler_h_scale_factors_vo_lib_chroma_scaler_h_scale_factor_0_WIDTH 16

 vo_lib_chroma_scaler_h_scale_factor_0:16, /*[15:0]  */
 hole0:16;
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_h_processReg {
 struct { uint32_t

 /* sorting 3 */
#define vo_lib_chroma_scaler_h_process_type_SHIFT 0
#define vo_lib_chroma_scaler_h_process_type_WIDTH 1
#define vo_lib_chroma_scaler_h_process_drop_pattern_SHIFT 8
#define vo_lib_chroma_scaler_h_process_drop_pattern_WIDTH 8
#define vo_lib_chroma_scaler_h_process_out_size_SHIFT 16
#define vo_lib_chroma_scaler_h_process_out_size_WIDTH 12

 type:1, /*[0:0]  */
 hole0:7,
 drop_pattern:8, /*[15:8]  */
 out_size:12, /*[27:16]  */
 hole1:4;
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_h_confReg {
 struct { uint32_t

 /* sorting 4 */
#define vo_lib_chroma_scaler_h_conf_output_size_SHIFT 0
#define vo_lib_chroma_scaler_h_conf_output_size_WIDTH 12
#define vo_lib_chroma_scaler_h_conf_taps_minus_1_SHIFT 16
#define vo_lib_chroma_scaler_h_conf_taps_minus_1_WIDTH 4
#define vo_lib_chroma_scaler_h_conf_phases_minus_1_SHIFT 20
#define vo_lib_chroma_scaler_h_conf_phases_minus_1_WIDTH 4
#define vo_lib_chroma_scaler_h_conf_init_phase_SHIFT 24
#define vo_lib_chroma_scaler_h_conf_init_phase_WIDTH 5

 output_size:12, /*[11:0]  */
 hole0:4,
 taps_minus_1:4, /*[19:16]  */
 phases_minus_1:4, /*[23:20]  */
 init_phase:5, /*[28:24]  */
 hole1:3;
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_h_coefficient_8_9_10_11Reg {
 struct { uint32_t

 /* sorting 4 */
#define vo_lib_chroma_scaler_h_coefficient_8_9_10_11__8_SHIFT 0
#define vo_lib_chroma_scaler_h_coefficient_8_9_10_11__8_WIDTH 8
#define vo_lib_chroma_scaler_h_coefficient_8_9_10_11__9_SHIFT 8
#define vo_lib_chroma_scaler_h_coefficient_8_9_10_11__9_WIDTH 8
#define vo_lib_chroma_scaler_h_coefficient_8_9_10_11__10_SHIFT 16
#define vo_lib_chroma_scaler_h_coefficient_8_9_10_11__10_WIDTH 8
#define vo_lib_chroma_scaler_h_coefficient_8_9_10_11__11_SHIFT 24
#define vo_lib_chroma_scaler_h_coefficient_8_9_10_11__11_WIDTH 8

 _8:8, /*[7:0]  */
 _9:8, /*[15:8]  */
 _10:8, /*[23:16]  */
 _11:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_h_coefficient_4_5_6_7Reg {
 struct { uint32_t

 /* sorting 4 */
#define vo_lib_chroma_scaler_h_coefficient_4_5_6_7__4_SHIFT 0
#define vo_lib_chroma_scaler_h_coefficient_4_5_6_7__4_WIDTH 8
#define vo_lib_chroma_scaler_h_coefficient_4_5_6_7__5_SHIFT 8
#define vo_lib_chroma_scaler_h_coefficient_4_5_6_7__5_WIDTH 8
#define vo_lib_chroma_scaler_h_coefficient_4_5_6_7__6_SHIFT 16
#define vo_lib_chroma_scaler_h_coefficient_4_5_6_7__6_WIDTH 8
#define vo_lib_chroma_scaler_h_coefficient_4_5_6_7__7_SHIFT 24
#define vo_lib_chroma_scaler_h_coefficient_4_5_6_7__7_WIDTH 8

 _4:8, /*[7:0]  */
 _5:8, /*[15:8]  */
 _6:8, /*[23:16]  */
 _7:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_h_coefficient_12_13_14_15Reg {
 struct { uint32_t

 /* sorting 4 */
#define vo_lib_chroma_scaler_h_coefficient_12_13_14_15__12_SHIFT 0
#define vo_lib_chroma_scaler_h_coefficient_12_13_14_15__12_WIDTH 8
#define vo_lib_chroma_scaler_h_coefficient_12_13_14_15__13_SHIFT 8
#define vo_lib_chroma_scaler_h_coefficient_12_13_14_15__13_WIDTH 8
#define vo_lib_chroma_scaler_h_coefficient_12_13_14_15__14_SHIFT 16
#define vo_lib_chroma_scaler_h_coefficient_12_13_14_15__14_WIDTH 8
#define vo_lib_chroma_scaler_h_coefficient_12_13_14_15__15_SHIFT 24
#define vo_lib_chroma_scaler_h_coefficient_12_13_14_15__15_WIDTH 8

 _12:8, /*[7:0]  */
 _13:8, /*[15:8]  */
 _14:8, /*[23:16]  */
 _15:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_h_coefficient_0_1_2_3Reg {
 struct { uint32_t

 /* sorting 4 */
#define vo_lib_chroma_scaler_h_coefficient_0_1_2_3__0_SHIFT 0
#define vo_lib_chroma_scaler_h_coefficient_0_1_2_3__0_WIDTH 8
#define vo_lib_chroma_scaler_h_coefficient_0_1_2_3__1_SHIFT 8
#define vo_lib_chroma_scaler_h_coefficient_0_1_2_3__1_WIDTH 8
#define vo_lib_chroma_scaler_h_coefficient_0_1_2_3__2_SHIFT 16
#define vo_lib_chroma_scaler_h_coefficient_0_1_2_3__2_WIDTH 8
#define vo_lib_chroma_scaler_h_coefficient_0_1_2_3__3_SHIFT 24
#define vo_lib_chroma_scaler_h_coefficient_0_1_2_3__3_WIDTH 8

 _0:8, /*[7:0]  */
 _1:8, /*[15:8]  */
 _2:8, /*[23:16]  */
 _3:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_lib_chroma_scaler_alphaReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_lib_chroma_scaler_alpha_a0_SHIFT 0
#define vo_lib_chroma_scaler_alpha_a0_WIDTH 8
#define vo_lib_chroma_scaler_alpha_a_enable_SHIFT 16
#define vo_lib_chroma_scaler_alpha_a_enable_WIDTH 1

 a0:8, /*[7:0]  */
 hole0:8,
 a_enable:1, /*[16:16]  */
 hole1:15;
 } bits;

 uint32_t value;
};

struct vo_lib_chroma_scaler {
 union vo_lib_chroma_scaler_h_confReg vo_lib_chroma_scaler_h_conf; /* +0x00000000  */
 union vo_lib_chroma_scaler_h_scale_factorsReg vo_lib_chroma_scaler_h_scale_factors; /* +0x00000004  */
 uint32_t pad0[0x0018/4];
 union vo_lib_chroma_scaler_h_coefficient_0_1_2_3Reg vo_lib_chroma_scaler_h_coefficient_0_1_2_3; /* +0x00000020  */
 union vo_lib_chroma_scaler_h_coefficient_4_5_6_7Reg vo_lib_chroma_scaler_h_coefficient_4_5_6_7; /* +0x00000024  */
 union vo_lib_chroma_scaler_h_coefficient_8_9_10_11Reg vo_lib_chroma_scaler_h_coefficient_8_9_10_11; /* +0x00000028  */
 union vo_lib_chroma_scaler_h_coefficient_12_13_14_15Reg vo_lib_chroma_scaler_h_coefficient_12_13_14_15; /* +0x0000002c  */
 uint32_t pad1[0x0050/4];
 union vo_lib_chroma_scaler_v_cb_confReg vo_lib_chroma_scaler_v_cb_conf; /* +0x00000080  */
 union vo_lib_chroma_scaler_v_cb_scale_factorsReg vo_lib_chroma_scaler_v_cb_scale_factors; /* +0x00000084  */
 uint32_t pad2[0x0018/4];
 union vo_lib_chroma_scaler_v_cb_coefficient_0_1_2_3Reg vo_lib_chroma_scaler_v_cb_coefficient_0_1_2_3; /* +0x000000a0  */
 union vo_lib_chroma_scaler_v_cb_coefficient_4_5_6_7Reg vo_lib_chroma_scaler_v_cb_coefficient_4_5_6_7; /* +0x000000a4  */
 union vo_lib_chroma_scaler_v_cb_coefficient_8_9_10_11Reg vo_lib_chroma_scaler_v_cb_coefficient_8_9_10_11; /* +0x000000a8  */
 union vo_lib_chroma_scaler_v_cb_coefficient_12_13_14_15Reg vo_lib_chroma_scaler_v_cb_coefficient_12_13_14_15; /* +0x000000ac  */
 uint32_t pad3[0x0050/4];
 union vo_lib_chroma_scaler_v_cr_confReg vo_lib_chroma_scaler_v_cr_conf; /* +0x00000100  */
 union vo_lib_chroma_scaler_v_cr_scale_factorsReg vo_lib_chroma_scaler_v_cr_scale_factors; /* +0x00000104  */
 uint32_t pad4[0x0018/4];
 union vo_lib_chroma_scaler_v_cr_coefficient_0_1_2_3Reg vo_lib_chroma_scaler_v_cr_coefficient_0_1_2_3; /* +0x00000120  */
 union vo_lib_chroma_scaler_v_cr_coefficient_4_5_6_7Reg vo_lib_chroma_scaler_v_cr_coefficient_4_5_6_7; /* +0x00000124  */
 union vo_lib_chroma_scaler_v_cr_coefficient_8_9_10_11Reg vo_lib_chroma_scaler_v_cr_coefficient_8_9_10_11; /* +0x00000128  */
 union vo_lib_chroma_scaler_v_cr_coefficient_12_13_14_15Reg vo_lib_chroma_scaler_v_cr_coefficient_12_13_14_15; /* +0x0000012c  */
 uint32_t pad5[0x0050/4];
 union vo_lib_chroma_scaler_input_formatReg vo_lib_chroma_scaler_input_format; /* +0x00000180  */
 union vo_lib_chroma_scaler_output_formatReg vo_lib_chroma_scaler_output_format; /* +0x00000184  */
 union vo_lib_chroma_scaler_alphaReg vo_lib_chroma_scaler_alpha; /* +0x00000188  */
 union vo_lib_chroma_scaler_h_processReg vo_lib_chroma_scaler_h_process; /* +0x0000018c  */
 union vo_lib_chroma_scaler_v_processReg vo_lib_chroma_scaler_v_process; /* +0x00000190  */
};
