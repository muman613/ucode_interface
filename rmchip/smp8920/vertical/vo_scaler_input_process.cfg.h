/* autogenerated with parsecfg: do not edit. */

union vo_scalinproc_keycolor_rvReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_scalinproc_keycolor_rv_color_rv_SHIFT 0
#define vo_scalinproc_keycolor_rv_color_rv_WIDTH 12
#define vo_scalinproc_keycolor_rv_range_rv_SHIFT 16
#define vo_scalinproc_keycolor_rv_range_rv_WIDTH 4

 color_rv:12, /*[11:0]  */
 hole0:4,
 range_rv:4, /*[19:16]  */
 hole1:12;
 } bits;

 uint32_t value;
};

union vo_scalinproc_keycolor_gyReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_scalinproc_keycolor_gy_color_gy_SHIFT 0
#define vo_scalinproc_keycolor_gy_color_gy_WIDTH 12
#define vo_scalinproc_keycolor_gy_range_gy_SHIFT 16
#define vo_scalinproc_keycolor_gy_range_gy_WIDTH 4

 color_gy:12, /*[11:0]  */
 hole0:4,
 range_gy:4, /*[19:16]  */
 hole1:12;
 } bits;

 uint32_t value;
};

union vo_scalinproc_keycolor_buReg {
 struct { uint32_t

 /* sorting 3 */
#define vo_scalinproc_keycolor_bu_color_bu_SHIFT 0
#define vo_scalinproc_keycolor_bu_color_bu_WIDTH 12
#define vo_scalinproc_keycolor_bu_range_bu_SHIFT 16
#define vo_scalinproc_keycolor_bu_range_bu_WIDTH 4
#define vo_scalinproc_keycolor_bu_enable_SHIFT 24
#define vo_scalinproc_keycolor_bu_enable_WIDTH 1

 color_bu:12, /*[11:0]  */
 hole0:4,
 range_bu:4, /*[19:16]  */
 hole1:4,
 enable:1, /*[24:24]  */
 hole2:7;
 } bits;

 uint32_t value;
};

union vo_scalinproc_formatReg {
 struct { uint32_t

 /* sorting 6 */
#define vo_scalinproc_format_submode_SHIFT 0
#define vo_scalinproc_format_submode_WIDTH 3
#define vo_scalinproc_format_use_lut_SHIFT 3
#define vo_scalinproc_format_use_lut_WIDTH 1
#define vo_scalinproc_format_video_SHIFT 6
#define vo_scalinproc_format_video_WIDTH 1
#define vo_scalinproc_format_discard_beg_SHIFT 8
#define vo_scalinproc_format_discard_beg_WIDTH 3
#define vo_scalinproc_format_discard_end_SHIFT 12
#define vo_scalinproc_format_discard_end_WIDTH 3
#define vo_scalinproc_format_bypass_SHIFT 16
#define vo_scalinproc_format_bypass_WIDTH 1

 submode:3, /*[2:0]  */
 use_lut:1, /*[3:3]  */
 hole0:2,
 video:1, /*[6:6]  */
 hole1:1,
 discard_beg:3, /*[10:8]  */
 hole2:1,
 discard_end:3, /*[14:12]  */
 hole3:1,
 bypass:1, /*[16:16]  */
 hole4:15;
 } bits;

 uint32_t value;
};

union vo_scalinproc_dumpReg {
 struct { uint32_t

 /* sorting 4 */
#define vo_scalinproc_dump_line_r0_SHIFT 0
#define vo_scalinproc_dump_line_r0_WIDTH 8
#define vo_scalinproc_dump_pixel_r0_SHIFT 8
#define vo_scalinproc_dump_pixel_r0_WIDTH 8
#define vo_scalinproc_dump_line_r1_SHIFT 16
#define vo_scalinproc_dump_line_r1_WIDTH 8
#define vo_scalinproc_dump_pixel_r1_SHIFT 24
#define vo_scalinproc_dump_pixel_r1_WIDTH 8

