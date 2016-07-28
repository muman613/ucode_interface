#!/bin/bash

CHIP=SMP8760
SPBIN=/utils/em8xxx/spbin/1.2.16c/bin/spbin


if [ -z ${RUAPATH} ]; then
	echo "\$RUAPATH must be set to RUA path!"
	exit
fi

if [ "$#" -ne 1 ]; then
	echo "Must specify 'release' or 'debug' to copy to..."
	exit
fi

BUILDTYPE=$(echo $1 | tr '[:upper:]' '[:lower:]')

if [ "$BUILDTYPE" != "release" ] && [ "$BUILDTYPE" != "debug" ] ; then
	echo "Must specify 'release' or 'debug' to copy to..."
	exit
fi

if [ "$BUILDTYPE" == "release" ]; then
	DEST="ucode/release"
fi
if [ "$BUILDTYPE" == "debug" ]; then
	DEST="ucode/debug"
fi


echo "Copying from $RUAPATH..."
#echo "$DEST"

cp -v $RUAPATH/ucode_video/video_t5/src/video_microcode_${CHIP}* ${DEST}
cp -v $RUAPATH/ucode_video/video_t5/api/include/video_interface.h ${DEST}


