/* autogenerated with parsecfg: do not edit. */

union vo_vxp_de_thresholds_regReg {
 struct { uint32_t

 /* sorting 4 */
#define vo_vxp_de_thresholds_reg_noise_rejection_thresh_SHIFT 0
#define vo_vxp_de_thresholds_reg_noise_rejection_thresh_WIDTH 6
#define vo_vxp_de_thresholds_reg_texture_overshoot_thresh_SHIFT 8
#define vo_vxp_de_thresholds_reg_texture_overshoot_thresh_WIDTH 8
#define vo_vxp_de_thresholds_reg_edge_overshoot_thresh_SHIFT 16
#define vo_vxp_de_thresholds_reg_edge_overshoot_thresh_WIDTH 8
#define vo_vxp_de_thresholds_reg_texture_vs_edge_thresh_SHIFT 24
#define vo_vxp_de_thresholds_reg_texture_vs_edge_thresh_WIDTH 7

 noise_rejection_thresh:6, /*[5:0]  */
 hole0:2,
 texture_overshoot_thresh:8, /*[15:8]  */
 edge_overshoot_thresh:8, /*[23:16]  */
 texture_vs_edge_thresh:7, /*[30:24]  */
 hole1:1;
 } bits;

 uint32_t value;
};

union vo_vxp_de_texture_enhancement_levels_regReg {
 struct { uint32_t

 /* sorting 4 */
#define vo_vxp_de_texture_enhancement_levels_reg_h_SHIFT 0
#define vo_vxp_de_texture_enhancement_levels_reg_h_WIDTH 6
#define vo_vxp_de_texture_enhancement_levels_reg_v_SHIFT 8
#define vo_vxp_de_texture_enhancement_levels_reg_v_WIDTH 6
#define vo_vxp_de_texture_enhancement_levels_reg_d_SHIFT 16
#define vo_vxp_de_texture_enhancement_levels_reg_d_WIDTH 6
#define vo_vxp_de_texture_enhancement_levels_reg_g_SHIFT 24
#define vo_vxp_de_texture_enhancement_levels_reg_g_WIDTH 6

 h:6, /*[5:0]  */
 hole0:2,
 v:6, /*[13:8]  */
 hole1:2,
 d:6, /*[21:16]  */
 hole2:2,
 g:6, /*[29:24]  */
 hole3:2;
 } bits;

 uint32_t value;
};

union vo_vxp_de_texture_enhancement_2_regReg {
 struct { uint32_t

 /* sorting 1 */
#define vo_vxp_de_texture_enhancement_2_reg_vo_vxp_de_texture_enhancement_8_SHIFT 0
#define vo_vxp_de_texture_enhancement_2_reg_vo_vxp_de_texture_enhancement_8_WIDTH 4

 vo_vxp_de_texture_enhancement_8:4, /*[3:0]  */
 hole0:28;
 } bits;

 uint32_t value;
};

union vo_vxp_de_texture_enhancement_1_regReg {
 struct { uint32_t

 /* sorting 8 */
#define vo_vxp_de_texture_enhancement_1_reg__0_SHIFT 0
#define vo_vxp_de_texture_enhancement_1_reg__0_WIDTH 4
#define vo_vxp_de_texture_enhancement_1_reg__1_SHIFT 4
#define vo_vxp_de_texture_enhancement_1_reg__1_WIDTH 4
#define vo_vxp_de_texture_enhancement_1_reg__2_SHIFT 8
#define vo_vxp_de_texture_enhancement_1_reg__2_WIDTH 4
#define vo_vxp_de_texture_enhancement_1_reg__3_SHIFT 12
#define vo_vxp_de_texture_enhancement_1_reg__3_WIDTH 4
#define vo_vxp_de_texture_enhancement_1_reg__4_SHIFT 16
#define vo_vxp_de_texture_enhancement_1_reg__4_WIDTH 4
#define vo_vxp_de_texture_enhancement_1_reg__5_SHIFT 20
#define vo_vxp_de_texture_enhancement_1_reg__5_WIDTH 4
#define vo_vxp_de_texture_enhancement_1_reg__6_SHIFT 24
#define vo_vxp_de_texture_enhancement_1_reg__6_WIDTH 4
#define vo_vxp_de_texture_enhancement_1_reg__7_SHIFT 28
#define vo_vxp_de_texture_enhancement_1_reg__7_WIDTH 4

 _0:4, /*[3:0]  */
 _1:4, /*[7:4]  */
 _2:4, /*[11:8]  */
 _3:4, /*[15:12]  */
 _4:4, /*[19:16]  */
 _5:4, /*[23:20]  */
 _6:4, /*[27:24]  */
 _7:4; /*[31:28]  */
 } bits;

 uint32_t value;
};

