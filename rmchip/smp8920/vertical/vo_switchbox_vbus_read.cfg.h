/* autogenerated with parsecfg: do not edit. */

union vo_sboxvbusrd_disconnect_cmdReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_sboxvbusrd_disconnect_cmd_id_SHIFT 0
#define vo_sboxvbusrd_disconnect_cmd_id_WIDTH 6
#define vo_sboxvbusrd_disconnect_cmd_type_SHIFT 8
#define vo_sboxvbusrd_disconnect_cmd_type_WIDTH 2

 id:6, /*[5:0]  */
 hole0:2,
 type:2, /*[9:8]  */
 hole1:22;
 } bits;

 uint32_t value;
};

union vo_sboxvbusrd_connect_cmdReg {
 struct { uint32_t

 /* sorting 2 */
#define vo_sboxvbusrd_connect_cmd_dest_SHIFT 0
#define vo_sboxvbusrd_connect_cmd_dest_WIDTH 6
#define vo_sboxvbusrd_connect_cmd_source_SHIFT 8
#define vo_sboxvbusrd_connect_cmd_source_WIDTH 6

 dest:6, /*[5:0]  */
 hole0:2,
 source:6, /*[13:8]  */
 hole1:18;
 } bits;

 uint32_t value;
};

struct vo_switchbox_vbus_read {
 union vo_sboxvbusrd_connect_cmdReg vo_sboxvbusrd_connect_cmd; /* +0x00000000  */
 union vo_sboxvbusrd_disconnect_cmdReg vo_sboxvbusrd_disconnect_cmd; /* +0x00000004  */
 uint32_t vo_sboxvbusrd_source_0; /* +0x00000008  */
 uint32_t vo_sboxvbusrd_source_1; /* +0x0000000c  */
 uint32_t vo_sboxvbusrd_source_2; /* +0x00000010  */
 uint32_t vo_sboxvbusrd_source_3; /* +0x00000014  */
 uint32_t vo_sboxvbusrd_source_4; /* +0x00000018  */
 uint32_t vo_sboxvbusrd_source_5; /* +0x0000001c  */
 uint32_t vo_sboxvbusrd_source_6; /* +0x00000020  */
 uint32_t vo_sboxvbusrd_source_7; /* +0x00000024  */
 uint32_t vo_sboxvbusrd_source_8; /* +0x00000028  */
 uint32_t vo_sboxvbusrd_source_9; /* +0x0000002c  */
 uint32_t vo_sboxvbusrd_source_10; /* +0x00000030  */
 uint32_t vo_sboxvbusrd_source_11; /* +0x00000034  */
 uint32_t vo_sboxvbusrd_source_12; /* +0x00000038  */
 uint32_t vo_sboxvbusrd_source_13; /* +0x0000003c  */
 uint32_t vo_sboxvbusrd_source_14; /* +0x00000040  */
 uint32_t vo_sboxvbusrd_source_15; /* +0x00000044  */
 uint32_t vo_sboxvbusrd_source_16; /* +0x00000048  */
 uint32_t vo_sboxvbusrd_source_17; /* +0x0000004c  */
 uint32_t vo_sboxvbusrd_source_18; /* +0x00000050  */
 uint32_t vo_sboxvbusrd_source_19; /* +0x00000054  */
 uint32_t vo_sboxvbusrd_source_20; /* +0x00000058  */
 uint32_t vo_sboxvbusrd_source_21; /* +0x0000005c  */
 uint32_t vo_sboxvbusrd_source_22; /* +0x00000060  */
 uint32_t vo_sboxvbusrd_source_23; /* +0x00000064  */
 uint32_t vo_sboxvbusrd_source_24; /* +0x00000068  */
 uint32_t vo_sboxvbusrd_source_25; /* +0x0000006c  */
 uint32_t vo_sboxvbusrd_source_26; /* +0x00000070  */
 uint32_t vo_sboxvbusrd_source_27; /* +0x00000074  */
 uint32_t vo_sboxvbusrd_source_28; /* +0x00000078  */
 uint32_t vo_sboxvbusrd_source_29; /* +0x0000007c  */
 uint32_t vo_sboxvbusrd_source_30; /* +0x00000080  */
 uint32_t vo_sboxvbusrd_source_31; /* +0x00000084  */
 uint32_t vo_sboxvbusrd_dest_0; /* +0x00000088  */
 uint32_t vo_sboxvbusrd_dest_1; /* +0x0000008c  */
 uint32_t vo_sboxvbusrd_dest_2; /* +0x00000090  */
 uint32_t vo_sboxvbusrd_dest_3; /* +0x00000094  */
 uint32_t vo_sboxvbusrd_dest_4; /* +0x00000098  */
 uint32_t vo_sboxvbusrd_dest_5; /* +0x0000009c  */
 uint32_t vo_sboxvbusrd_dest_6; /* +0x000000a0  */
 uint32_t vo_sboxvbusrd_dest_7; /* +0x000000a4  */
 uint32_t vo_sboxvbusrd_dest_8; /* +0x000000a8  */
 uint32_t vo_sboxvbusrd_dest_9; /* +0x000000ac  */
 uint32_t vo_sboxvbusrd_dest_10; /* +0x000000b0  */
 uint32_t vo_sboxvbusrd_dest_11; /* +0x000000b4  */
 uint32_t vo_sboxvbusrd_dest_12; /* +0x000000b8  */
 uint32_t vo_sboxvbusrd_dest_13; /* +0x000000bc  */
 uint32_t vo_sboxvbusrd_dest_14; /* +0x000000c0  */
 uint32_t vo_sboxvbusrd_dest_15; /* +0x000000c4  */
 uint32_t vo_sboxvbusrd_dest_16; /* +0x000000c8  */
 uint32_t vo_sboxvbusrd_dest_17; /* +0x000000cc  */
 uint32_t vo_sboxvbusrd_dest_18; /* +0x000000d0  */
 uint32_t vo_sboxvbusrd_dest_19; /* +0x000000d4  */
 uint32_t vo_sboxvbusrd_dest_20; /* +0x000000d8  */
 uint32_t vo_sboxvbusrd_dest_21; /* +0x000000dc  */
 uint32_t vo_sboxvbusrd_dest_22; /* +0x000000e0  */
 uint32_t vo_sboxvbusrd_dest_23; /* +0x000000e4  */
 uint32_t vo_sboxvbusrd_dest_24; /* +0x000000e8  */
 uint32_t vo_sboxvbusrd_dest_25; /* +0x000000ec  */
 uint32_t vo_sboxvbusrd_dest_26; /* +0x000000f0  */
 uint32_t vo_sboxvbusrd_dest_27; /* +0x000000f4  */
 uint32_t vo_sboxvbusrd_dest_28; /* +0x000000f8  */
 uint32_t vo_sboxvbusrd_dest_29; /* +0x000000fc  */
 uint32_t vo_sboxvbusrd_dest_30; /* +0x00000100  */
 uint32_t vo_sboxvbusrd_dest_31; /* +0x00000104  */
};
