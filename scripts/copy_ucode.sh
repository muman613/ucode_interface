#!/bin/bash
################################################################################
#	MODULE		:	copy_ucode.sh
#	VERSION		:	2.0
#	PROJECT		:	Microcode Interface Project
#	DATE		:	August 10th, 2016
#	PROGRAMMER	:	Michael A. Uman
#	COPYRIGHT	:	(C) 2016 Sigma Designs
################################################################################

#	Determine the scripts full path in order to locate the destination dir
SCRIPTSPEC=$(readlink -f $0)
PROJECTROOT=$(dirname $(dirname $SCRIPTSPEC))

###
#	Get the chip selection from the user
###

get_chip () {
#	echo "get_chip"
	local CHIPSPEC

	CHIPSPEC=$(dialog --backtitle "Copy Microcode Script" 					\
                      --title "Select Chip" 								\
                      --menu "Select Chip" 20 80 10 						\
                      "8756" "Chablis"										\
                      "8758" "Riesling B"									\
                      "8760" "Riesling C" 									\
                      --output-fd 1)
	if [ "$?" -eq "1" ]; then
		exit
	fi
	echo "$CHIPSPEC"
}

###
#
###

get_ruapath () {
	local PATHSPEC

	PATHSPEC=$(dialog --backtitle "Copy Microcode Script" 					\
                      --title "Select RUAPATH" 								\
                      --dselect $HOME 20 80 --output-fd 1)
	if [ "$?" -eq "1" ]; then
		exit
	fi
	echo "$PATHSPEC"
}

###
#
###

get_buildtype () {
#	echo "get_chip"
	local BUILDSPEC

	BUILDSPEC=$(dialog --backtitle "Copy Microcode Script"					\
					   --title "Select Build Type" 							\
                       --menu "Select Build Type" 20 80 10 					\
                       "debug"   "Debug build" 								\
                       "release" "Release build" --output-fd 1)
	if [ "$?" -eq "1" ]; then
		exit
	fi
	echo "$BUILDSPEC"
}

###
#	Make all destination directories if they don't already exist.
###

make_dest_dirs () {
	ROOT="$1/ucode"
	CHIPS=( "8758" "8760" )
	BUILDS=( "debug" "release" )

	if [ ! -d "${ROOT}" ]; then
		echo "Making top-level dest directory..."
		mkdir "${ROOT}"
	fi

	for chip in "${CHIPS[@]}"; do
#		DIR="${ROOT}/${chip}/${build}"
		for build in "${BUILDS[@]}"; do
			DIR="${ROOT}/${chip}/${build}"
			if [ ! -d "${DIR}" ]; then
				echo "Making sub-directory ${DIR}..."
				mkdir -p "${DIR}"
			fi
		done
	done
}

###
#	Copy all files from the source to the dest...
###

do_copy_files () {
	#echo "do_copy_files"

	case ${CHIP} in
	8756)
		UCODE_DIRS=( video_t4/src video_t4_h265/src )
		DEST="${PROJECTROOT}/ucode/8756/"
		;;
	8758)
		UCODE_DIRS=( video_t4/src video_t4_h265/src )
		DEST="${PROJECTROOT}/ucode/8758/"
		;;
	8760)
		UCODE_DIRS=( video_t5/src )
		DEST="${PROJECTROOT}/ucode/8760/"
		;;
	esac

	if [ "${BUILDTYPE}" == "debug" ]; then
		DEST+="debug/"
	elif [ "${BUILDTYPE}" == "release" ]; then
		DEST+="release/"
	fi

	FILESPF=( ".bin" "_debug.bin" "_labels.h" ".lst" ".map" "_h265.bin" "_h265_debug.bin" "_h265_labels.h" "_h265.lst" "_h265.map" )
	SRCPATH="${RUAPATH}ucode_video/${UCODE_DIRS[0]}"
	UCODEBASE="video_microcode_${FULLCHIP}"

	if [ ! -f "${SRCPATH}/$UCODEBASE.bin" ]; then
		echo "No bin file found in ${SRCPATH}..."
		exit
	fi

	echo "CHIP        : ${CHIP}"
	echo "FULLCHIP    : ${FULLCHIP}"
	echo "RUAPATH     : ${RUAPATH}"
	echo "BUILDTYPE   : ${BUILDTYPE}"
	echo "DEST        : ${DEST}"
	echo "PROJECTROOT : ${PROJECTROOT}"
	echo "SRCPATH     : ${SRCPATH}"
	echo "UCODEBASE   : ${UCODEBASE}"

	make_dest_dirs "${PROJECTROOT}"

	for ucd in "${UCODE_DIRS[@]}"; do
		for pf in "${FILESPF[@]}"; do
			SRCPATH="${RUAPATH}ucode_video/${ucd}"
			SOURCEFILE="${SRCPATH}/${UCODEBASE}${pf}"
			if [ -f "${SOURCEFILE}" ]; then
				echo "Copying ${UCODEBASE}${pf}..."
#				echo cp "${SOURCEFILE}" "${DEST}"
				cp 2>&1 > /dev/null "${SOURCEFILE}" "${DEST}"
			fi
		done
	done
	
	echo "Copying video_interface.hh..."
	cp 2>&1 > /dev/null "${SRCPATH}/video_interface.hh" "${DEST}/.."
}

###
#	Start of main shell script
###

RUAPATH=$(get_ruapath)
if [ -z ${RUAPATH} ]; then
#	echo "\$RUAPATH must be set to RUA path!"
	exit
fi

CHIP=$(get_chip)
if [ -z ${CHIP} ]; then
	clear
	exit
fi

FULLCHIP="SMP$CHIP"

BUILDTYPE=$(get_buildtype)
if [ -z "${BUILDTYPE}" ]; then
	clear
	exit
fi

if [ "$BUILDTYPE" != "release" ] && [ "$BUILDTYPE" != "debug" ] ; then
	echo "Must specify 'release' or 'debug' to copy to..."
	exit
fi

clear

do_copy_files


