/* autogenerated with parsecfg: do not edit. */

union mvp_store_yReg {
 struct { uint32_t

 /* sorting 1 */
#define mvp_store_y_mvp_store_y_value_SHIFT 0
#define mvp_store_y_mvp_store_y_value_WIDTH 8

 mvp_store_y_value:8, /*[7:0]  */
 hole0:24;
 } bits;

 uint32_t value;
};

union mvp_store_xReg {
 struct { uint32_t

 /* sorting 1 */
#define mvp_store_x_mvp_store_x_value_SHIFT 0
#define mvp_store_x_mvp_store_x_value_WIDTH 8

 mvp_store_x_value:8, /*[7:0]  */
 hole0:24;
 } bits;

 uint32_t value;
};

union mvp_slice_cfgReg {
 struct { uint32_t

 /* sorting 2 */
#define mvp_slice_cfg_e1_SHIFT 0
#define mvp_slice_cfg_e1_WIDTH 4
#define mvp_slice_cfg_e2_SHIFT 5
#define mvp_slice_cfg_e2_WIDTH 1

 e1:4, /*[3:0]  */
 hole0:1,
 e2:1, /*[5:5]  */
 hole1:26;
 } bits;

 uint32_t value;
};

union mvp_picture_cfgReg {
 struct { uint32_t

 /* sorting 3 */
#define mvp_picture_cfg_e1_SHIFT 1
#define mvp_picture_cfg_e1_WIDTH 1
#define mvp_picture_cfg_e2_SHIFT 4
#define mvp_picture_cfg_e2_WIDTH 2
#define mvp_picture_cfg_e3_SHIFT 8
#define mvp_picture_cfg_e3_WIDTH 2

 hole0:1,
 e1:1, /*[1:1]  */
 hole1:2,
 e2:2, /*[5:4]  */
 hole2:2,
 e3:2, /*[9:8]  */
 hole3:22;
 } bits;

 uint32_t value;
};

union mvp_min_poc_cfgReg {
 struct { uint32_t

 /* sorting 1 */
#define mvp_min_poc_cfg_mvp_min_poc_cfg_value_SHIFT 0
#define mvp_min_poc_cfg_mvp_min_poc_cfg_value_WIDTH 8

 mvp_min_poc_cfg_value:8, /*[7:0]  */
 hole0:24;
 } bits;

 uint32_t value;
};

union mvp_fme_opt_cfgReg {
 struct { uint32_t

 /* sorting 1 */
#define mvp_fme_opt_cfg_mvp_fme_opt_cfg_value_SHIFT 0
#define mvp_fme_opt_cfg_mvp_fme_opt_cfg_value_WIDTH 11

 mvp_fme_opt_cfg_value:11, /*[10:0]  */
 hole0:21;
 } bits;

 uint32_t value;
};

union mvp_fme_mb_typeReg {
 struct { uint32_t

 /* sorting 2 */
#define mvp_fme_mb_type_mb_type_SHIFT 0
#define mvp_fme_mb_type_mb_type_WIDTH 6
#define mvp_fme_mb_type_submb_type_SHIFT 8
#define mvp_fme_mb_type_submb_type_WIDTH 6

 mb_type:6, /*[5:0]  */
 hole0:2,
 submb_type:6, /*[13:8]  */
 hole1:18;
 } bits;

 uint32_t value;
};

union mvp_filter_loaderReg {
 struct { uint32_t

 /* sorting 1 */
#define mvp_filter_loader_mvp_filter_loader_value_SHIFT 0
#define mvp_filter_loader_mvp_filter_loader_value_WIDTH 16

 mvp_filter_loader_value:16, /*[15:0]  */
 hole0:16;
 } bits;

 uint32_t value;
};

union mvp_can_ref_l0_l1Reg {
 struct { uint32_t

 /* sorting 4 */
#define mvp_can_ref_l0_l1_e1_SHIFT 0
#define mvp_can_ref_l0_l1_e1_WIDTH 3
#define mvp_can_ref_l0_l1_e2_SHIFT 4
#define mvp_can_ref_l0_l1_e2_WIDTH 3
#define mvp_can_ref_l0_l1_e3_SHIFT 8
#define mvp_can_ref_l0_l1_e3_WIDTH 3
#define mvp_can_ref_l0_l1_e4_SHIFT 12
#define mvp_can_ref_l0_l1_e4_WIDTH 3

 e1:3, /*[2:0]  */
 hole0:1,
 e2:3, /*[6:4]  */
 hole1:1,
 e3:3, /*[10:8]  */
 hole2:1,
 e4:3, /*[14:12]  */
 hole3:17;
 } bits;

 uint32_t value;
};

struct vtsc_motion_vectors_predictor {
 union mvp_store_xReg mvp_store_x; /* +0x00000000  */
 union mvp_store_yReg mvp_store_y; /* +0x00000004  */
 uint32_t mvp_mb_cfg; /* +0x00000008 ,NO_TEST */
 union mvp_slice_cfgReg mvp_slice_cfg; /* +0x0000000c  */
 union mvp_picture_cfgReg mvp_picture_cfg; /* +0x00000010  */
 union mvp_min_poc_cfgReg mvp_min_poc_cfg; /* +0x00000014  */
 union mvp_filter_loaderReg mvp_filter_loader; /* +0x00000018  */
 union mvp_can_ref_l0_l1Reg mvp_can_ref_l0_l1; /* +0x0000001c  */
 union mvp_fme_mb_typeReg mvp_fme_mb_type; /* +0x00000020  */
 union mvp_fme_opt_cfgReg mvp_fme_opt_cfg; /* +0x00000024  */
 uint32_t mvp_refidx_l0_l1; /* +0x00000028 ,RO */
 uint32_t mvp_mode_best; /* +0x0000002c ,RO */
 uint32_t mvp_mode_costtop; /* +0x00000030 ,RO */
 uint32_t mvp_mode_costbot; /* +0x00000034 ,RO */
};
