#	Get the current makefile to MAKEFILE
where-am-i = $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
MAKEFILE := $(call where-am-i)

TARGET_TYPE=statlib
ARCH?=$(shell arch)


ifdef DEBUG
LIBNAME=libsymbolmgr_d
else
LIBNAME=libsymbolmgr
endif

CPP_SOURCES=	symbolmgr.cpp

LIBXML2_CFLAGS=$(shell xml2-config --cflags)
LIBXML2_LDFLAGS=$(shell xml2-config --libs)

CFLAGS=$(LIBXML2_CFLAGS)
LDFLAGS=$(LIBXML2_LDFLAGS)

LIB_DIR=../libs/Linux/$(ARCH)


include ../../Build/buildsys.mk

-include $(DEPS)
