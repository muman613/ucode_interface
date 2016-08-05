#!/bin/bash
################################################################################
#	Utility script to build all targets in a text GUI.
################################################################################

if [ -f buildoptions ]; then
makeall.sh | tee buildlog |  dialog --backtitle "Interface Build Tools"		\
                                      --title "Build Output" --programbox 40 128
else
./makeall.sh | tee buildlog |  dialog --backtitle "Interface Build Tools"		\
                                      --title "Build Output" --programbox 40 128
fi
