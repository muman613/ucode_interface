################################################################################
#	Nakefile
################################################################################

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
LIBNAME=libsmpplatform_d
else
LIBNAME=libsmpplatform
endif

CPP_SOURCES = 	targetAllocator.cpp												\
				targetEngine.cpp												\
				targetInterfaceBase.cpp											\
				targetStandardInterface.cpp										\
				ucode_utils.cpp													\
				video_utils.cpp													\
				string_utils.cpp												\
				struct_utils.cpp

INCLUDES=-I../.. -I.. -I ../gbusfifolib
DEFINES=-DRMFEATURE_VIDEO_INTERFACE_VERSION=2
LIBXML2_CFLAGS=$(shell xml2-config --cflags)
LIBXML2_LDFLAGS=$(shell xml2-config --libs)

CFLAGS=$(DEFINES) $(LIBXML2_CFLAGS) $(INCLUDES) --std=c++11
#CFLAGS=$(DEFINES) $(INCLUDES) --std=c++11
LDFLAGS=$(LIBXML2_LDFLAGS)

LIB_DIR=../libs/Linux/$(ARCH)

ifeq ($(TARGET_TYPE), dynlib)
ifdef DEBUG
LDFLAGS+=../libs/Linux/${ARCH}/libplatformdb2_d.a								\
		 ../libs/Linux/${ARCH}/libstructcontrol_d.a								\
		 ../libs/Linux/${ARCH}/libfileresolver_d.a								\
		 ../libs/Linux/${ARCH}/libremote_d.a									\
		 ../libs/Linux/${ARCH}/libsymbolmgr_d.a									\
		 ../libs/Linux/${ARCH}/libgbusfifo_d.a
 else
LDFLAGS+=../libs/Linux/${ARCH}/libplatformdb2.a									\
		 ../libs/Linux/${ARCH}/libstructcontrol.a								\
		 ../libs/Linux/${ARCH}/libfileresolver.a								\
		 ../libs/Linux/${ARCH}/libremote.a										\
		 ../libs/Linux/${ARCH}/libsymbolmgr.a									\
		 ../libs/Linux/${ARCH}/libgbusfifo.a
endif
endif


include ../../Build/buildsys.mk

-include $(DEPS)


