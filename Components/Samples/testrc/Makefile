#	Get the current makefile to MAKEFILE
where-am-i = $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
MAKEFILE := $(call where-am-i)

ARCH?=$(shell arch)
TARGET_TYPE=exe
TARGET_EXE=testrc

CPP_SOURCES=main.cpp

ifdef DEBUG
RCLIENT_LIB=../../libs/Linux/$(ARCH)/libremote_d.a -lpthread
CPP_SOURCES+=dbgimplementation.cpp
else
RCLIENT_LIB=../../libs/Linux/$(ARCH)/libremote.a
endif

RCLIENT_CFLAGS=-I../../remote_client

INCLUDES=-I ../../..

CFLAGS=$(RCLIENT_CFLAGS) $(INCLUDES) -std=c++11
LIBS=$(RCLIENT_LIB)

include ../../../Build/buildsys.mk

info:
	@echo "CFLAGS        = $(CFLAGS)"
	@echo "LDFLAGS       = $(LDFLAGS)"
	@echo "DEPS          = $(DEPS)"
	@echo "DEP_DIR       = $(DEP_DIR)" 
	@echo "EXE_DIR       = $(EXE_DIR)"
	@echo "OBJ_DIR       = $(OBJ_DIR)"
	@echo "LIB_DIR       = $(LIB_DIR)"
	
-include $(DEPS)

