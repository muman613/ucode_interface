#	Get the current makefile to MAKEFILE
where-am-i = $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
MAKEFILE := $(call where-am-i)

TARGET_TYPE?=statlib
ARCH?=$(shell arch)

ifdef DEBUG
LIBNAME=libfileresolver_d
else
LIBNAME=libfileresolver
endif

CPP_SOURCES=	fileresolver.cpp

CFLAGS=-std=c++11
#LDFLAGS=

LIB_DIR=../libs/Linux/$(ARCH)


include ../../Build/buildsys.mk

info:
	@echo "ARCH        = $(ARCH)" 
	@echo "CFLAGS      = $(CFLAGS)"
	@echo "LDFLAGS     = $(LDFLAGS)"
	@echo "OBJ_DIR     = $(OBJ_DIR)"
	@echo "DEP_DIR     = $(DEP_DIR)"
	@echo "LIB_DIR     = $(LIB_DIR)"
	@echo "TARGET      = $(TARGET)"
	@echo "TARGET_TYPE = $(TARGET_TYPE)"
	
-include $(DEPS)
