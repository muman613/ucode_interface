#!/bin/bash
################################################################################
#	Build all combinations of library
#
#	* x86 Debug
#	* x86 Release
#
################################################################################

make clean
DEBUG=1 make clean

make
DEBUG=1 make


