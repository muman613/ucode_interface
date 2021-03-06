/* autogenerated with parsecfg: do not edit. */

/* gotta drop vo_gacc_X_format_discard_end@vo_gacc_X_format: 0x0000fcff [15:13] */
/* gotta drop vo_gacc_X_format_discard_begin@vo_gacc_X_format: 0x0000fcff [12:10] */
/* gotta drop vo_gacc_Y_format_discard_end@vo_gacc_Y_format: 0x0000ffff [15:13] */
/* gotta drop vo_gacc_Y_format_discard_begin@vo_gacc_Y_format: 0x0000ffff [12:10] */
/* gotta drop vo_gacc_control_src_ctrl@vo_gacc_control: 0x000007c7 [8:8] */
/* gotta drop vo_gacc_control_merge_ctrl@vo_gacc_control: 0x000007c7 [9:9] */
/* gotta drop vo_gacc_control_alpha_sat@vo_gacc_control: 0x000007c7 [10:10] */
union vo_gacc_scaling_and_contoursReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_gacc_scaling_and_contours_scaling_SHIFT 0
#define vo_gacc_scaling_and_contours_scaling_WIDTH 19
#define vo_gacc_scaling_and_contours_contours_SHIFT 19
#define vo_gacc_scaling_and_contours_contours_WIDTH 9

 scaling:19, /*[18:0]  */
 contours:9, /*[27:19]  */
 hole0:4;
 } bits;

 uint32_t value;
};

union vo_gacc_mode_controlReg {
 struct { uint32_t

 /* sorting 4 */
#define vo_gacc_mode_control_data_source_SHIFT 4
#define vo_gacc_mode_control_data_source_WIDTH 1
#define vo_gacc_mode_control_dropout_SHIFT 8
#define vo_gacc_mode_control_dropout_WIDTH 1
#define vo_gacc_mode_control_tiled_SHIFT 12
#define vo_gacc_mode_control_tiled_WIDTH 1
#define vo_gacc_mode_control_read_data_length_SHIFT 16
#define vo_gacc_mode_control_read_data_length_WIDTH 11

 hole0:4,
 data_source:1, /*[4:4]  */
 hole1:3,
 dropout:1, /*[8:8]  */
 hole2:3,
 tiled:1, /*[12:12]  */
 hole3:3,
 read_data_length:11, /*[26:16]  */
 hole4:5;
 } bits;

 uint32_t value;
};

union vo_gacc_matrix_coeffs_scale_YX_XYReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_gacc_matrix_coeffs_scale_YX_XY_XY_SHIFT 0
#define vo_gacc_matrix_coeffs_scale_YX_XY_XY_WIDTH 16
#define vo_gacc_matrix_coeffs_scale_YX_XY_YX_SHIFT 16
#define vo_gacc_matrix_coeffs_scale_YX_XY_YX_WIDTH 16

 xy:16, /*[15:0]  */
 yx:16; /*[31:16]  */
 } bits;

 uint32_t value;
};

union vo_gacc_matrix_coeffs_scale_X_YReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_gacc_matrix_coeffs_scale_X_Y_X_SHIFT 0
#define vo_gacc_matrix_coeffs_scale_X_Y_X_WIDTH 16
#define vo_gacc_matrix_coeffs_scale_X_Y_Y_SHIFT 16
#define vo_gacc_matrix_coeffs_scale_X_Y_Y_WIDTH 16

 x:16, /*[15:0]  */
 y:16; /*[31:16]  */
 } bits;

 uint32_t value;
};

union vo_gacc_matrix_coeffs_offsetReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_gacc_matrix_coeffs_offset_X_SHIFT 0
#define vo_gacc_matrix_coeffs_offset_X_WIDTH 16
#define vo_gacc_matrix_coeffs_offset_Y_SHIFT 16
#define vo_gacc_matrix_coeffs_offset_Y_WIDTH 16

 x:16, /*[15:0]  */
 y:16; /*[31:16]  */
 } bits;

 uint32_t value;
};

union vo_gacc_grd_controlReg {
 struct { uint32_t

 /* sorting 7 */
#define vo_gacc_grd_control_mode_SHIFT 0
#define vo_gacc_grd_control_mode_WIDTH 1
#define vo_gacc_grd_control_ll_SHIFT 1
#define vo_gacc_grd_control_ll_WIDTH 1
#define vo_gacc_grd_control_alpha_ext_SHIFT 2
#define vo_gacc_grd_control_alpha_ext_WIDTH 1
#define vo_gacc_grd_control_alpha_int_SHIFT 3
#define vo_gacc_grd_control_alpha_int_WIDTH 1
#define vo_gacc_grd_control_use_weave_SHIFT 4
#define vo_gacc_grd_control_use_weave_WIDTH 4
#define vo_gacc_grd_control_parity_init_SHIFT 8
#define vo_gacc_grd_control_parity_init_WIDTH 1
#define vo_gacc_grd_control_width_SHIFT 16
#define vo_gacc_grd_control_width_WIDTH 12

