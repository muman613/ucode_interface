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

ARCH_ARRAY=( 'ARCH=x86_64' 'ARCH=x86' )
DBG_ARRAY=( 'NDEBUG=1' 'DEBUG=1')

if [ -t 1 ]; then
	clear
fi

for dbg in ${DBG_ARRAY[@]}; do
	for arch in ${ARCH_ARRAY[@]}; do
		make 2>&1 $arch $dbg clean
		make 2>&1 $arch $dbg
	done
done