union vo_vxp_de_mam_texture_thresholds_2_regReg {
 struct { uint32_t

 /* sorting 4 */
#define vo_vxp_de_mam_texture_thresholds_2_reg__4_SHIFT 0
#define vo_vxp_de_mam_texture_thresholds_2_reg__4_WIDTH 7
#define vo_vxp_de_mam_texture_thresholds_2_reg__5_SHIFT 8
#define vo_vxp_de_mam_texture_thresholds_2_reg__5_WIDTH 7
#define vo_vxp_de_mam_texture_thresholds_2_reg__6_SHIFT 16
#define vo_vxp_de_mam_texture_thresholds_2_reg__6_WIDTH 7
#define vo_vxp_de_mam_texture_thresholds_2_reg__7_SHIFT 24
#define vo_vxp_de_mam_texture_thresholds_2_reg__7_WIDTH 7

 _4:7, /*[6:0]  */
 hole0:1,
 _5:7, /*[14:8]  */
 hole1:1,
 _6:7, /*[22:16]  */
 hole2:1,
 _7:7, /*[30:24]  */
 hole3:1;
 } bits;

 uint32_t value;
};

union vo_vxp_de_mam_texture_thresholds_1_regReg {
 struct { uint32_t

 /* sorting 4 */
#define vo_vxp_de_mam_texture_thresholds_1_reg__0_SHIFT 0
#define vo_vxp_de_mam_texture_thresholds_1_reg__0_WIDTH 7
#define vo_vxp_de_mam_texture_thresholds_1_reg__1_SHIFT 8
#define vo_vxp_de_mam_texture_thresholds_1_reg__1_WIDTH 7
#define vo_vxp_de_mam_texture_thresholds_1_reg__2_SHIFT 16
#define vo_vxp_de_mam_texture_thresholds_1_reg__2_WIDTH 7
#define vo_vxp_de_mam_texture_thresholds_1_reg__3_SHIFT 24
#define vo_vxp_de_mam_texture_thresholds_1_reg__3_WIDTH 7

 _0:7, /*[6:0]  */
 hole0:1,
 _1:7, /*[14:8]  */
 hole1:1,
 _2:7, /*[22:16]  */
 hole2:1,
 _3:7, /*[30:24]  */
 hole3:1;
 } bits;

 uint32_t value;
};

union vo_vxp_de_mam_edge_thresholds_2_regReg {
 struct { uint32_t

 /* sorting 4 */
#define vo_vxp_de_mam_edge_thresholds_2_reg__4_SHIFT 0
#define vo_vxp_de_mam_edge_thresholds_2_reg__4_WIDTH 7
#define vo_vxp_de_mam_edge_thresholds_2_reg__5_SHIFT 8
#define vo_vxp_de_mam_edge_thresholds_2_reg__5_WIDTH 7
#define vo_vxp_de_mam_edge_thresholds_2_reg__6_SHIFT 16
#define vo_vxp_de_mam_edge_thresholds_2_reg__6_WIDTH 7
#define vo_vxp_de_mam_edge_thresholds_2_reg__7_SHIFT 24
#define vo_vxp_de_mam_edge_thresholds_2_reg__7_WIDTH 7

 _4:7, /*[6:0]  */
 hole0:1,
 _5:7, /*[14:8]  */
 hole1:1,
 _6:7, /*[22:16]  */
 hole2:1,
 _7:7, /*[30:24]  */
 hole3:1;
 } bits;

 uint32_t value;
};

union vo_vxp_de_mam_edge_thresholds_1_regReg {
 struct { uint32_t

 /* sorting 4 */
#define vo_vxp_de_mam_edge_thresholds_1_reg__0_SHIFT 0
#define vo_vxp_de_mam_edge_thresholds_1_reg__0_WIDTH 7
#define vo_vxp_de_mam_edge_thresholds_1_reg__1_SHIFT 8
#define vo_vxp_de_mam_edge_thresholds_1_reg__1_WIDTH 7
#define vo_vxp_de_mam_edge_thresholds_1_reg__2_SHIFT 16
#define vo_vxp_de_mam_edge_thresholds_1_reg__2_WIDTH 7
#define vo_vxp_de_mam_edge_thresholds_1_reg__3_SHIFT 24
#define vo_vxp_de_mam_edge_thresholds_1_reg__3_WIDTH 7

 _0:7, /*[6:0]  */
 hole0:1,
 _1:7, /*[14:8]  */
 hole1:1,
 _2:7, /*[22:16]  */
 hole2:1,
 _3:7, /*[30:24]  */
 hole3:1;
 } bits;

 uint32_t value;
};