 mode:1, /*[0:0]  */
 ll:1, /*[1:1]  */
 alpha_ext:1, /*[2:2]  */
 alpha_int:1, /*[3:3]  */
 use_weave:4, /*[7:4]  */
 parity_init:1, /*[8:8]  */
 hole0:7,
 width:12, /*[27:16]  */
 hole1:4;
 } bits;

 uint32_t value;
};

union vo_gacc_grd_centerReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_gacc_grd_center_x_SHIFT 0
#define vo_gacc_grd_center_x_WIDTH 12
#define vo_gacc_grd_center_y_SHIFT 16
#define vo_gacc_grd_center_y_WIDTH 12

 x:12, /*[11:0]  */
 hole0:4,
 y:12, /*[27:16]  */
 hole1:4;
 } bits;

 uint32_t value;
};

union vo_gacc_control3Reg {
 struct { uint32_t

 /* sorting 1 */
#define vo_gacc_control3_vo_gacc_control3_replace_mod_SHIFT 0
#define vo_gacc_control3_vo_gacc_control3_replace_mod_WIDTH 5

 vo_gacc_control3_replace_mod:5, /*[4:0]  */
 hole0:27;
 } bits;

 uint32_t value;
};

union vo_gacc_control2Reg {
 struct { uint32_t

 /* sorting 9 */
#define vo_gacc_control2_blend_order_SHIFT 0
#define vo_gacc_control2_blend_order_WIDTH 3
#define vo_gacc_control2_ac_SHIFT 3
#define vo_gacc_control2_ac_WIDTH 1
#define vo_gacc_control2_cc_SHIFT 4
#define vo_gacc_control2_cc_WIDTH 1
#define vo_gacc_control2_dith_cs_SHIFT 5
#define vo_gacc_control2_dith_cs_WIDTH 2
#define vo_gacc_control2_clip_ctrl_SHIFT 7
#define vo_gacc_control2_clip_ctrl_WIDTH 1
#define vo_gacc_control2_fb_SHIFT 8
#define vo_gacc_control2_fb_WIDTH 1
#define vo_gacc_control2_a_src_SHIFT 9
#define vo_gacc_control2_a_src_WIDTH 2
#define vo_gacc_control2_dvpal_ysize_SHIFT 12
#define vo_gacc_control2_dvpal_ysize_WIDTH 11
#define vo_gacc_control2_dvpal_ctrl_SHIFT 23
#define vo_gacc_control2_dvpal_ctrl_WIDTH 9

 blend_order:3, /*[2:0]  */
 ac:1, /*[3:3]  */
 cc:1, /*[4:4]  */
 dith_cs:2, /*[6:5]  */
 clip_ctrl:1, /*[7:7]  */
 fb:1, /*[8:8]  */
 a_src:2, /*[10:9]  */
 hole0:1,
 dvpal_ysize:11, /*[22:12]  */
 dvpal_ctrl:9; /*[31:23]  */
 } bits;

 uint32_t value;
};

union vo_gacc_controlReg {
 struct { uint32_t

 /* sorting 10 */
#define vo_gacc_control_cmd_ctrl_SHIFT 0
#define vo_gacc_control_cmd_ctrl_WIDTH 3
#define vo_gacc_control_ge_SHIFT 6
#define vo_gacc_control_ge_WIDTH 1
#define vo_gacc_control_ve_SHIFT 7
#define vo_gacc_control_ve_WIDTH 1
#define vo_gacc_control_data_ctrl_SHIFT 8
#define vo_gacc_control_data_ctrl_WIDTH 3
#define vo_gacc_control_output_format_SHIFT 11
#define vo_gacc_control_output_format_WIDTH 2
#define vo_gacc_control_dithering_control_SHIFT 13
#define vo_gacc_control_dithering_control_WIDTH 2
#define vo_gacc_control_merge_modulate_SHIFT 15
#define vo_gacc_control_merge_modulate_WIDTH 1
#define vo_gacc_control_raster_op_SHIFT 16
#define vo_gacc_control_raster_op_WIDTH 8
#define vo_gacc_control_raster_sub_format_SHIFT 24
#define vo_gacc_control_raster_sub_format_WIDTH 2
#define vo_gacc_control_raster_chanel_SHIFT 26
#define vo_gacc_control_raster_chanel_WIDTH 6

