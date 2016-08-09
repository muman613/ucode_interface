################################################################################
#	Nakefile
################################################################################

#	Get the current makefile to MAKEFILE
where-am-i = $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
MAKEFILE := $(call where-am-i)

TARGET_TYPE=statlib
ARCH?=$(shell arch)


ifdef DEBUG
LIBNAME=libstructcontrol_d
else
LIBNAME=libstructcontrol
endif

CPP_SOURCES = 	sc_lexer.cpp				\
				sc_tcalc.cpp				\
				structure_control.cpp

#LIBXML2_CFLAGS=$(shell xml2-config --cflags)
#LIBXML2_LDFLAGS=$(shell xml2-config --libs)

CFLAGS=$(LIBXML2_CFLAGS) -std=c++11
LDFLAGS=$(LIBXML2_LDFLAGS)

LIB_DIR=../libs/Linux/$(ARCH)

ADD_CLEAN_FILES=sc_lexer.cpp sc_lexer.h sc_tcalc.cpp sc_tcalc.hpp

include ../../Build/buildsys.mk

sc_tcalc.cpp: sc_tcalc.y
	@$(YACC) -o sc_tcalc.cpp -d sc_tcalc.y

sc_lexer.cpp: sc_lexer.l sc_tcalc.cpp
	@$(LEX) -o sc_lexer.cpp -L --header-file=sc_lexer.h sc_lexer.l
	
-include $(DEPS)