union vo_vxp_de_image_size_regReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_vxp_de_image_size_reg_h_size_SHIFT 0
#define vo_vxp_de_image_size_reg_h_size_WIDTH 12
#define vo_vxp_de_image_size_reg_v_size_SHIFT 16
#define vo_vxp_de_image_size_reg_v_size_WIDTH 12

 h_size:12, /*[11:0]  */
 hole0:4,
 v_size:12, /*[27:16]  */
 hole1:4;
 } bits;

 uint32_t value;
};

union vo_vxp_de_image_posn_regReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_vxp_de_image_posn_reg_h_posn_SHIFT 0
#define vo_vxp_de_image_posn_reg_h_posn_WIDTH 11
#define vo_vxp_de_image_posn_reg_v_posn_SHIFT 16
#define vo_vxp_de_image_posn_reg_v_posn_WIDTH 11

 h_posn:11, /*[10:0]  */
 hole0:5,
 v_posn:11, /*[26:16]  */
 hole1:5;
 } bits;

 uint32_t value;
};

union vo_vxp_de_hpfg_c_2_regReg {
 struct { uint32_t

 /* sorting 4 */
#define vo_vxp_de_hpfg_c_2_reg__10_SHIFT 0
#define vo_vxp_de_hpfg_c_2_reg__10_WIDTH 8
#define vo_vxp_de_hpfg_c_2_reg__11_SHIFT 8
#define vo_vxp_de_hpfg_c_2_reg__11_WIDTH 8
#define vo_vxp_de_hpfg_c_2_reg__12_SHIFT 16
#define vo_vxp_de_hpfg_c_2_reg__12_WIDTH 8
#define vo_vxp_de_hpfg_c_2_reg__13_SHIFT 24
#define vo_vxp_de_hpfg_c_2_reg__13_WIDTH 8

