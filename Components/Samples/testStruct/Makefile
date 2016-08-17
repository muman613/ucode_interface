#	Get the current makefile to MAKEFILE
where-am-i = $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
MAKEFILE := $(call where-am-i)

ARCH?=$(shell arch)
TARGET_TYPE=exe
TARGET_EXE=testStruct

CPP_SOURCES=main.cpp

ifdef DEBUG
STRUCT_LIB=../../libs/Linux/$(ARCH)/libstructcontrol_d.a
else
STRUCT_LIB=../../libs/Linux/$(ARCH)/libstructcontrol.a
endif

LIBTRE_CFLAGS=-I../../include
LIBTRE_LIB=../../libs/Linux/$(ARCH)/libtre.a

STRUCT_CFLAGS=-I../../structure_control
CFLAGS=$(LIBTRE_CFLAGS) $(STRUCT_CFLAGS) -std=c++11
LIBS=$(STRUCT_LIB) $(LIBTRE_LIB)

include ../../../Build/buildsys.mk

info:
	@echo "STRUCT_CFLAGS = $(STRUCT_CFLAGS)"
	@echo "STRUCT_LIB    = $(STRUCT_LIB)"
	@echo "LIBTRE_CFLAGS = $(LIBTRE_CFLAGS)"
	@echo "LIBTRE_LIB    = $(LIBTRE_LIB)"
	@echo "CFLAGS        = $(CFLAGS)"
	@echo "LDFLAGS       = $(LDFLAGS)"
	@echo "DEPS          = $(DEPS)"
	@echo "DEP_DIR       = $(DEP_DIR)" 
	@echo "EXE_DIR       = $(EXE_DIR)"
	@echo "OBJ_DIR       = $(OBJ_DIR)"
	@echo "LIB_DIR       = $(LIB_DIR)"
	
-include $(DEPS)

