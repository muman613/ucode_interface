/* autogenerated with parsecfg: do not edit. */

union pmem_xfer_cfgReg {
 struct { uint32_t

 /* sorting 3 */
#define pmem_xfer_cfg_cntx_load_flag_SHIFT 0
#define pmem_xfer_cfg_cntx_load_flag_WIDTH 1
#define pmem_xfer_cfg_zero_SHIFT 1
#define pmem_xfer_cfg_zero_WIDTH 9
#define pmem_xfer_cfg_low_hz_4mbs_thld_SHIFT 10
#define pmem_xfer_cfg_low_hz_4mbs_thld_WIDTH 6

 cntx_load_flag:1, /*[0:0] ,RO */
 zero:9, /*[9:1] ,RO */
 low_hz_4mbs_thld:6, /*[15:10]  */
 hole0:16;
 } bits;

 uint32_t value;
};

union pmem_slice_cfgReg {
 struct { uint32_t

 /* sorting 4 */
#define pmem_slice_cfg_beta_offset_SHIFT 0
#define pmem_slice_cfg_beta_offset_WIDTH 4
#define pmem_slice_cfg_alpha_offset_SHIFT 4
#define pmem_slice_cfg_alpha_offset_WIDTH 4
#define pmem_slice_cfg_dis_dbk_idc_SHIFT 8
#define pmem_slice_cfg_dis_dbk_idc_WIDTH 2
#define pmem_slice_cfg_slice_qp_luma_SHIFT 10
#define pmem_slice_cfg_slice_qp_luma_WIDTH 6

 beta_offset:4, /*[3:0]  */
 alpha_offset:4, /*[7:4]  */
 dis_dbk_idc:2, /*[9:8]  */
 slice_qp_luma:6, /*[15:10]  */
 hole0:16;
 } bits;

 uint32_t value;
};

union pmem_picture_cfgReg {
 struct { uint32_t

 /* sorting 3 */
#define pmem_picture_cfg_picture_type_SHIFT 0
#define pmem_picture_cfg_picture_type_WIDTH 2
#define pmem_picture_cfg_cons_ipred_flag_SHIFT 2
#define pmem_picture_cfg_cons_ipred_flag_WIDTH 1
#define pmem_picture_cfg_chroma_qp_idx_offset_SHIFT 3
#define pmem_picture_cfg_chroma_qp_idx_offset_WIDTH 5

 picture_type:2, /*[1:0]  */
 cons_ipred_flag:1, /*[2:2]  */
 chroma_qp_idx_offset:5, /*[7:3]  */
 hole0:24;
 } bits;

 uint32_t value;
};

union pmem_mb_cfgReg {
 struct { uint32_t

 /* sorting 4 */
#define pmem_mb_cfg_qp_luma_SHIFT 0
#define pmem_mb_cfg_qp_luma_WIDTH 6
#define pmem_mb_cfg_lambda_scale_SHIFT 6
#define pmem_mb_cfg_lambda_scale_WIDTH 3
#define pmem_mb_cfg_lambda_SHIFT 9
#define pmem_mb_cfg_lambda_WIDTH 1
#define pmem_mb_cfg_read_only_SHIFT 10
#define pmem_mb_cfg_read_only_WIDTH 6

 qp_luma:6, /*[5:0]  */
 lambda_scale:3, /*[8:6]  */
 lambda:1, /*[9:9]  */
 read_only:6, /*[15:10] ,RO */
 hole0:16;
 } bits;

 uint32_t value;
};

struct vtsc_prediction_memory {
 uint32_t pad0[0x0180/4];
 union pmem_mb_cfgReg pmem_mb_cfg; /* +0x00000180  */
 union pmem_slice_cfgReg pmem_slice_cfg; /* +0x00000184  */
 union pmem_picture_cfgReg pmem_picture_cfg; /* +0x00000188  */
 union pmem_xfer_cfgReg pmem_xfer_cfg; /* +0x0000018c  */
 uint32_t pmem_res_sad_mb_top; /* +0x00000190 ,RO */
 uint32_t pmem_res_sad_mb_bottom; /* +0x00000194 ,RO */
};
