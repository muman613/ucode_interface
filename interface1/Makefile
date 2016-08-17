################################################################################
#
#
################################################################################

TARGET_EXE=interface1
TARGET_TYPE=exe
ARCH=x86

CPP_SOURCES=  	dbgimplementation.cpp						\
				mmimplementation.cpp						\
				ucode_load_microcode.cpp					\
				utils.cpp									\
				video_interface.cpp							\
				test_interface.cpp							\
				misc.cpp sock.cpp							\
				gbus.cpp llad.cpp	\
				gbus_fifo.cpp								\
				gbus_fifo_eraser.cpp						\
				gbus_packet_fifo.cpp						\
				gbus_packet_fifo_eraser.cpp					\
				curses-mgr.cpp								\


#DBG_FLAGS=-g3 -D_DEBUG
RMCFLAGS=-DRMCHIP_ID=RMCHIP_ID_SMP8758 -DRMCHIP_REVISION=1 -DRMFEATURE_VIDEO_INTERFACE_VERSION=2
#RMCFLAGS=-DRMCHIP_ID=RMCHIP_ID_SMP8758 -DRMCHIP_REVISION=1 -DRMFEATURE_VIDEO_INTERFACE_VERSION=2
INCLUDE_FLAGS=-I . -I .. -I ../rmlibcw -I ../llad -I ../llad/network -I ../gbuslib

DEFINES=$(RMCFLAGS) -include options.h -D_FILE_OFFSET_BITS=64
#DEFINES=$(RMCFLAGS) -include options.h -D_FILE_OFFSET_BITS=64 -DGBUS_LOGGER=1
#DEFINES=$(RMCFLAGS) -DENABLE_THREADS=1 
#DEFINES=$(RMCFLAGS) -DENABLE_THREADS=1 -DENABLE_CURSES=1 -DENABLE_ENV_VARS=1 -DENABLE_PROFILING=1

ifdef UCODE_DEBUG
DEFINES+=-DUCODE_DEBUG=1
endif

CFLAGS=$(DEFINES) $(DBG_FLAGS) $(INCLUDE_FLAGS) -Wall
LDFLAGS=-pthread -lpanelw -lncursesw

include ../Build/buildsys.mk

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

