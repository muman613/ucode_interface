/* autogenerated with parsecfg: do not edit. */

/* gotta drop OTP_CMD_STAT_command_complete@OTP_CMD_STAT: 0xffffffff [31:31] */
union OTP_MISCReg {
 struct { uint32_t

 /* sorting 2 */
#define OTP_MISC_c0_SHIFT 0
#define OTP_MISC_c0_WIDTH 16
#define OTP_MISC_c1_SHIFT 16
#define OTP_MISC_c1_WIDTH 16

 c0:16, /*[15:0]  */
 c1:16; /*[31:16]  */
 } bits;

 uint32_t value;
};

union OTP_FREEReg {
 struct { uint32_t

 /* sorting 3 */
#define OTP_FREE_obj_free_SHIFT 0
#define OTP_FREE_obj_free_WIDTH 12
#define OTP_FREE_IX_free_SHIFT 16
#define OTP_FREE_IX_free_WIDTH 7
#define OTP_FREE_IX_end_SHIFT 24
#define OTP_FREE_IX_end_WIDTH 7

 obj_free:12, /*[11:0] ,RO */
 hole0:4,
 ix_free:7, /*[22:16] ,RO */
 hole1:1,
 ix_end:7, /*[30:24] ,RO */
 hole2:1;
 } bits;

 uint32_t value;
};

union OTP_CMD_STATReg {
 struct { uint32_t

 /* sorting 3 */
#define OTP_CMD_STAT_cs0_SHIFT 0
#define OTP_CMD_STAT_cs0_WIDTH 16
#define OTP_CMD_STAT_cs1_SHIFT 16
#define OTP_CMD_STAT_cs1_WIDTH 8
#define OTP_CMD_STAT_CmdStat_SHIFT 24
#define OTP_CMD_STAT_CmdStat_WIDTH 8

 cs0:16, /*[15:0]  */
 cs1:8, /*[23:16]  */
 cmdstat:8; /*[31:24]  */
 } bits;

 uint32_t value;
};

