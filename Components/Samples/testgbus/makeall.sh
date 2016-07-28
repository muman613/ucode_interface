#!/bin/bash
################################################################################
#	Build all combinations of target
#
#	*̶ ̶x̶8̶6̶_̶6̶4̶ ̶D̶e̶b̶u̶g̶
#	*̶ ̶x̶8̶6̶_̶6̶4̶ ̶R̶e̶l̶e̶a̶s̶e̶
#	* x86 Debug
#	* x86 Release
#
################################################################################

ARCH_ARRAY=( 'ARCH=x86' )
DBG_ARRAY=( 'NDEBUG=1' 'DEBUG=1')

if [ -t 1 ]; then
	clear
fi

for dbg in ${DBG_ARRAY[@]}; do
	for arch in ${ARCH_ARRAY[@]}; do
		make $arch $dbg clean
		make $arch $dbg
	done
done


