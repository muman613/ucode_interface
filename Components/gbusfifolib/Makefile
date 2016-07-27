################################################################################
#	Makefile
################################################################################

#	Get the current makefile to MAKEFILE
where-am-i = $(CURDIR)/$(word $(words $(MAKEFILE_LIST)),$(MAKEFILE_LIST))
MAKEFILE := $(call where-am-i)

TARGET_TYPE=statlib
ARCH=x86


ifdef DEBUG
LIBNAME=libgbusfifo_d
else
LIBNAME=libgbusfifo
endif

CPP_SOURCES= 	gbus_fifo.cpp 			\
			 	gbus_fifo_eraser.cpp 	\
			 	gbus_packet_fifo.cpp 	\
			 	gbus_packet_fifo_eraser.cpp

INCLUDES=-I .. -I ../..

CFLAGS=$(INCLUDES) -std=c++11
LDFLAGS=

LIB_DIR=../libs/Linux/$(ARCH)


include ../../Build/buildsys.mk

-include $(DEPS)
