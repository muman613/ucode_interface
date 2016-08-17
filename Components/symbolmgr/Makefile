#	Get the current makefile to MAKEFILE
where-am-i = $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
MAKEFILE := $(call where-am-i)

ifdef SHARED
TARGET_TYPE=dynlib
else
TARGET_TYPE=statlib
endif

ARCH?=$(shell arch)


ifdef DEBUG
LIBNAME=libsymbolmgr_d
else
LIBNAME=libsymbolmgr
endif

CPP_SOURCES=	symbolmgr.cpp

LIBXML2_CFLAGS=$(shell xml2-config --cflags)
LIBXML2_LDFLAGS=$(shell xml2-config --libs)

INCLUDES=-I../include
CFLAGS=$(LIBXML2_CFLAGS) -std=c++11
LDFLAGS=$(LIBXML2_LDFLAGS)

LIB_DIR=../libs/Linux/$(ARCH)


include ../../Build/buildsys.mk

-include $(DEPS)