struct ha_otp_controller {
 union OTP_CMD_STATReg OTP_CMD_STAT; /* +0x00000000 ,NO_TEST */
 union OTP_MISCReg OTP_MISC; /* +0x00000004  */
 union OTP_FREEReg OTP_FREE; /* +0x00000008  */
 uint32_t OTP_OBJ_AREA; /* +0x0000000c ,RO */
 uint32_t OTP_LOCKS; /* +0x00000010 ,RO */
 uint32_t OTP_SYSINFO; /* +0x00000014 ,RO */
 uint32_t OTP_PWRINFO; /* +0x00000018 ,RO */
 uint32_t pad0[0x01e4/4];
 uint32_t OTP_SCRATCHPAD; /* +0x00000200  */
 uint32_t coeff1; /* +0x00000204  */
 uint32_t coeff2; /* +0x00000208  */
 uint32_t coeff3; /* +0x0000020c  */
 uint32_t coeff4; /* +0x00000210  */
 uint32_t coeff5; /* +0x00000214  */
 uint32_t coeff6; /* +0x00000218  */
 uint32_t coeff7; /* +0x0000021c  */
 uint32_t coeff8; /* +0x00000220  */
 uint32_t coeff9; /* +0x00000224  */
 uint32_t coeff10; /* +0x00000228  */
 uint32_t coeff11; /* +0x0000022c  */
 uint32_t coeff12; /* +0x00000230  */
 uint32_t coeff13; /* +0x00000234  */
 uint32_t coeff14; /* +0x00000238  */
 uint32_t coeff15; /* +0x0000023c  */
 uint32_t coeff16; /* +0x00000240  */
 uint32_t coeff17; /* +0x00000244  */
 uint32_t coeff18; /* +0x00000248  */
 uint32_t coeff19; /* +0x0000024c  */
 uint32_t coeff20; /* +0x00000250  */
 uint32_t coeff21; /* +0x00000254  */
 uint32_t coeff22; /* +0x00000258  */
 uint32_t coeff23; /* +0x0000025c  */
 uint32_t coeff24; /* +0x00000260  */
 uint32_t coeff25; /* +0x00000264  */
 uint32_t coeff26; /* +0x00000268  */
 uint32_t coeff27; /* +0x0000026c  */
 uint32_t coeff28; /* +0x00000270  */
 uint32_t coeff29; /* +0x00000274  */
 uint32_t coeff30; /* +0x00000278  */
 uint32_t coeff31; /* +0x0000027c  */
 uint32_t coeff32; /* +0x00000280  */
 uint32_t coeff33; /* +0x00000284  */
 uint32_t coeff34; /* +0x00000288  */
 uint32_t coeff35; /* +0x0000028c  */
 uint32_t coeff36; /* +0x00000290  */
 uint32_t coeff37; /* +0x00000294  */
 uint32_t coeff38; /* +0x00000298  */
 uint32_t coeff39; /* +0x0000029c  */
 uint32_t coeff40; /* +0x000002a0  */
 uint32_t coeff41; /* +0x000002a4  */
 uint32_t coeff42; /* +0x000002a8  */
 uint32_t coeff43; /* +0x000002ac  */
 uint32_t coeff44; /* +0x000002b0  */
 uint32_t coeff45; /* +0x000002b4  */
 uint32_t coeff46; /* +0x000002b8  */
 uint32_t coeff47; /* +0x000002bc  */
 uint32_t coeff48; /* +0x000002c0  */
 uint32_t coeff49; /* +0x000002c4  */
 uint32_t coeff50; /* +0x000002c8  */
 uint32_t coeff51; /* +0x000002cc  */
 uint32_t coeff52; /* +0x000002d0  */
 uint32_t coeff53; /* +0x000002d4  */
 uint32_t coeff54; /* +0x000002d8  */
 uint32_t coeff55; /* +0x000002dc  */
 uint32_t coeff56; /* +0x000002e0  */
 uint32_t coeff57; /* +0x000002e4  */
 uint32_t coeff58; /* +0x000002e8  */
 uint32_t coeff59; /* +0x000002ec  */
 uint32_t coeff60; /* +0x000002f0  */
 uint32_t coeff61; /* +0x000002f4  */
 uint32_t coeff62; /* +0x000002f8  */
 uint32_t coeff63; /* +0x000002fc  */
 uint32_t coeff64; /* +0x00000300  */
 uint32_t coeff65; /* +0x00000304  */
 uint32_t coeff66; /* +0x00000308  */
 uint32_t coeff67; /* +0x0000030c  */
 uint32_t coeff68; /* +0x00000310  */
 uint32_t coeff69; /* +0x00000314  */
 uint32_t coeff70; /* +0x00000318  */
 uint32_t coeff71; /* +0x0000031c  */
 uint32_t coeff72; /* +0x00000320  */
 uint32_t coeff73; /* +0x00000324  */
 uint32_t coeff74; /* +0x00000328  */
 uint32_t coeff75; /* +0x0000032c  */
 uint32_t coeff76; /* +0x00000330  */
 uint32_t coeff77; /* +0x00000334  */
 uint32_t coeff78; /* +0x00000338  */
 uint32_t coeff79; /* +0x0000033c  */
 uint32_t coeff80; /* +0x00000340  */
 uint32_t coeff81; /* +0x00000344  */
 uint32_t coeff82; /* +0x00000348  */
 uint32_t coeff83; /* +0x0000034c  */
 uint32_t coeff84; /* +0x00000350  */
 uint32_t coeff85; /* +0x00000354  */
 uint32_t coeff86; /* +0x00000358  */
 uint32_t coeff87; /* +0x0000035c  */
 uint32_t coeff88; /* +0x00000360  */
 uint32_t coeff89; /* +0x00000364  */
 uint32_t coeff90; /* +0x00000368  */
 uint32_t coeff91; /* +0x0000036c  */
 uint32_t coeff92; /* +0x00000370  */
 uint32_t coeff93; /* +0x00000374  */
 uint32_t coeff94; /* +0x00000378  */
 uint32_t coeff95; /* +0x0000037c  */
 uint32_t coeff96; /* +0x00000380  */
 uint32_t coeff97; /* +0x00000384  */
 uint32_t coeff98; /* +0x00000388  */
 uint32_t coeff99; /* +0x0000038c  */
 uint32_t coeff100; /* +0x00000390  */
 uint32_t coeff101; /* +0x00000394  */
 uint32_t coeff102; /* +0x00000398  */
 uint32_t coeff103; /* +0x0000039c  */
 uint32_t coeff104; /* +0x000003a0  */
 uint32_t coeff105; /* +0x000003a4  */
 uint32_t coeff106; /* +0x000003a8  */
 uint32_t coeff107; /* +0x000003ac  */
 uint32_t coeff108; /* +0x000003b0  */
 uint32_t coeff109; /* +0x000003b4  */
 uint32_t coeff110; /* +0x000003b8  */
 uint32_t coeff111; /* +0x000003bc  */
 uint32_t coeff112; /* +0x000003c0  */
 uint32_t coeff113; /* +0x000003c4  */
 uint32_t coeff114; /* +0x000003c8  */
 uint32_t coeff115; /* +0x000003cc  */
 uint32_t coeff116; /* +0x000003d0  */
 uint32_t coeff117; /* +0x000003d4  */
 uint32_t coeff118; /* +0x000003d8  */
 uint32_t coeff119; /* +0x000003dc  */
 uint32_t coeff120; /* +0x000003e0  */
 uint32_t coeff121; /* +0x000003e4  */
 uint32_t coeff122; /* +0x000003e8  */
 uint32_t coeff123; /* +0x000003ec  */
 uint32_t coeff124; /* +0x000003f0  */
 uint32_t coeff125; /* +0x000003f4  */
 uint32_t coeff126; /* +0x000003f8  */
 uint32_t coeff127; /* +0x000003fc  */
};
