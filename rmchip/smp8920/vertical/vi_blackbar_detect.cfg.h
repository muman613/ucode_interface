/* autogenerated with parsecfg: do not edit. */

union vi_blackbar_outside_pixReg {
 struct { uint32_t

 /* sorting 2 */
#define vi_blackbar_outside_pix_bot_SHIFT 0
#define vi_blackbar_outside_pix_bot_WIDTH 10
#define vi_blackbar_outside_pix_top_SHIFT 16
#define vi_blackbar_outside_pix_top_WIDTH 10

 bot:10, /*[9:0]  */
 hole0:6,
 top:10, /*[25:16]  */
 hole1:6;
 } bits;

 uint32_t value;
};

union vi_blackbar_frame_sizeReg {
 struct { uint32_t

 /* sorting 2 */
#define vi_blackbar_frame_size_height_SHIFT 0
#define vi_blackbar_frame_size_height_WIDTH 11
#define vi_blackbar_frame_size_width_SHIFT 16
#define vi_blackbar_frame_size_width_WIDTH 12

 height:11, /*[10:0]  */
 hole0:5,
 width:12, /*[27:16]  */
 hole1:4;
 } bits;

 uint32_t value;
};

union vi_blackbar_cfgReg {
 struct { uint32_t

 /* sorting 3 */
#define vi_blackbar_cfg_direction_SHIFT 0
#define vi_blackbar_cfg_direction_WIDTH 1
#define vi_blackbar_cfg_size_SHIFT 1
#define vi_blackbar_cfg_size_WIDTH 10
#define vi_blackbar_cfg_is_422_SHIFT 11
#define vi_blackbar_cfg_is_422_WIDTH 1

 direction:1, /*[0:0]  */
 size:10, /*[10:1]  */
 is_422:1, /*[11:11]  */
 hole0:20;
 } bits;

 uint32_t value;
};

