################################################################################
#	FILE			:	Makefile
#	PROJECT			:	testEngine
#	AUTHOR			:	Michael A. Uman
#	DESCRIPTION		:	Testing new targetEngine component
#	DATE			:	July 28, 2016
#	COPYRIGHT		:	(C) 2016 Sigma Designs, Inc.
################################################################################

#	Get the current makefile to MAKEFILE
where-am-i = $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
MAKEFILE := $(call where-am-i)

ARCH?=$(shell arch)
TARGET_TYPE=exe
TARGET_EXE=testEngine

CPP_SOURCES=main.cpp

ifdef DEBUG
PLATLIB_LIBS=../../libs/Linux/$(ARCH)/libsmpplatform_d.a
PLATDB_LIBS=../../libs/Linux/$(ARCH)/libplatformdb2_d.a
RCLIENT_LIBS=../../libs/Linux/$(ARCH)/libremote_d.a -lpthread
GBUSFIFO_LIBS=../../libs/Linux/$(ARCH)/libgbusfifo_d.a 
SYMMGR_LIBS=../../libs/Linux/$(ARCH)/libsymbolmgr_d.a -lpthread
STRUCT_LIBS=../../libs/Linux/$(ARCH)/libstructcontrol_d.a
RESOLV_LIBS=../../libs/Linux/$(ARCH)/libfileresolver_d.a

CPP_SOURCES+=../common/dbgimplementation.cpp
else
PLATLIB_LIBS=../../libs/Linux/$(ARCH)/libsmpplatform.a
PLATDB_LIBS=../../libs/Linux/$(ARCH)/libplatformdb2.a
RCLIENT_LIBS=../../libs/Linux/$(ARCH)/libremote.a
GBUSFIFO_LIBS=../../libs/Linux/$(ARCH)/libgbusfifo.a
SYMMGR_LIBS=../../libs/Linux/$(ARCH)/libsymbolmgr.a
STRUCT_LIBS=../../libs/Linux/$(ARCH)/libstructcontrol.a
RESOLV_LIBS=../../libs/Linux/$(ARCH)/libfileresolver.a
endif

TRE_CFLAGS=-I../../include
TRE_LIBS=../../libs/Linux/$(ARCH)/libtre.a

#PLATDB_CFLAGS=-I../../platformDB2/
#RCLIENT_CFLAGS=-I../../remote_client
PLATLIB_CFLAGS=-I../../smpPlatformLib/
GBUSFIFO_CFLAGS=-I../../gbusfifolib/
LIBXML_CFLAGS=$(shell pkg-config libxml-2.0 --cflags)
LIBXML_LIBS=$(shell pkg-config libxml-2.0 --libs)

INCLUDES=-I../.. -I../../.. $(PLATLIB_CFLAGS) $(GBUSFIFO_CFLAGS)

CFLAGS=$(INCLUDES) $(LIBXML_CFLAGS) $(TRE_CFLAGS) -std=c++11
LIBS=$(PLATLIB_LIBS) $(PLATDB_LIBS) $(RCLIENT_LIBS) $(SYMMGR_LIBS)				\
     $(STRUCT_LIBS) $(RESOLV_LIBS) $(LIBXML_LIBS) $(GBUSFIFO_LIBS) $(TRE_LIBS)

include ../../../Build/buildsys.mk

info:
	@echo "PLATDB_CFLAGS = $(PLATDB_CFLAGS)"
	@echo "PLATDB_LIBS   = $(PLATDB_LIBS)"
	@echo "CFLAGS        = $(CFLAGS)"
	@echo "LDFLAGS       = $(LDFLAGS)"
	@echo "TRE_CFLAGS    = $(TRE_CFLAGS)"
	@echo "TRE_LIBS      = $(TRE_LIBS)"
	@echo "LIBXML_CFLAGS = $(LIBXML_CFLAGS)"
	@echo "LIBXML_LIBS   = $(LIBXML_LIBS)"
	@echo "DEPS          = $(DEPS)"
	@echo "DEP_DIR       = $(DEP_DIR)" 
	@echo "EXE_DIR       = $(EXE_DIR)"
	@echo "OBJ_DIR       = $(OBJ_DIR)"
	@echo "LIB_DIR       = $(LIB_DIR)"
	@echo "MAKEFILE_LIST = $(MAKEFILE_LIST)"
	
-include $(DEPS)

