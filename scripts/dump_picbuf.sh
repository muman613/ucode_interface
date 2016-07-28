#!/bin/bash
################################################################################
#	Dump Picture Buffers
################################################################################

function get_scheduler_data_start {
	LABELS_H=$1
	SDS_PTR_LO=$(printf "0x%X" $((0x100000 + $(cat $LABELS_H | grep -i SchedulerDataStart__gbus_addr_lo | awk '{ print $3 }'))))
	SDS_PTR_HI=$(printf "0x%X" $((0x100000 + $(cat $LABELS_H | grep -i SchedulerDataStart__gbus_addr_hi | awk '{ print $3 }'))))

	SDS_LO=$(printf "%X" $(gbus_read_uint32 $SDS_PTR_LO))
	SDS_HI=$(printf "%X" $(gbus_read_uint32 $SDS_PTR_HI))
#	echo "Scheduler_Data_Start_lo = $SDS_PTR_LO"
#	echo "Scheduler_Data_Start_hi = $SDS_PTR_HI"
#	echo "Scheduler_Data_Start = $SDS_HI$SDS_LO"
	echo "0x$SDS_HI$SDS_LO"
}

function get_video_task_database {
	SDS=$1
	VTDB_PTR=$(printf "0x%X" $(($SDS + 4)))
	VTDB=$(gbus_read_uint32 $VTDB_PTR | tr 'a-f' 'A-F')
	echo "$VTDB"
}

function dump_picture_buffer {
	PICBUF=$1
	LUMA_BUFFER_PTR=$(printf "0x%X" $(($PICBUF + 0x4)))
	CHROMA_BUFFER_PTR=$(printf "0x%X" $(($PICBUF + 0xc)))
	LUMA_BUFFER=$(gbus_read_uint32 $LUMA_BUFFER_PTR | tr 'a-f' 'A-F')
	CHROMA_BUFFER=$(gbus_read_uint32 $CHROMA_BUFFER_PTR | tr 'a-f' 'A-F')
	echo "Picture Buffer     @ $PICBUF"
	echo "    Luma Buffer    @ $LUMA_BUFFER"
	echo "    Chroma Buffer  @ $CHROMA_BUFFER"
}

#VTDB=$1
LABELS=$1


SCHEDULER_DATA_START=$(get_scheduler_data_start $LABELS)

VTDB=$(get_video_task_database $SCHEDULER_DATA_START)

#DISP_FIFO=0xc0083c6c

DISP_FIFO=$(printf "0x%X" $(($VTDB + 0x84)))

echo "Scheduler Data Start @ $SCHEDULER_DATA_START"
echo "Video Task Database  @ $VTDB"
echo "Display FIFO         @ $DISP_FIFO"
echo "---------------------------------------------------"

val=$(gbus_read_uint32 $DISP_FIFO)

for ((i = 0 ; i < 0x21 ; i++))
{
#	echo "$i - $val"
	
	PICBUF=$(gbus_read_uint32 $val | tr 'a-f' 'A-F')

	dump_picture_buffer $PICBUF	
	
	val=$(printf "0x%x" $(($val + 4)))
	
	echo "---------------------------------------------------"
}

