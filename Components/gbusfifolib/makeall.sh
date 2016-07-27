#!/bin/bash
################################################################################
#	Build all combinations of library
#
#	*̶ ̶x̶8̶6̶_̶6̶4̶ ̶D̶e̶b̶u̶g̶
#	*̶ ̶x̶8̶6̶_̶6̶4̶ ̶R̶e̶l̶e̶a̶s̶e̶
#	* x86 Debug
#	* x86 Release
#
################################################################################

make clean
DEBUG=1 make clean

make
DEBUG=1 make