 cmd_ctrl:3, /*[2:0]  */
 hole0:3,
 ge:1, /*[6:6]  */
 ve:1, /*[7:7]  */
 data_ctrl:3, /*[10:8]  */
 output_format:2, /*[12:11]  */
 dithering_control:2, /*[14:13]  */
 merge_modulate:1, /*[15:15]  */
 raster_op:8, /*[23:16]  */
 raster_sub_format:2, /*[25:24]  */
 raster_chanel:6; /*[31:26]  */
 } bits;

 uint32_t value;
};

union vo_gacc_Y_keycolorReg {
 struct { uint32_t

 /* sorting 3 */
#define vo_gacc_Y_keycolor_keycolor_SHIFT 0
#define vo_gacc_Y_keycolor_keycolor_WIDTH 24
#define vo_gacc_Y_keycolor_range_SHIFT 24
#define vo_gacc_Y_keycolor_range_WIDTH 5
#define vo_gacc_Y_keycolor_ac_SHIFT 31
#define vo_gacc_Y_keycolor_ac_WIDTH 1

 keycolor:24, /*[23:0]  */
 range:5, /*[28:24]  */
 hole0:2,
 ac:1; /*[31:31]  */
 } bits;

 uint32_t value;
};

union vo_gacc_Y_formatReg {
 struct { uint32_t

 /* sorting 9 */
#define vo_gacc_Y_format__mode_SHIFT 0
#define vo_gacc_Y_format__mode_WIDTH 3
#define vo_gacc_Y_format__sub_mode_SHIFT 3
#define vo_gacc_Y_format__sub_mode_WIDTH 3
#define vo_gacc_Y_format__422_SHIFT 6
#define vo_gacc_Y_format__422_WIDTH 1
#define vo_gacc_Y_format__alpha_gamma_SHIFT 7
#define vo_gacc_Y_format__alpha_gamma_WIDTH 1
#define vo_gacc_Y_format__gamma_SHIFT 8
#define vo_gacc_Y_format__gamma_WIDTH 1
#define vo_gacc_Y_format__fe_SHIFT 9
#define vo_gacc_Y_format__fe_WIDTH 1
#define vo_gacc_Y_format__discard_SHIFT 10
#define vo_gacc_Y_format__discard_WIDTH 6
#define vo_gacc_Y_format__alpha_0_SHIFT 16
#define vo_gacc_Y_format__alpha_0_WIDTH 8
#define vo_gacc_Y_format__alpha_1_SHIFT 24
#define vo_gacc_Y_format__alpha_1_WIDTH 8

 _mode:3, /*[2:0]  */
 _sub_mode:3, /*[5:3]  */
 _422:1, /*[6:6]  */
 _alpha_gamma:1, /*[7:7]  */
 _gamma:1, /*[8:8]  */
 _fe:1, /*[9:9]  */
 _discard:6, /*[15:10]  */
 _alpha_0:8, /*[23:16]  */
 _alpha_1:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_gacc_Y_bounding_boxReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_gacc_Y_bounding_box_in_SHIFT 0
#define vo_gacc_Y_bounding_box_in_WIDTH 16
#define vo_gacc_Y_bounding_box_ax_SHIFT 16
#define vo_gacc_Y_bounding_box_ax_WIDTH 16

 in:16, /*[15:0]  */
 ax:16; /*[31:16]  */
 } bits;

 uint32_t value;
};

union vo_gacc_X_keycolorReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_gacc_X_keycolor_keycolor_SHIFT 0
#define vo_gacc_X_keycolor_keycolor_WIDTH 24
#define vo_gacc_X_keycolor_range_SHIFT 24
#define vo_gacc_X_keycolor_range_WIDTH 5

 keycolor:24, /*[23:0]  */
 range:5, /*[28:24]  */
 hole0:3;
 } bits;

 uint32_t value;
};

union vo_gacc_X_formatReg {
 struct { uint32_t

 /* sorting 5 */
#define vo_gacc_X_format__mode_SHIFT 0
#define vo_gacc_X_format__mode_WIDTH 3
#define vo_gacc_X_format__sub_mode_SHIFT 3
#define vo_gacc_X_format__sub_mode_WIDTH 3
#define vo_gacc_X_format__422_SHIFT 6
#define vo_gacc_X_format__422_WIDTH 1
#define vo_gacc_X_format__ac_SHIFT 7
#define vo_gacc_X_format__ac_WIDTH 1
#define vo_gacc_X_format__discard_SHIFT 10
#define vo_gacc_X_format__discard_WIDTH 6

