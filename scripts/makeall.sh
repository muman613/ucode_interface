#!/bin/bash
################################################################################
#	Build all combinations of target
#
#	* x86_64 Debug
#	* x86_64 Release
#	* x86 Debug
#	* x86 Release
#
################################################################################

#	Function allows buildoptions to specify files to be touched on clean build.
function touch_files() {
	FILES=("$@")

	for file in ${FILES[@]}; do
		touch $file
	done
}

#	If running without a pipe, clear the terminal...
if [ -t 1 ]; then
	clear
fi

LINK_ARRAY=( 'STATIC=1' )

if [ -f buildoptions ]; then
. buildoptions
else
echo "No buildoptions found, building all configurations..."
ARCH_ARRAY=( 'ARCH=x86_64' 'ARCH=x86' )
DBG_ARRAY=( 'NDEBUG=1' 'DEBUG=1')
fi

for link in ${LINK_ARRAY[@]}; do
	for dbg in ${DBG_ARRAY[@]}; do
		for arch in ${ARCH_ARRAY[@]}; do
			if [ "$CLEAN" == "1" ]; then
				make 2>&1 ${arch} ${dbg} ${link} clean
				if [ -n "${TOUCH_FILES}" ]; then
					touch_files "${TOUCH_FILES[@]}"
				fi
			fi
			make 2>&1 ${arch} ${dbg} ${link}
		done
	done
done

