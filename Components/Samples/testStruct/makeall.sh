#!/bin/bash
################################################################################
#	Build all combinations of library
#
#	* x86_64 Debug
#	* x86_64 Release
#	* x86 Debug
#	* x86 Release
#
################################################################################

ARCH=x86_64 make clean
ARCH=x86_64 DEBUG=1 make clean
ARCH=x86 make clean
ARCH=x86 DEBUG=1 make clean

touch sc_lexer.h sc_tcalc.hpp

ARCH=x86_64 make
ARCH=x86_64 DEBUG=1 make
ARCH=x86 make
ARCH=x86 DEBUG=1 make


