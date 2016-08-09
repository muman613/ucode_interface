#!/bin/bash
################################################################################
#	Utility script to build all targets in a text GUI.
################################################################################

eval $( resize )
HEIGHT=$(($LINES - 6))


if [ -f buildoptions ]; then
makeall.sh | tee buildlog |  dialog --backtitle "Interface Build Tools"		\
                                      --title "Build Output" --programbox $HEIGHT 128
else
./makeall.sh | tee buildlog |  dialog --backtitle "Interface Build Tools"		\
                                      --title "Build Output" --programbox $HEIGHT 128
fi
