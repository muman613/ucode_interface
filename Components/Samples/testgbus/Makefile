#	Get the current makefile to MAKEFILE
where-am-i = $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
MAKEFILE := $(call where-am-i)

#ARCH?=$(shell arch)
ARCH=x86
TARGET_TYPE=exe
TARGET_EXE=testgbus

CPP_SOURCES=main.cpp

ifdef DEBUG
RCLIENT_LIB=../../libs/Linux/$(ARCH)/libremote_d.a -lpthread
GBUSFIFO_LIB=../../libs/Linux/$(ARCH)/libgbusfifo_d.a 
CPP_SOURCES+=../common/dbgimplementation.cpp
else
RCLIENT_LIB=../../libs/Linux/$(ARCH)/libremote.a -lpthread
GBUSFIFO_LIB=../../libs/Linux/$(ARCH)/libgbusfifo.a
endif

GBUSFIFO_CFLAGS=-I../../gbusfifolib
RCLIENT_CFLAGS=-I../../remote_client

INCLUDES=-I ../../.. -I ../..

CFLAGS=$(GBUSFIFO_CFLAGS) $(RCLIENT_CFLAGS) $(INCLUDES) -std=c++11
LIBS=$(GBUSFIFO_LIB) $(RCLIENT_LIB)

include ../../../Build/buildsys.mk

info:
	@echo "CFLAGS        = $(CFLAGS)"
	@echo "LDFLAGS       = $(LDFLAGS)"
	@echo "CPP_SOURCES_TRIM = $(CPP_SOURCES_TRIM)"
	@echo "DEPS          = $(DEPS)"
	@echo "DEP_DIR       = $(DEP_DIR)" 
	@echo "EXE_DIR       = $(EXE_DIR)"
	@echo "OBJ_DIR       = $(OBJ_DIR)"
	@echo "LIB_DIR       = $(LIB_DIR)"
	
-include $(DEPS)

