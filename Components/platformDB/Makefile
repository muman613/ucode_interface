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
LIBNAME=libplatformdb_d
else
LIBNAME=libplatformdb
endif

CPP_SOURCES=	PlatformBlock.cpp 		\
				PlatformChip.cpp  		\
				PlatformDatabase.cpp  	\
				PlatformEngine.cpp  	\
				xml_utils.cpp

LIBXML2_CFLAGS=$(shell xml2-config --cflags)
LIBXML2_LDFLAGS=$(shell xml2-config --libs)

CFLAGS=$(LIBXML2_CFLAGS) -std=c++11
LDFLAGS=$(LIBXML2_LDFLAGS)

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
