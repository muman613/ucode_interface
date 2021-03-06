/* autogenerated with parsecfg: do not edit. */

union sha_total_size_hReg {
 struct { uint32_t

 /* sorting 1 */
#define sha_total_size_h_sha_size_h_SHIFT 0
#define sha_total_size_h_sha_size_h_WIDTH 8

 sha_size_h:8, /*[7:0]  */
 hole0:24;
 } bits;

 uint32_t value;
};

union sha_config_sha_modeReg {
 struct { uint32_t

 /* sorting 1 */
#define sha_config_sha_mode_sha256_sha1n_SHIFT 0
#define sha_config_sha_mode_sha256_sha1n_WIDTH 1

 sha256_sha1n:1, /*[0:0] ,NO_MEM */
 hole0:31;
 } bits;

 uint32_t value;
};

union sha_config_regReg {
 struct { uint32_t

 /* sorting 3 */
#define sha_config_reg_cnt_SHIFT 0
#define sha_config_reg_cnt_WIDTH 30
#define sha_config_reg_first_block_flag_SHIFT 30
#define sha_config_reg_first_block_flag_WIDTH 1
#define sha_config_reg_last_block_flag_SHIFT 31
#define sha_config_reg_last_block_flag_WIDTH 1

 cnt:30, /*[29:0]  */
 first_block_flag:1, /*[30:30] ,NO_MEM */
 last_block_flag:1; /*[31:31]  */
 } bits;

 uint32_t value;
};

struct xpu_cipher_sha {
 union sha_config_regReg sha_config_reg; /* +0x00000000  */
 uint32_t sha_total_size_lo; /* +0x00000004  */
 union sha_total_size_hReg sha_total_size_h; /* +0x00000008  */
 uint32_t sha_h0_value; /* +0x0000000c  */
 uint32_t sha_h1_value; /* +0x00000010  */
 uint32_t sha_h2_value; /* +0x00000014  */
 uint32_t sha_h3_value; /* +0x00000018  */
 uint32_t sha_h4_value; /* +0x0000001c  */
 uint32_t sha_h5_value; /* +0x00000020  */
 uint32_t sha_h6_value; /* +0x00000024  */
 uint32_t sha_h7_value; /* +0x00000028  */
 union sha_config_sha_modeReg sha_config_sha_mode; /* +0x0000002c  */
};
