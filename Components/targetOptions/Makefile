################################################################################
#	Nakefile
################################################################################

#	Get the current makefile to MAKEFILE
where-am-i = $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
MAKEFILE := $(call where-am-i)

TARGET_TYPE=statlib
ARCH?=$(shell arch)


ifdef DEBUG
LIBNAME=libtargetOptions_d
else
LIBNAME=libtargetOptions
endif

CPP_SOURCES = 	targetOptionsManager.cpp

LIBXML2_CFLAGS=$(shell xml2-config --cflags)
#LIBXML2_LDFLAGS=$(shell xml2-config --libs)

INCLUDES=-I../include
CFLAGS=$(LIBXML2_CFLAGS) -std=c++11
#LDFLAGS=$(LIBXML2_LDFLAGS)

LIB_DIR=../libs/Linux/$(ARCH)


include ../../Build/buildsys.mk

-include $(DEPS)
