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

CPP_SOURCES=main.cpp utils.cpp optionparser.cpp

COMPONENT_DIR=../Components/libs/Linux/$(ARCH)

ifdef SHARED
TARGET_EXE=interface4_shared

ifdef DEBUG
PLATLIB_LIBS=-L$(COMPONENT_DIR) -lsmpplatform_d
OPTS_LIBS=$(COMPONENT_DIR)/libtargetOptions_d.a


CPP_SOURCES+=dbgimplementation.cpp
else
PLATLIB_LIBS=-L$(COMPONENT_DIR) -lsmpplatform
OPTS_LIBS=$(COMPONENT_DIR)/libtargetOptions.a
endif

PLATLIB_CFLAGS=-I../Components/smpPlatformLib/
LIBXML_CFLAGS=$(shell pkg-config libxml-2.0 --cflags)
LIBXML_LIBS=$(shell pkg-config libxml-2.0 --libs)
INCLUDES=-I.. -I../Components/include -I../Components $(PLATLIB_CFLAGS) 
CFLAGS=$(INCLUDES) $(LIBXML_CFLAGS) $(PLATLIB_CFLAGS) -std=c++11
LIBS=$(PLATLIB_LIBS) $(LIBXML_LIBS) $(OPTS_LIBS) -lpthread

else	# SHARED
TARGET_EXE=interface4

ifdef DEBUG
PLATLIB_LIBS=$(COMPONENT_DIR)/libsmpplatform_d.a
PLATDB_LIBS=$(COMPONENT_DIR)/libplatformdb2_d.a
RCLIENT_LIBS=$(COMPONENT_DIR)/libremote_d.a
GBUSFIFO_LIBS=$(COMPONENT_DIR)/libgbusfifo_d.a 
SYMMGR_LIBS=$(COMPONENT_DIR)/libsymbolmgr_d.a -lpthread
STRUCT_LIBS=$(COMPONENT_DIR)/libstructcontrol_d.a
RESOLV_LIBS=$(COMPONENT_DIR)/libfileresolver_d.a
OPTS_LIBS=$(COMPONENT_DIR)/libtargetOptions_d.a

CPP_SOURCES+=dbgimplementation.cpp
else
PLATLIB_LIBS=$(COMPONENT_DIR)/libsmpplatform.a
PLATDB_LIBS=$(COMPONENT_DIR)/libplatformdb2.a
RCLIENT_LIBS=$(COMPONENT_DIR)/libremote.a
GBUSFIFO_LIBS=$(COMPONENT_DIR)/libgbusfifo.a
SYMMGR_LIBS=$(COMPONENT_DIR)/libsymbolmgr.a
STRUCT_LIBS=$(COMPONENT_DIR)/libstructcontrol.a
RESOLV_LIBS=$(COMPONENT_DIR)/libfileresolver.a
OPTS_LIBS=$(COMPONENT_DIR)/libtargetOptions.a
endif

TRE_CFLAGS=-I../../include
TRE_LIBS=../../libs/Linux/$(ARCH)/libtre.a

#PLATDB_CFLAGS=-I../../platformDB2/
#RCLIENT_CFLAGS=-I../../remote_client
PLATLIB_CFLAGS=-I../Components/smpPlatformLib/
GBUSFIFO_CFLAGS=-I../../gbusfifolib/
LIBXML_CFLAGS=$(shell pkg-config libxml-2.0 --cflags)
LIBXML_LIBS=$(shell pkg-config libxml-2.0 --libs)

#DEFINES=-DGBUS_LOGGER=1
#INCLUDES=-I../.. -I../../.. -I ../../include $(PLATLIB_CFLAGS) $(GBUSFIFO_CFLAGS)
INCLUDES=-I.. -I../Components/include -I../Components $(PLATLIB_CFLAGS) 

CFLAGS=$(DEFINES) $(LIBXML_CFLAGS) -std=c++11
LIBS=$(PLATLIB_LIBS) $(OPTS_LIBS) $(PLATDB_LIBS) $(RCLIENT_LIBS) $(SYMMGR_LIBS) \
     $(STRUCT_LIBS) $(RESOLV_LIBS) $(LIBXML_LIBS) $(GBUSFIFO_LIBS) -lpthread

endif	# SHARED

include ../Build/buildsys.mk

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
	@echo "INCLUDES      = $(INCLUDES)"
	
-include $(DEPS)

