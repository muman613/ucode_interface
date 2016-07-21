#	Some crazy aliases

alias pbusopen='xkc pbusopen'

#	MPEG Engine control aliases
alias mpeg_reset='gbus_write_uint32 0x80ffc 0x3'
alias mpeg_stop='gbus_write_uint32 0x80ffc 0x1'
alias mpeg_start='gbus_write_uint32 0x80ffc 0x0'

# Playback control aliases
alias send_uninit_cmd='gbus_write_uint32 0x8c083748 0x0'
alias send_init_cmd='gbus_write_uint32 0x8c083748 0x1'
alias send_stop_cmd='gbus_write_uint32 0x8c083748 0x2'
alias send_play_cmd='gbus_write_uint32 0x8c083748 0x3'
alias get_status='gbus_read_uint32 0x8c08374c'

# Fill & Dump aliases
alias fillpm='gbus_fill 0x100000 0 4096'
alias dumppm='em8600_dump 0x100000 4096'


alias runtest='test_interface -b /mnt/storage/video_microcode_SMP8910_release.bin -s stream 2> /mnt/storage/log'
