/* autogenerated with parsecfg: do not edit. */

/* gotta drop ha_rstctrl_reset_ipu_set@ha_rstctrl_reset_0: 0x000000ff [1:0] */
/* gotta drop ha_rstctrl_reset_ipu_current@ha_rstctrl_reset_0: 0x000000ff [5:4] */
/* gotta drop ha_rstctrl_reset_timer_pool_set@ha_rstctrl_reset_0: 0x0000ffff [9:8] */
/* gotta drop ha_rstctrl_reset_timer_pool_current@ha_rstctrl_reset_0: 0x0000ffff [13:12] */
union ha_rstctrl_reset_0Reg {
 struct { uint32_t

 /* sorting 2 */
#define ha_rstctrl_reset_0_ipu_SHIFT 0
#define ha_rstctrl_reset_0_ipu_WIDTH 8
#define ha_rstctrl_reset_0_timer_pool_SHIFT 8
#define ha_rstctrl_reset_0_timer_pool_WIDTH 8

 ipu:8, /*[7:0]  */
 timer_pool:8, /*[15:8]  */
 hole0:16;
 } bits;

 uint32_t value;
};

struct ha_reset_controller {
 union ha_rstctrl_reset_0Reg ha_rstctrl_reset_0; /* +0x00000000 ,NO_TEST */
};
