/* autogenerated with parsecfg: do not edit. */

union i2s_out_irq_countReg {
 struct { uint32_t

 /* sorting 1 */
#define i2s_out_irq_count_i2s_out_irq_count16_SHIFT 0
#define i2s_out_irq_count_i2s_out_irq_count16_WIDTH 16

 i2s_out_irq_count16:16, /*[15:0]  */
 hole0:16;
 } bits;

 uint32_t value;
};

union i2s_out_data_ctrlReg {
 struct { uint32_t

 /* sorting 4 */
#define i2s_out_data_ctrl__en_SHIFT 0
#define i2s_out_data_ctrl__en_WIDTH 16
#define i2s_out_data_ctrl__align_SHIFT 16
#define i2s_out_data_ctrl__align_WIDTH 5
#define i2s_out_data_ctrl__bo_SHIFT 21
#define i2s_out_data_ctrl__bo_WIDTH 1
#define i2s_out_data_ctrl__16en_SHIFT 22
#define i2s_out_data_ctrl__16en_WIDTH 1

 _en:16, /*[15:0] ,NO_MEM */
 _align:5, /*[20:16]  */
 _bo:1, /*[21:21]  */
 _16en:1, /*[22:22]  */
 hole0:9;
 } bits;

 uint32_t value;
};

union i2s_out_clk_ctrlReg {
 struct { uint32_t

 /* sorting 5 */
#define i2s_out_clk_ctrl_clk_en_SHIFT 0
#define i2s_out_clk_ctrl_clk_en_WIDTH 3
#define i2s_out_clk_ctrl_clk_polarity_SHIFT 3
#define i2s_out_clk_ctrl_clk_polarity_WIDTH 2
#define i2s_out_clk_ctrl_aclk_ctrl_SHIFT 5
#define i2s_out_clk_ctrl_aclk_ctrl_WIDTH 2
#define i2s_out_clk_ctrl_bclk_ctrl_SHIFT 7
#define i2s_out_clk_ctrl_bclk_ctrl_WIDTH 2
#define i2s_out_clk_ctrl_mclk_ctrl_SHIFT 9
#define i2s_out_clk_ctrl_mclk_ctrl_WIDTH 4

 clk_en:3, /*[2:0]  */
 clk_polarity:2, /*[4:3]  */
 aclk_ctrl:2, /*[6:5]  */
 bclk_ctrl:2, /*[8:7]  */
 mclk_ctrl:4, /*[12:9]  */
 hole0:19;
 } bits;

 uint32_t value;
};

struct audio_io_i2s_out {
 union i2s_out_clk_ctrlReg i2s_out_clk_ctrl; /* +0x00000000  */
 union i2s_out_data_ctrlReg i2s_out_data_ctrl; /* +0x00000004  */
 uint32_t i2s_out_irq_ctrl; /* +0x00000008 ,NO_TEST */
 uint32_t i2s_out_count; /* +0x0000000c  */
 union i2s_out_irq_countReg i2s_out_irq_count; /* +0x00000010  */
};