 _10:8, /*[7:0]  */
 _11:8, /*[15:8]  */
 _12:8, /*[23:16]  */
 _13:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_vxp_de_hpfg_c_1_regReg {
 struct { uint32_t

 /* sorting 4 */
#define vo_vxp_de_hpfg_c_1_reg__00_SHIFT 0
#define vo_vxp_de_hpfg_c_1_reg__00_WIDTH 8
#define vo_vxp_de_hpfg_c_1_reg__01_SHIFT 8
#define vo_vxp_de_hpfg_c_1_reg__01_WIDTH 8
#define vo_vxp_de_hpfg_c_1_reg__02_SHIFT 16
#define vo_vxp_de_hpfg_c_1_reg__02_WIDTH 8
#define vo_vxp_de_hpfg_c_1_reg__03_SHIFT 24
#define vo_vxp_de_hpfg_c_1_reg__03_WIDTH 8

 _00:8, /*[7:0]  */
 _01:8, /*[15:8]  */
 _02:8, /*[23:16]  */
 _03:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

union vo_vxp_de_edge_enhancement_levels_regReg {
 struct { uint32_t

 /* sorting 4 */
#define vo_vxp_de_edge_enhancement_levels_reg_h_SHIFT 0
#define vo_vxp_de_edge_enhancement_levels_reg_h_WIDTH 6
#define vo_vxp_de_edge_enhancement_levels_reg_v_SHIFT 8
#define vo_vxp_de_edge_enhancement_levels_reg_v_WIDTH 6
#define vo_vxp_de_edge_enhancement_levels_reg_d_SHIFT 16
#define vo_vxp_de_edge_enhancement_levels_reg_d_WIDTH 6
#define vo_vxp_de_edge_enhancement_levels_reg_g_SHIFT 24
#define vo_vxp_de_edge_enhancement_levels_reg_g_WIDTH 6

 h:6, /*[5:0]  */
 hole0:2,
 v:6, /*[13:8]  */
 hole1:2,
 d:6, /*[21:16]  */
 hole2:2,
 g:6, /*[29:24]  */
 hole3:2;
 } bits;

 uint32_t value;
};

union vo_vxp_de_edge_enhancement_2_regReg {
 struct { uint32_t

 /* sorting 1 */
#define vo_vxp_de_edge_enhancement_2_reg_vo_vxp_de_edge_enhancement_8_SHIFT 0
#define vo_vxp_de_edge_enhancement_2_reg_vo_vxp_de_edge_enhancement_8_WIDTH 4

 vo_vxp_de_edge_enhancement_8:4, /*[3:0]  */
 hole0:28;
 } bits;

 uint32_t value;
};

union vo_vxp_de_edge_enhancement_1_regReg {
 struct { uint32_t

 /* sorting 8 */
#define vo_vxp_de_edge_enhancement_1_reg__0_SHIFT 0
#define vo_vxp_de_edge_enhancement_1_reg__0_WIDTH 4
#define vo_vxp_de_edge_enhancement_1_reg__1_SHIFT 4
#define vo_vxp_de_edge_enhancement_1_reg__1_WIDTH 4
#define vo_vxp_de_edge_enhancement_1_reg__2_SHIFT 8
#define vo_vxp_de_edge_enhancement_1_reg__2_WIDTH 4
#define vo_vxp_de_edge_enhancement_1_reg__3_SHIFT 12
#define vo_vxp_de_edge_enhancement_1_reg__3_WIDTH 4
#define vo_vxp_de_edge_enhancement_1_reg__4_SHIFT 16
#define vo_vxp_de_edge_enhancement_1_reg__4_WIDTH 4
#define vo_vxp_de_edge_enhancement_1_reg__5_SHIFT 20
#define vo_vxp_de_edge_enhancement_1_reg__5_WIDTH 4
#define vo_vxp_de_edge_enhancement_1_reg__6_SHIFT 24
#define vo_vxp_de_edge_enhancement_1_reg__6_WIDTH 4
#define vo_vxp_de_edge_enhancement_1_reg__7_SHIFT 28
#define vo_vxp_de_edge_enhancement_1_reg__7_WIDTH 4

 _0:4, /*[3:0]  */
 _1:4, /*[7:4]  */
 _2:4, /*[11:8]  */
 _3:4, /*[15:12]  */
 _4:4, /*[19:16]  */
 _5:4, /*[23:20]  */
 _6:4, /*[27:24]  */
 _7:4; /*[31:28]  */
 } bits;

 uint32_t value;
};

union vo_vxp_de_config_regReg {
 struct { uint32_t

 /* sorting 4 */
#define vo_vxp_de_config_reg_enable_SHIFT 0
#define vo_vxp_de_config_reg_enable_WIDTH 1
#define vo_vxp_de_config_reg_follow_image_params_SHIFT 4
#define vo_vxp_de_config_reg_follow_image_params_WIDTH 1
#define vo_vxp_de_config_reg_oswindow_SHIFT 8
#define vo_vxp_de_config_reg_oswindow_WIDTH 2
#define vo_vxp_de_config_reg_version_SHIFT 12
#define vo_vxp_de_config_reg_version_WIDTH 1

 enable:1, /*[0:0]  */
 hole0:3,
 follow_image_params:1, /*[4:4]  */
 hole1:3,
 oswindow:2, /*[9:8]  */
 hole2:2,
 version:1, /*[12:12]  */
 hole3:19;
 } bits;

 uint32_t value;
};

struct vo_vxp_detail_enhance {
 union vo_vxp_de_config_regReg vo_vxp_de_config_reg; /* +0x00000000  */
 union vo_vxp_de_image_posn_regReg vo_vxp_de_image_posn_reg; /* +0x00000004  */
 union vo_vxp_de_image_size_regReg vo_vxp_de_image_size_reg; /* +0x00000008  */
 union vo_vxp_de_edge_enhancement_levels_regReg vo_vxp_de_edge_enhancement_levels_reg; /* +0x0000000c  */
 union vo_vxp_de_texture_enhancement_levels_regReg vo_vxp_de_texture_enhancement_levels_reg; /* +0x00000010  */
 union vo_vxp_de_thresholds_regReg vo_vxp_de_thresholds_reg; /* +0x00000014  */
 union vo_vxp_de_edge_enhancement_1_regReg vo_vxp_de_edge_enhancement_1_reg; /* +0x00000018  */
 union vo_vxp_de_edge_enhancement_2_regReg vo_vxp_de_edge_enhancement_2_reg; /* +0x0000001c  */
 union vo_vxp_de_texture_enhancement_1_regReg vo_vxp_de_texture_enhancement_1_reg; /* +0x00000020  */
 union vo_vxp_de_texture_enhancement_2_regReg vo_vxp_de_texture_enhancement_2_reg; /* +0x00000024  */
 union vo_vxp_de_mam_edge_thresholds_1_regReg vo_vxp_de_mam_edge_thresholds_1_reg; /* +0x00000028  */
 union vo_vxp_de_mam_edge_thresholds_2_regReg vo_vxp_de_mam_edge_thresholds_2_reg; /* +0x0000002c  */
 uint32_t pad0[0x0004/4];
 union vo_vxp_de_mam_texture_thresholds_1_regReg vo_vxp_de_mam_texture_thresholds_1_reg; /* +0x00000034  */
 union vo_vxp_de_mam_texture_thresholds_2_regReg vo_vxp_de_mam_texture_thresholds_2_reg; /* +0x00000038  */
 uint32_t pad1[0x0004/4];
 union vo_vxp_de_hpfg_c_1_regReg vo_vxp_de_hpfg_c_1_reg; /* +0x00000040  */
 union vo_vxp_de_hpfg_c_2_regReg vo_vxp_de_hpfg_c_2_reg; /* +0x00000044  */
};