 _mode:3, /*[2:0]  */
 _sub_mode:3, /*[5:3]  */
 _422:1, /*[6:6]  */
 _ac:1, /*[7:7]  */
 hole0:2,
 _discard:6, /*[15:10]  */
 hole1:16;
 } bits;

 uint32_t value;
};

union vo_gacc_X_bounding_boxReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_gacc_X_bounding_box_in_SHIFT 0
#define vo_gacc_X_bounding_box_in_WIDTH 16
#define vo_gacc_X_bounding_box_ax_SHIFT 16
#define vo_gacc_X_bounding_box_ax_WIDTH 16

 in:16, /*[15:0]  */
 ax:16; /*[31:16]  */
 } bits;

 uint32_t value;
};

union vo_gacc_X_alpha_or_fillReg {
 struct { uint32_t

 /* sorting 4 */
#define vo_gacc_X_alpha_or_fill__0_SHIFT 0
#define vo_gacc_X_alpha_or_fill__0_WIDTH 8
#define vo_gacc_X_alpha_or_fill__1_SHIFT 8
#define vo_gacc_X_alpha_or_fill__1_WIDTH 8
#define vo_gacc_X_alpha_or_fill__2_SHIFT 16
#define vo_gacc_X_alpha_or_fill__2_WIDTH 8
#define vo_gacc_X_alpha_or_fill__3_SHIFT 24
#define vo_gacc_X_alpha_or_fill__3_WIDTH 8

 _0:8, /*[7:0]  */
 _1:8, /*[15:8]  */
 _2:8, /*[23:16]  */
 _3:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

struct vo_graphic_accelerator {
 union vo_gacc_X_formatReg vo_gacc_X_format; /* +0x00000000  */
 union vo_gacc_X_alpha_or_fillReg vo_gacc_X_alpha_or_fill; /* +0x00000004  */
 union vo_gacc_X_keycolorReg vo_gacc_X_keycolor; /* +0x00000008  */
 union vo_gacc_Y_formatReg vo_gacc_Y_format; /* +0x0000000c  */
 union vo_gacc_Y_keycolorReg vo_gacc_Y_keycolor; /* +0x00000010  */
 union vo_gacc_controlReg vo_gacc_control; /* +0x00000014  */
 uint32_t pad0[0x0004/4];
 union vo_gacc_control2Reg vo_gacc_control2; /* +0x0000001c  */
 uint32_t pad1[0x0004/4];
 union vo_gacc_control3Reg vo_gacc_control3; /* +0x00000024  */
 uint32_t pad2[0x0018/4];
 uint32_t vo_gacc_grd_color0; /* +0x00000040  */
 uint32_t vo_gacc_grd_color1; /* +0x00000044  */
 uint32_t vo_gacc_grd_scale_factor; /* +0x00000048  */
 uint32_t vo_gacc_grd_vt_scale_init; /* +0x0000004c  */
 uint32_t vo_gacc_grd_init_square_dist; /* +0x00000050  */
 uint32_t vo_gacc_grd_ext_radius2; /* +0x00000054  */
 uint32_t vo_gacc_grd_int_radius2; /* +0x00000058  */
 union vo_gacc_grd_centerReg vo_gacc_grd_center; /* +0x0000005c  */
 union vo_gacc_grd_controlReg vo_gacc_grd_control; /* +0x00000060  */
 uint32_t pad3[0x001c/4];
 union vo_gacc_mode_controlReg vo_gacc_mode_control; /* +0x00000080  */
 uint32_t vo_gacc_DRAM_read_address; /* +0x00000084  */
 uint32_t vo_gacc_DRAM_write_address; /* +0x00000088  */
 union vo_gacc_X_bounding_boxReg vo_gacc_X_bounding_box; /* +0x0000008c  */
 union vo_gacc_Y_bounding_boxReg vo_gacc_Y_bounding_box; /* +0x00000090  */
 union vo_gacc_scaling_and_contoursReg vo_gacc_scaling_and_contours; /* +0x00000094  */
 union vo_gacc_matrix_coeffs_scale_X_YReg vo_gacc_matrix_coeffs_scale_X_Y; /* +0x00000098  */
 union vo_gacc_matrix_coeffs_scale_YX_XYReg vo_gacc_matrix_coeffs_scale_YX_XY; /* +0x0000009c  */
 union vo_gacc_matrix_coeffs_offsetReg vo_gacc_matrix_coeffs_offset; /* +0x000000a0  */
};
