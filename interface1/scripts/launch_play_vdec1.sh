#!/bin/bash

CODEC=$1
MEDIA=$2
UCODE_PATH=ucode/debug/video_microcode_SMP8760.bin
BASENAME=$(basename "$MEDIA")
CAPTURE=/tmp/"${BASENAME%.*}".yuv


echo "Playing $MEDIA..."
echo "Capture to file $CAPTURE"

./test_interface -e 1 -p $CODEC -b $UCODE_PATH -s $MEDIA -o $CAPTURE 2>&1 | tee log 

