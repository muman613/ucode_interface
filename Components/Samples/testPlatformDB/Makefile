#	Get the current makefile to MAKEFILE
where-am-i = $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
MAKEFILE := $(call where-am-i)

ARCH?=$(shell arch)
TARGET_TYPE=exe
TARGET_EXE=testPlatformDB
#PLATDB_CONFIG?="/opt/sigma/platformdb/bin/platformdb-config"

CPP_SOURCES=main.cpp

ifdef DEBUG
PLATDB_LIBS=../../libs/Linux/$(ARCH)/libplatformdb2_d.a
else
PLATDB_LIBS=../../libs/Linux/$(ARCH)/libplatformdb2.a
endif


LIBXML_CFLAGS=$(shell pkg-config libxml-2.0 --cflags)
LIBXML_LIBS=$(shell pkg-config libxml-2.0 --libs)
PLATDB_CFLAGS=-I../../platformDB2/
CFLAGS=$(WX_CFLAGS) $(PLATDB_CFLAGS) $(LIBXML_CFLAGS) -std=c++11
LIBS=$(PLATDB_LIBS) $(WX_LIBS) $(LIBXML_LIBS)

include ../../../Build/buildsys.mk

info:
	@echo "PLATDB_CFLAGS = $(PLATDB_CFLAGS)"
	@echo "PLATDB_LIBS   = $(PLATDB_LIBS)"
	@echo "CFLAGS        = $(CFLAGS)"
	@echo "LDFLAGS       = $(LDFLAGS)"
	@echo "LIBXML_CFLAGS = $(LIBXML_CFLAGS)"
	@echo "LIBXML_LIBS   = $(LIBXML_LIBS)"
	@echo "WX_CFLAGS     = $(WX_CFLAGS)"
	@echo "WX_LIBS       = $(WX_LIBS)"
	@echo "DEPS          = $(DEPS)"
	@echo "DEP_DIR       = $(DEP_DIR)" 
	@echo "EXE_DIR       = $(EXE_DIR)"
	@echo "OBJ_DIR       = $(OBJ_DIR)"
	@echo "LIB_DIR       = $(LIB_DIR)"
	
-include $(DEPS)

