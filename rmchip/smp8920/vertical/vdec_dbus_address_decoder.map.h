/* autogenerated with parsemap: do not edit. */
struct vdec_dbus_address_decoder_dbus {
                              uint32_t pad0[14336/4];
#define vdec_dbus_address_decoder_dbus_vdec_blackbar_detect_OFF 0x00003800
/* [0x00003800,0x00003908[ */ struct { struct vdec_blackbar_detect_det d; uint32_t w[(0x00000108-sizeof(struct vdec_blackbar_detect_det))/4]; } _vdec_blackbar_detect;
#define vdec_dbus_address_decoder_dbus_vdec_block_transform_OFF 0x00003908
/* [0x00003908,0x00003909[ */ struct { struct vdec_block_transform_det d; uint32_t w[(0x00000001-sizeof(struct vdec_block_transform_det))/4]; } _vdec_block_transform;
                              uint32_t pad1[3/4];
#define vdec_dbus_address_decoder_dbus_vdec_clock_gate_top_multicycle_OFF 0x0000390c
/* [0x0000390c,0x0000390d[ */ struct { struct vdec_clock_gate_top_multicycle_det d; uint32_t w[(0x00000001-sizeof(struct vdec_clock_gate_top_multicycle_det))/4]; } _vdec_clock_gate_top_multicycle;
                              uint32_t pad2[51/4];
#define vdec_dbus_address_decoder_dbus_vdec_horizontal_scaler_OFF 0x00003940
/* [0x00003940,0x00003980[ */ struct { struct vdec_horizontal_scaler_det d; uint32_t w[(0x00000040-sizeof(struct vdec_horizontal_scaler_det))/4]; } _vdec_horizontal_scaler;
#define vdec_dbus_address_decoder_dbus_vdec_vertical_scaler_OFF 0x00003980
/* [0x00003980,0x000039c0[ */ struct { struct vdec_vertical_scaler_det d; uint32_t w[(0x00000040-sizeof(struct vdec_vertical_scaler_det))/4]; } _vdec_vertical_scaler;
#define vdec_dbus_address_decoder_dbus_vdec_gbus_interface_OFF 0x000039c0
/* [0x000039c0,0x00003a00[ */ struct { struct vdec_gbus_interface_det d; uint32_t w[(0x00000040-sizeof(struct vdec_gbus_interface_det))/4]; } _vdec_gbus_interface;
                              uint32_t pad3[256/4];
#define vdec_dbus_address_decoder_dbus_vdec_command_sequencer_OFF 0x00003b00
/* [0x00003b00,0x00003ba0[ */ struct { struct vdec_command_sequencer_det d; uint32_t w[(0x000000a0-sizeof(struct vdec_command_sequencer_det))/4]; } _vdec_command_sequencer;
                              uint32_t pad4[96/4];
#define vdec_dbus_address_decoder_dbus_vdec_motion_vectors_predictor_OFF 0x00003c00
/* [0x00003c00,0x00003d90[ */ struct { struct vdec_motion_vectors_predictor_det d; uint32_t w[(0x00000190-sizeof(struct vdec_motion_vectors_predictor_det))/4]; } _vdec_motion_vectors_predictor;
                              uint32_t pad5[112/4];
#define vdec_dbus_address_decoder_dbus_vdec_h264_inv_trans_or_mpeg_qmatrix_arbiter_OFF 0x00003e00
/* [0x00003e00,0x00003e80[ */ struct { struct vdec_h264_inv_trans_or_mpeg_qmatrix_arbiter_det d; uint32_t w[(0x00000080-sizeof(struct vdec_h264_inv_trans_or_mpeg_qmatrix_arbiter_det))/4]; } _vdec_h264_inv_trans_or_mpeg_qmatrix_arbiter;
#define vdec_dbus_address_decoder_dbus_vdec_mbus_interface_wr_OFF 0x00003e80
/* [0x00003e80,0x00003ec0[ */ struct { struct vdec_mbus_interface_wr_det d; uint32_t w[(0x00000040-sizeof(struct vdec_mbus_interface_wr_det))/4]; } _vdec_mbus_interface_wr;
#define vdec_dbus_address_decoder_dbus_vdec_mbus_interface_rd_OFF 0x00003ec0
/* [0x00003ec0,0x00003f00[ */ struct { struct vdec_mbus_interface_rd_det d; uint32_t w[(0x00000040-sizeof(struct vdec_mbus_interface_rd_det))/4]; } _vdec_mbus_interface_rd;
#define vdec_dbus_address_decoder_dbus_vdec_huffman_OFF 0x00003f00
/* [0x00003f00,0x00003f20[ */ struct { struct vdec_huffman_det d; uint32_t w[(0x00000020-sizeof(struct vdec_huffman_det))/4]; } _vdec_huffman;
                              uint32_t pad6[64/4];
#define vdec_dbus_address_decoder_dbus_vdec_sub_picture_OFF 0x00003f60
/* [0x00003f60,0x00003f68[ */ struct { struct vdec_sub_picture_det d; uint32_t w[(0x00000008-sizeof(struct vdec_sub_picture_det))/4]; } _vdec_sub_picture;
                              uint32_t pad7[8/4];
#define vdec_dbus_address_decoder_dbus_vdec_wmv9_dbk_OFF 0x00003f70
/* [0x00003f70,0x00003f78[ */ struct { struct vdec_wmv9_dbk_det d; uint32_t w[(0x00000008-sizeof(struct vdec_wmv9_dbk_det))/4]; } _vdec_wmv9_dbk;
                              uint32_t pad8[8/4];
#define vdec_dbus_address_decoder_dbus_vdec_acdc_pred_OFF 0x00003f80
/* [0x00003f80,0x00003f90[ */ struct { struct vdec_acdc_pred_det d; uint32_t w[(0x00000010-sizeof(struct vdec_acdc_pred_det))/4]; } _vdec_acdc_pred;
                              uint32_t pad9[8/4];
#define vdec_dbus_address_decoder_dbus_vdec_crc32_spy_OFF 0x00003f98
/* [0x00003f98,0x00003fa0[ */ struct { struct vdec_crc32_spy_det d; uint32_t w[(0x00000008-sizeof(struct vdec_crc32_spy_det))/4]; } _vdec_crc32_spy;
#define vdec_dbus_address_decoder_dbus_vdec_avs_motion_vector_helper_OFF 0x00003fa0
/* [0x00003fa0,0x00003fc0[ */ struct { struct vdec_avs_motion_vector_helper_det d; uint32_t w[(0x00000020-sizeof(struct vdec_avs_motion_vector_helper_det))/4]; } _vdec_avs_motion_vector_helper;
#define vdec_dbus_address_decoder_dbus_vdec_misc_OFF 0x00003fc0
/* [0x00003fc0,0x00004000[ */ struct { struct vdec_misc_det d; uint32_t w[(0x00000040-sizeof(struct vdec_misc_det))/4]; } _vdec_misc;
};