struct vi_blackbar_detect {
 uint32_t vi_blackbar_buffers_0; /* +0x00000000  */
 uint32_t vi_blackbar_buffers_1; /* +0x00000004  */
 uint32_t vi_blackbar_buffers_2; /* +0x00000008  */
 uint32_t vi_blackbar_buffers_3; /* +0x0000000c  */
 uint32_t vi_blackbar_buffers_4; /* +0x00000010  */
 uint32_t vi_blackbar_buffers_5; /* +0x00000014  */
 uint32_t vi_blackbar_buffers_6; /* +0x00000018  */
 uint32_t vi_blackbar_buffers_7; /* +0x0000001c  */
 uint32_t vi_blackbar_buffers_8; /* +0x00000020  */
 uint32_t vi_blackbar_buffers_9; /* +0x00000024  */
 uint32_t vi_blackbar_buffers_10; /* +0x00000028  */
 uint32_t vi_blackbar_buffers_11; /* +0x0000002c  */
 uint32_t vi_blackbar_buffers_12; /* +0x00000030  */
 uint32_t vi_blackbar_buffers_13; /* +0x00000034  */
 uint32_t vi_blackbar_buffers_14; /* +0x00000038  */
 uint32_t vi_blackbar_buffers_15; /* +0x0000003c  */
 uint32_t vi_blackbar_buffers_16; /* +0x00000040  */
 uint32_t vi_blackbar_buffers_17; /* +0x00000044  */
 uint32_t vi_blackbar_buffers_18; /* +0x00000048  */
 uint32_t vi_blackbar_buffers_19; /* +0x0000004c  */
 uint32_t vi_blackbar_buffers_20; /* +0x00000050  */
 uint32_t vi_blackbar_buffers_21; /* +0x00000054  */
 uint32_t vi_blackbar_buffers_22; /* +0x00000058  */
 uint32_t vi_blackbar_buffers_23; /* +0x0000005c  */
 uint32_t vi_blackbar_buffers_24; /* +0x00000060  */
 uint32_t vi_blackbar_buffers_25; /* +0x00000064  */
 uint32_t vi_blackbar_buffers_26; /* +0x00000068  */
 uint32_t vi_blackbar_buffers_27; /* +0x0000006c  */
 uint32_t vi_blackbar_buffers_28; /* +0x00000070  */
 uint32_t vi_blackbar_buffers_29; /* +0x00000074  */
 uint32_t vi_blackbar_buffers_30; /* +0x00000078  */
 uint32_t vi_blackbar_buffers_31; /* +0x0000007c  */
 uint32_t vi_blackbar_buffers_32; /* +0x00000080  */
 uint32_t vi_blackbar_buffers_33; /* +0x00000084  */
 uint32_t vi_blackbar_buffers_34; /* +0x00000088  */
 uint32_t vi_blackbar_buffers_35; /* +0x0000008c  */
 uint32_t vi_blackbar_buffers_36; /* +0x00000090  */
 uint32_t vi_blackbar_buffers_37; /* +0x00000094  */
 uint32_t vi_blackbar_buffers_38; /* +0x00000098  */
 uint32_t vi_blackbar_buffers_39; /* +0x0000009c  */
 uint32_t vi_blackbar_buffers_40; /* +0x000000a0  */
 uint32_t vi_blackbar_buffers_41; /* +0x000000a4  */
 uint32_t vi_blackbar_buffers_42; /* +0x000000a8  */
 uint32_t vi_blackbar_buffers_43; /* +0x000000ac  */
 uint32_t vi_blackbar_buffers_44; /* +0x000000b0  */
 uint32_t vi_blackbar_buffers_45; /* +0x000000b4  */
 uint32_t vi_blackbar_buffers_46; /* +0x000000b8  */
 uint32_t vi_blackbar_buffers_47; /* +0x000000bc  */
 uint32_t vi_blackbar_buffers_48; /* +0x000000c0  */
 uint32_t vi_blackbar_buffers_49; /* +0x000000c4  */
 uint32_t vi_blackbar_buffers_50; /* +0x000000c8  */
 uint32_t vi_blackbar_buffers_51; /* +0x000000cc  */
 uint32_t vi_blackbar_buffers_52; /* +0x000000d0  */
 uint32_t vi_blackbar_buffers_53; /* +0x000000d4  */
 uint32_t vi_blackbar_buffers_54; /* +0x000000d8  */
 uint32_t vi_blackbar_buffers_55; /* +0x000000dc  */
 uint32_t vi_blackbar_buffers_56; /* +0x000000e0  */
 uint32_t vi_blackbar_buffers_57; /* +0x000000e4  */
 uint32_t vi_blackbar_buffers_58; /* +0x000000e8  */
 uint32_t vi_blackbar_buffers_59; /* +0x000000ec  */
 uint32_t vi_blackbar_buffers_60; /* +0x000000f0  */
 uint32_t vi_blackbar_buffers_61; /* +0x000000f4  */
 uint32_t vi_blackbar_buffers_62; /* +0x000000f8  */
 uint32_t vi_blackbar_buffers_63; /* +0x000000fc  */
 uint32_t vi_blackbar_buffers_64; /* +0x00000100  */
 uint32_t vi_blackbar_buffers_65; /* +0x00000104  */
 uint32_t vi_blackbar_buffers_66; /* +0x00000108  */
 uint32_t vi_blackbar_buffers_67; /* +0x0000010c  */
 uint32_t vi_blackbar_buffers_68; /* +0x00000110  */
 uint32_t vi_blackbar_buffers_69; /* +0x00000114  */
 uint32_t vi_blackbar_buffers_70; /* +0x00000118  */
 uint32_t vi_blackbar_buffers_71; /* +0x0000011c  */
 uint32_t vi_blackbar_buffers_72; /* +0x00000120  */
 uint32_t vi_blackbar_buffers_73; /* +0x00000124  */
 uint32_t vi_blackbar_buffers_74; /* +0x00000128  */
 uint32_t vi_blackbar_buffers_75; /* +0x0000012c  */
 uint32_t vi_blackbar_buffers_76; /* +0x00000130  */
 uint32_t vi_blackbar_buffers_77; /* +0x00000134  */
 uint32_t vi_blackbar_buffers_78; /* +0x00000138  */
 uint32_t vi_blackbar_buffers_79; /* +0x0000013c  */
 uint32_t vi_blackbar_buffers_80; /* +0x00000140  */
 uint32_t vi_blackbar_buffers_81; /* +0x00000144  */
 uint32_t vi_blackbar_buffers_82; /* +0x00000148  */
 uint32_t vi_blackbar_buffers_83; /* +0x0000014c  */
 uint32_t vi_blackbar_buffers_84; /* +0x00000150  */
 uint32_t vi_blackbar_buffers_85; /* +0x00000154  */
 uint32_t vi_blackbar_buffers_86; /* +0x00000158  */
 uint32_t vi_blackbar_buffers_87; /* +0x0000015c  */
 uint32_t vi_blackbar_buffers_88; /* +0x00000160  */
 uint32_t vi_blackbar_buffers_89; /* +0x00000164  */
 uint32_t vi_blackbar_buffers_90; /* +0x00000168  */
 uint32_t vi_blackbar_buffers_91; /* +0x0000016c  */
 uint32_t vi_blackbar_buffers_92; /* +0x00000170  */
 uint32_t vi_blackbar_buffers_93; /* +0x00000174  */
 uint32_t vi_blackbar_buffers_94; /* +0x00000178  */
 uint32_t vi_blackbar_buffers_95; /* +0x0000017c  */
 uint32_t vi_blackbar_buffers_96; /* +0x00000180  */
 uint32_t vi_blackbar_buffers_97; /* +0x00000184  */
 uint32_t vi_blackbar_buffers_98; /* +0x00000188  */
 uint32_t vi_blackbar_buffers_99; /* +0x0000018c  */
 uint32_t vi_blackbar_buffers_100; /* +0x00000190  */
 uint32_t vi_blackbar_buffers_101; /* +0x00000194  */
 uint32_t vi_blackbar_buffers_102; /* +0x00000198  */
 uint32_t vi_blackbar_buffers_103; /* +0x0000019c  */
 uint32_t vi_blackbar_buffers_104; /* +0x000001a0  */
 uint32_t vi_blackbar_buffers_105; /* +0x000001a4  */
 uint32_t vi_blackbar_buffers_106; /* +0x000001a8  */
 uint32_t vi_blackbar_buffers_107; /* +0x000001ac  */
 uint32_t vi_blackbar_buffers_108; /* +0x000001b0  */
 uint32_t vi_blackbar_buffers_109; /* +0x000001b4  */
 uint32_t vi_blackbar_buffers_110; /* +0x000001b8  */
 uint32_t vi_blackbar_buffers_111; /* +0x000001bc  */
 uint32_t vi_blackbar_buffers_112; /* +0x000001c0  */
 uint32_t vi_blackbar_buffers_113; /* +0x000001c4  */
 uint32_t vi_blackbar_buffers_114; /* +0x000001c8  */
 uint32_t vi_blackbar_buffers_115; /* +0x000001cc  */
 uint32_t vi_blackbar_buffers_116; /* +0x000001d0  */
 uint32_t vi_blackbar_buffers_117; /* +0x000001d4  */
 uint32_t vi_blackbar_buffers_118; /* +0x000001d8  */
 uint32_t vi_blackbar_buffers_119; /* +0x000001dc  */
 uint32_t vi_blackbar_buffers_120; /* +0x000001e0  */
 uint32_t vi_blackbar_buffers_121; /* +0x000001e4  */
 uint32_t vi_blackbar_buffers_122; /* +0x000001e8  */
 uint32_t vi_blackbar_buffers_123; /* +0x000001ec  */
 uint32_t vi_blackbar_buffers_124; /* +0x000001f0  */
 uint32_t vi_blackbar_buffers_125; /* +0x000001f4  */
 uint32_t vi_blackbar_buffers_126; /* +0x000001f8  */
 uint32_t vi_blackbar_buffers_127; /* +0x000001fc  */
 uint32_t vi_blackbar_buffers_128; /* +0x00000200  */
 uint32_t vi_blackbar_buffers_129; /* +0x00000204  */
 uint32_t vi_blackbar_buffers_130; /* +0x00000208  */
 uint32_t vi_blackbar_buffers_131; /* +0x0000020c  */
 uint32_t vi_blackbar_buffers_132; /* +0x00000210  */
 uint32_t vi_blackbar_buffers_133; /* +0x00000214  */
 uint32_t vi_blackbar_buffers_134; /* +0x00000218  */
 uint32_t vi_blackbar_buffers_135; /* +0x0000021c  */
 uint32_t vi_blackbar_buffers_136; /* +0x00000220  */
 uint32_t vi_blackbar_buffers_137; /* +0x00000224  */
 uint32_t vi_blackbar_buffers_138; /* +0x00000228  */
 uint32_t vi_blackbar_buffers_139; /* +0x0000022c  */
 uint32_t vi_blackbar_buffers_140; /* +0x00000230  */
 uint32_t vi_blackbar_buffers_141; /* +0x00000234  */
 uint32_t vi_blackbar_buffers_142; /* +0x00000238  */
 uint32_t vi_blackbar_buffers_143; /* +0x0000023c  */
 uint32_t vi_blackbar_buffers_144; /* +0x00000240  */
 uint32_t vi_blackbar_buffers_145; /* +0x00000244  */
 uint32_t vi_blackbar_buffers_146; /* +0x00000248  */
 uint32_t vi_blackbar_buffers_147; /* +0x0000024c  */
 uint32_t vi_blackbar_buffers_148; /* +0x00000250  */
 uint32_t vi_blackbar_buffers_149; /* +0x00000254  */
 uint32_t vi_blackbar_buffers_150; /* +0x00000258  */
 uint32_t vi_blackbar_buffers_151; /* +0x0000025c  */
 uint32_t vi_blackbar_buffers_152; /* +0x00000260  */
 uint32_t vi_blackbar_buffers_153; /* +0x00000264  */
 uint32_t vi_blackbar_buffers_154; /* +0x00000268  */
 uint32_t vi_blackbar_buffers_155; /* +0x0000026c  */
 uint32_t vi_blackbar_buffers_156; /* +0x00000270  */
 uint32_t vi_blackbar_buffers_157; /* +0x00000274  */
 uint32_t vi_blackbar_buffers_158; /* +0x00000278  */
 uint32_t vi_blackbar_buffers_159; /* +0x0000027c  */
 uint32_t vi_blackbar_buffers_160; /* +0x00000280  */
 uint32_t vi_blackbar_buffers_161; /* +0x00000284  */
 uint32_t vi_blackbar_buffers_162; /* +0x00000288  */
 uint32_t vi_blackbar_buffers_163; /* +0x0000028c  */
 uint32_t vi_blackbar_buffers_164; /* +0x00000290  */
 uint32_t vi_blackbar_buffers_165; /* +0x00000294  */
 uint32_t vi_blackbar_buffers_166; /* +0x00000298  */
 uint32_t vi_blackbar_buffers_167; /* +0x0000029c  */
 uint32_t vi_blackbar_buffers_168; /* +0x000002a0  */
 uint32_t vi_blackbar_buffers_169; /* +0x000002a4  */
 uint32_t vi_blackbar_buffers_170; /* +0x000002a8  */
 uint32_t vi_blackbar_buffers_171; /* +0x000002ac  */
 uint32_t vi_blackbar_buffers_172; /* +0x000002b0  */
 uint32_t vi_blackbar_buffers_173; /* +0x000002b4  */
 uint32_t vi_blackbar_buffers_174; /* +0x000002b8  */
 uint32_t vi_blackbar_buffers_175; /* +0x000002bc  */
 uint32_t vi_blackbar_buffers_176; /* +0x000002c0  */
 uint32_t vi_blackbar_buffers_177; /* +0x000002c4  */
 uint32_t vi_blackbar_buffers_178; /* +0x000002c8  */
 uint32_t vi_blackbar_buffers_179; /* +0x000002cc  */
 uint32_t vi_blackbar_buffers_180; /* +0x000002d0  */
 uint32_t vi_blackbar_buffers_181; /* +0x000002d4  */
 uint32_t vi_blackbar_buffers_182; /* +0x000002d8  */
 uint32_t vi_blackbar_buffers_183; /* +0x000002dc  */
 uint32_t vi_blackbar_buffers_184; /* +0x000002e0  */
 uint32_t vi_blackbar_buffers_185; /* +0x000002e4  */
 uint32_t vi_blackbar_buffers_186; /* +0x000002e8  */
 uint32_t vi_blackbar_buffers_187; /* +0x000002ec  */
 uint32_t vi_blackbar_buffers_188; /* +0x000002f0  */
 uint32_t vi_blackbar_buffers_189; /* +0x000002f4  */
 uint32_t vi_blackbar_buffers_190; /* +0x000002f8  */
 uint32_t vi_blackbar_buffers_191; /* +0x000002fc  */
 uint32_t vi_blackbar_buffers_192; /* +0x00000300  */
 uint32_t vi_blackbar_buffers_193; /* +0x00000304  */
 uint32_t vi_blackbar_buffers_194; /* +0x00000308  */
 uint32_t vi_blackbar_buffers_195; /* +0x0000030c  */
 uint32_t vi_blackbar_buffers_196; /* +0x00000310  */
 uint32_t vi_blackbar_buffers_197; /* +0x00000314  */
 uint32_t vi_blackbar_buffers_198; /* +0x00000318  */
 uint32_t vi_blackbar_buffers_199; /* +0x0000031c  */
 uint32_t vi_blackbar_buffers_200; /* +0x00000320  */
 uint32_t vi_blackbar_buffers_201; /* +0x00000324  */
 uint32_t vi_blackbar_buffers_202; /* +0x00000328  */
 uint32_t vi_blackbar_buffers_203; /* +0x0000032c  */
 uint32_t vi_blackbar_buffers_204; /* +0x00000330  */
 uint32_t vi_blackbar_buffers_205; /* +0x00000334  */
 uint32_t vi_blackbar_buffers_206; /* +0x00000338  */
 uint32_t vi_blackbar_buffers_207; /* +0x0000033c  */
 uint32_t vi_blackbar_buffers_208; /* +0x00000340  */
 uint32_t vi_blackbar_buffers_209; /* +0x00000344  */
 uint32_t vi_blackbar_buffers_210; /* +0x00000348  */
 uint32_t vi_blackbar_buffers_211; /* +0x0000034c  */
 uint32_t vi_blackbar_buffers_212; /* +0x00000350  */
 uint32_t vi_blackbar_buffers_213; /* +0x00000354  */
 uint32_t vi_blackbar_buffers_214; /* +0x00000358  */
 uint32_t vi_blackbar_buffers_215; /* +0x0000035c  */
 uint32_t vi_blackbar_buffers_216; /* +0x00000360  */
 uint32_t vi_blackbar_buffers_217; /* +0x00000364  */
 uint32_t vi_blackbar_buffers_218; /* +0x00000368  */
 uint32_t vi_blackbar_buffers_219; /* +0x0000036c  */
 uint32_t vi_blackbar_buffers_220; /* +0x00000370  */
 uint32_t vi_blackbar_buffers_221; /* +0x00000374  */
 uint32_t vi_blackbar_buffers_222; /* +0x00000378  */
 uint32_t vi_blackbar_buffers_223; /* +0x0000037c  */
 uint32_t vi_blackbar_buffers_224; /* +0x00000380  */
 uint32_t vi_blackbar_buffers_225; /* +0x00000384  */
 uint32_t vi_blackbar_buffers_226; /* +0x00000388  */
 uint32_t vi_blackbar_buffers_227; /* +0x0000038c  */
 uint32_t vi_blackbar_buffers_228; /* +0x00000390  */
 uint32_t vi_blackbar_buffers_229; /* +0x00000394  */
 uint32_t vi_blackbar_buffers_230; /* +0x00000398  */
 uint32_t vi_blackbar_buffers_231; /* +0x0000039c  */
 uint32_t vi_blackbar_buffers_232; /* +0x000003a0  */
 uint32_t vi_blackbar_buffers_233; /* +0x000003a4  */
 uint32_t vi_blackbar_buffers_234; /* +0x000003a8  */
 uint32_t vi_blackbar_buffers_235; /* +0x000003ac  */
 uint32_t vi_blackbar_buffers_236; /* +0x000003b0  */
 uint32_t vi_blackbar_buffers_237; /* +0x000003b4  */
 uint32_t vi_blackbar_buffers_238; /* +0x000003b8  */
 uint32_t vi_blackbar_buffers_239; /* +0x000003bc  */
 uint32_t vi_blackbar_buffers_240; /* +0x000003c0  */
 uint32_t vi_blackbar_buffers_241; /* +0x000003c4  */
 uint32_t vi_blackbar_buffers_242; /* +0x000003c8  */
 uint32_t vi_blackbar_buffers_243; /* +0x000003cc  */
 uint32_t vi_blackbar_buffers_244; /* +0x000003d0  */
 uint32_t vi_blackbar_buffers_245; /* +0x000003d4  */
 uint32_t vi_blackbar_buffers_246; /* +0x000003d8  */
 uint32_t vi_blackbar_buffers_247; /* +0x000003dc  */
 uint32_t vi_blackbar_buffers_248; /* +0x000003e0  */
 uint32_t vi_blackbar_buffers_249; /* +0x000003e4  */
 uint32_t vi_blackbar_buffers_250; /* +0x000003e8  */
 uint32_t vi_blackbar_buffers_251; /* +0x000003ec  */
 uint32_t vi_blackbar_buffers_252; /* +0x000003f0  */
 uint32_t vi_blackbar_buffers_253; /* +0x000003f4  */
 uint32_t vi_blackbar_buffers_254; /* +0x000003f8  */
 uint32_t vi_blackbar_buffers_255; /* +0x000003fc  */
 union vi_blackbar_frame_sizeReg vi_blackbar_frame_size; /* +0x00000400  */
 union vi_blackbar_cfgReg vi_blackbar_cfg; /* +0x00000404  */
 uint32_t vi_blackbar_color; /* +0x00000408  */
 uint32_t vi_blackbar_range; /* +0x0000040c  */
 union vi_blackbar_outside_pixReg vi_blackbar_outside_pix; /* +0x00000410  */
};