 line_r0:8, /*[7:0]  */
 pixel_r0:8, /*[15:8]  */
 line_r1:8, /*[23:16]  */
 pixel_r1:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_scalinproc_csc_fadingReg {
 struct { uint32_t

 /* sorting 3 */
#define vo_scalinproc_csc_fading_alpha0_SHIFT 0
#define vo_scalinproc_csc_fading_alpha0_WIDTH 8
#define vo_scalinproc_csc_fading_alpha1_SHIFT 8
#define vo_scalinproc_csc_fading_alpha1_WIDTH 8
#define vo_scalinproc_csc_fading_en_SHIFT 16
#define vo_scalinproc_csc_fading_en_WIDTH 1

 alpha0:8, /*[7:0]  */
 alpha1:8, /*[15:8]  */
 en:1, /*[16:16]  */
 hole0:15;
 } bits;

 uint32_t value;
};

union vo_scalinproc_connectionReg {
 struct { uint32_t

 /* sorting 8 */
#define vo_scalinproc_connection_lut_gamma_SHIFT 0
#define vo_scalinproc_connection_lut_gamma_WIDTH 2
#define vo_scalinproc_connection_en_lut_gamma_SHIFT 7
#define vo_scalinproc_connection_en_lut_gamma_WIDTH 1
#define vo_scalinproc_connection_csc_SHIFT 8
#define vo_scalinproc_connection_csc_WIDTH 2
#define vo_scalinproc_connection_en_csc_SHIFT 15
#define vo_scalinproc_connection_en_csc_WIDTH 1
#define vo_scalinproc_connection_scaler_SHIFT 16
#define vo_scalinproc_connection_scaler_WIDTH 2
#define vo_scalinproc_connection_en_scaler_SHIFT 23
#define vo_scalinproc_connection_en_scaler_WIDTH 1
#define vo_scalinproc_connection_output_SHIFT 24
#define vo_scalinproc_connection_output_WIDTH 2
#define vo_scalinproc_connection_en_output_SHIFT 31
#define vo_scalinproc_connection_en_output_WIDTH 1

 lut_gamma:2, /*[1:0]  */
 hole0:5,
 en_lut_gamma:1, /*[7:7]  */
 csc:2, /*[9:8]  */
 hole1:5,
 en_csc:1, /*[15:15]  */
 scaler:2, /*[17:16]  */
 hole2:5,
 en_scaler:1, /*[23:23]  */
 output:2, /*[25:24]  */
 hole3:5,
 en_output:1; /*[31:31]  */
 } bits;

 uint32_t value;
};

union vo_scalinproc_alphaReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_scalinproc_alpha_a0_SHIFT 0
#define vo_scalinproc_alpha_a0_WIDTH 8
#define vo_scalinproc_alpha_a1_SHIFT 8
#define vo_scalinproc_alpha_a1_WIDTH 8

 a0:8, /*[7:0]  */
 a1:8, /*[15:8]  */
 hole0:16;
 } bits;

 uint32_t value;
};

struct vo_scaler_input_process {
 uint32_t vo_scalinproc_csc_m00; /* +0x00000000  */
 uint32_t vo_scalinproc_csc_m01; /* +0x00000004  */
 uint32_t vo_scalinproc_csc_m02; /* +0x00000008  */
 uint32_t vo_scalinproc_csc_m10; /* +0x0000000c  */
 uint32_t vo_scalinproc_csc_m11; /* +0x00000010  */
 uint32_t vo_scalinproc_csc_m12; /* +0x00000014  */
 uint32_t vo_scalinproc_csc_m20; /* +0x00000018  */
 uint32_t vo_scalinproc_csc_m21; /* +0x0000001c  */
 uint32_t vo_scalinproc_csc_m22; /* +0x00000020  */
 uint32_t vo_scalinproc_csc_r0; /* +0x00000024  */
 uint32_t vo_scalinproc_csc_r1; /* +0x00000028  */
 uint32_t vo_scalinproc_csc_r2; /* +0x0000002c  */
 union vo_scalinproc_csc_fadingReg vo_scalinproc_csc_fading; /* +0x00000030  */
 uint32_t pad0[0x000c/4];
 union vo_scalinproc_formatReg vo_scalinproc_format; /* +0x00000040  */
 union vo_scalinproc_alphaReg vo_scalinproc_alpha; /* +0x00000044  */
 union vo_scalinproc_keycolor_buReg vo_scalinproc_keycolor_bu; /* +0x00000048  */
 union vo_scalinproc_keycolor_gyReg vo_scalinproc_keycolor_gy; /* +0x0000004c  */
 union vo_scalinproc_keycolor_rvReg vo_scalinproc_keycolor_rv; /* +0x00000050  */
 union vo_scalinproc_connectionReg vo_scalinproc_connection; /* +0x00000054  */
 union vo_scalinproc_dumpReg vo_scalinproc_dump; /* +0x00000058  */
};
