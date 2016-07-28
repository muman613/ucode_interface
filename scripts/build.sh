#!/bin/bash
################################################################################
#	Utility script to build all targets in a text GUI.
################################################################################

if [ -f makeall.sh ]; then
./makeall.sh | tee buildlog |  dialog --backtitle "Interface Build Tools"		\
                                      --title "Build Output" --programbox 40 128
else
	echo "No makeall.sh script found!"
fi
