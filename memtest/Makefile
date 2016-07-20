###############################################################################
#	Makefile
#
#	Tool to test read/write using gbus_read_dataXX functions.
#
###############################################################################

GCC=gcc

TARGET=memtest

C_SRC=  dbgimplementation.c mmimplementation.c									\
		memtest.c misc.c sock.c gbus.c llad.c utils.c


DBG_FLAGS=-g3 -D_DEBUG
RMCFLAGS=-DRMCHIP_ID=RMCHIP_ID_SMP8760 -DRMCHIP_REVISION=1 -DRMFEATURE_VIDEO_INTERFACE_VERSION=2
INCLUDE_FLAGS=-I . -I .. -I ../rmlibcw -I ../llad -I ../llad/network -I ../gbuslib

DEFINES=$(RMCFLAGS)

CFLAGS=-m32 $(DEFINES) $(DBG_FLAGS) $(INCLUDE_FLAGS)

C_OBJS= $(C_SRC:%.c=%.o)
OBJS=$(C_OBJS) $(CPP_OBJS)

%.o:%.c Makefile
	$(GCC) -c -o $*.o $(CFLAGS) $*.c

$(TARGET): $(OBJS)
	$(GCC) -m32 -o $(TARGET) $(OBJS) $(LDFLAGS)

clean:
	rm -rf $(TARGET) $(OBJS)

depends:
	makedepend -Y $(DEFINES) $(RMCFLAGS) $(INCLUDE_FLAGS) $(C_SRC)

# DO NOT DELETE

dbgimplementation.o: ../rmdef/rmdef.h ../rmdef/rmem86xxid.h
dbgimplementation.o: ../rmdef/rmplatform.h ../rmdef/rmarchid.h
dbgimplementation.o: ../rmdef/rmcompilerid.h ../rmdef/rmgcc.h
dbgimplementation.o: ../rmdef/rmbtypes.h ../rmdef/rmforbid.h
dbgimplementation.o: ../rmdef/rmstatus.h ../rmdef/rmstatus.inc
dbgimplementation.o: ../rmdef/rmpanic.h ../rmdef/rmmacros_c.h
dbgimplementation.o: ../rmdef/rmmacros_gcc.h ../rmdef/rmmacros_divisions.h
dbgimplementation.o: ../rmdef/rmselfcheck.h ../rmdef/rmstreamid.h
dbgimplementation.o: ../rmdef/rmdbg.h ../rmdef/rmmm.h ../rmdef/rmsync.h
dbgimplementation.o: ../rmdef/rmpacketcommandops.h ../rmdef/rmnonasciitype.h
dbgimplementation.o: ../rmcore/include/rmcore.h ../rmcore/include/rmascii.h
dbgimplementation.o: ../rmcore/include/rmcorelist.h
dbgimplementation.o: ../rmcore/include/rmcorequeue.h
dbgimplementation.o: ../rmcore/include/rmcorepool.h
dbgimplementation.o: ../rmcore/include/rmgrep.h
dbgimplementation.o: ../rmcore/include/rmstatustostring.h
dbgimplementation.o: ../rmcore/include/rmwrrd.h ../rmcore/include/rmlist.h
dbgimplementation.o: ../rmcore/include/rmqueue.h
dbgimplementation.o: ../rmcore/include/rmtimeoutqueue.h
dbgimplementation.o: ../rmcore/include/rmpool.h ../rmcore/include/rmparser.h
dbgimplementation.o: ../rmcore/include/rmfifo.h ../rmlibcw/include/rmlibcw.h
dbgimplementation.o: ../rmlibcw/include/rmnonascii.h
dbgimplementation.o: ../rmlibcw/include/rmsemaphores.h
dbgimplementation.o: ../rmlibcw/include/rmcriticalsections.h
dbgimplementation.o: ../rmlibcw/include/rmtimeoutsemaphore.h
dbgimplementation.o: ../rmlibcw/include/rmthreads.h
dbgimplementation.o: ../rmlibcw/include/rmrandom.h
dbgimplementation.o: ../rmlibcw/include/rmtime.h
dbgimplementation.o: ../rmlibcw/include/rmsprintf.h
dbgimplementation.o: ../rmlibcw/include/rmfile.h ../rmlibcw/include/rmenv.h
dbgimplementation.o: ../rmlibcw/include/rmsocket.h
dbgimplementation.o: ../rmlibcw/include/rmpacketcommandioctl.h
dbgimplementation.o: ../rmlibcw/include/rmdynamicloader.h
dbgimplementation.o: ../rmlibcw/include/rmstrcmp.h
dbgimplementation.o: ../rmlibcw/include/rmstrstr.h
dbgimplementation.o: ../rmlibcw/include/rmrecordfile.h
dbgimplementation.o: ../rmlibcw/include/rmlibcw.h
dbgimplementation.o: ../rmlibcw/include/rmfilecache.h
mmimplementation.o: ../rmdef/rmdef.h ../rmdef/rmem86xxid.h
mmimplementation.o: ../rmdef/rmplatform.h ../rmdef/rmarchid.h
mmimplementation.o: ../rmdef/rmcompilerid.h ../rmdef/rmgcc.h
mmimplementation.o: ../rmdef/rmbtypes.h ../rmdef/rmforbid.h
mmimplementation.o: ../rmdef/rmstatus.h ../rmdef/rmstatus.inc
mmimplementation.o: ../rmdef/rmpanic.h ../rmdef/rmmacros_c.h
mmimplementation.o: ../rmdef/rmmacros_gcc.h ../rmdef/rmmacros_divisions.h
mmimplementation.o: ../rmdef/rmselfcheck.h ../rmdef/rmstreamid.h
mmimplementation.o: ../rmdef/rmdbg.h ../rmdef/rmmm.h ../rmdef/rmsync.h
mmimplementation.o: ../rmdef/rmpacketcommandops.h ../rmdef/rmnonasciitype.h
memtest.o: ../llad/include/llad.h ../rmdef/rmdef.h ../rmdef/rmem86xxid.h
memtest.o: ../rmdef/rmplatform.h ../rmdef/rmarchid.h ../rmdef/rmcompilerid.h
memtest.o: ../rmdef/rmgcc.h ../rmdef/rmbtypes.h ../rmdef/rmforbid.h
memtest.o: ../rmdef/rmstatus.h ../rmdef/rmstatus.inc ../rmdef/rmpanic.h
memtest.o: ../rmdef/rmmacros_c.h ../rmdef/rmmacros_gcc.h
memtest.o: ../rmdef/rmmacros_divisions.h ../rmdef/rmselfcheck.h
memtest.o: ../rmdef/rmstreamid.h ../rmdef/rmdbg.h ../rmdef/rmmm.h
memtest.o: ../rmdef/rmsync.h ../rmdef/rmpacketcommandops.h
memtest.o: ../rmdef/rmnonasciitype.h ../rmchip/rmchip.h ../rmchip/rmchip_id.h
memtest.o: ../rmchip/rmchip_smp8760r1.h ../rmchip/rmchip_common.h
memtest.o: ../llad/include/gbus.h ../llad/include/llad.h utils.h
misc.o: ../rmlibcw/include/rmlibcw.h ../rmdef/rmdef.h ../rmdef/rmem86xxid.h
misc.o: ../rmdef/rmplatform.h ../rmdef/rmarchid.h ../rmdef/rmcompilerid.h
misc.o: ../rmdef/rmgcc.h ../rmdef/rmbtypes.h ../rmdef/rmforbid.h
misc.o: ../rmdef/rmstatus.h ../rmdef/rmstatus.inc ../rmdef/rmpanic.h
misc.o: ../rmdef/rmmacros_c.h ../rmdef/rmmacros_gcc.h
misc.o: ../rmdef/rmmacros_divisions.h ../rmdef/rmselfcheck.h
misc.o: ../rmdef/rmstreamid.h ../rmdef/rmdbg.h ../rmdef/rmmm.h
misc.o: ../rmdef/rmsync.h ../rmdef/rmpacketcommandops.h
misc.o: ../rmdef/rmnonasciitype.h ../rmlibcw/include/rmnonascii.h
misc.o: ../rmlibcw/include/rmsemaphores.h
misc.o: ../rmlibcw/include/rmcriticalsections.h
misc.o: ../rmlibcw/include/rmtimeoutsemaphore.h
misc.o: ../rmlibcw/include/rmthreads.h ../rmlibcw/include/rmrandom.h
misc.o: ../rmlibcw/include/rmtime.h ../rmlibcw/include/rmsprintf.h
misc.o: ../rmlibcw/include/rmfile.h ../rmlibcw/include/rmenv.h
misc.o: ../rmlibcw/include/rmsocket.h
misc.o: ../rmlibcw/include/rmpacketcommandioctl.h
misc.o: ../rmlibcw/include/rmdynamicloader.h ../rmlibcw/include/rmstrcmp.h
misc.o: ../rmlibcw/include/rmstrstr.h ../rmlibcw/include/rmrecordfile.h
misc.o: ../rmlibcw/include/rmlibcw.h ../rmlibcw/include/rmfilecache.h
misc.o: ../rmcore/include/rmcore.h ../rmcore/include/rmascii.h
misc.o: ../rmcore/include/rmcorelist.h ../rmcore/include/rmcorequeue.h
misc.o: ../rmcore/include/rmcorepool.h ../rmcore/include/rmgrep.h
misc.o: ../rmcore/include/rmstatustostring.h ../rmcore/include/rmwrrd.h
misc.o: ../rmcore/include/rmlist.h ../rmcore/include/rmqueue.h
misc.o: ../rmcore/include/rmtimeoutqueue.h ../rmcore/include/rmpool.h
misc.o: ../rmcore/include/rmparser.h ../rmcore/include/rmfifo.h
misc.o: ../rmdef/rmstatus.inc
sock.o: sock.h ../rmdef/rmdef.h ../rmdef/rmem86xxid.h ../rmdef/rmplatform.h
sock.o: ../rmdef/rmarchid.h ../rmdef/rmcompilerid.h ../rmdef/rmgcc.h
sock.o: ../rmdef/rmbtypes.h ../rmdef/rmforbid.h ../rmdef/rmstatus.h
sock.o: ../rmdef/rmstatus.inc ../rmdef/rmpanic.h ../rmdef/rmmacros_c.h
sock.o: ../rmdef/rmmacros_gcc.h ../rmdef/rmmacros_divisions.h
sock.o: ../rmdef/rmselfcheck.h ../rmdef/rmstreamid.h ../rmdef/rmdbg.h
sock.o: ../rmdef/rmmm.h ../rmdef/rmsync.h ../rmdef/rmpacketcommandops.h
sock.o: ../rmdef/rmnonasciitype.h
gbus.o: ../llad/include/gbus.h ../llad/include/llad.h
gbus.o: ../llad/network/include/sock.h ../rmdef/rmdef.h ../rmdef/rmem86xxid.h
gbus.o: ../rmdef/rmplatform.h ../rmdef/rmarchid.h ../rmdef/rmcompilerid.h
gbus.o: ../rmdef/rmgcc.h ../rmdef/rmbtypes.h ../rmdef/rmforbid.h
gbus.o: ../rmdef/rmstatus.h ../rmdef/rmstatus.inc ../rmdef/rmpanic.h
gbus.o: ../rmdef/rmmacros_c.h ../rmdef/rmmacros_gcc.h
gbus.o: ../rmdef/rmmacros_divisions.h ../rmdef/rmselfcheck.h
gbus.o: ../rmdef/rmstreamid.h ../rmdef/rmdbg.h ../rmdef/rmmm.h
gbus.o: ../rmdef/rmsync.h ../rmdef/rmpacketcommandops.h
gbus.o: ../rmdef/rmnonasciitype.h ../llad/network/include/llad_protocol.h
gbus.o: struct.h
llad.o: ../llad/include/llad.h ../rmdef/rmdef.h ../rmdef/rmem86xxid.h
llad.o: ../rmdef/rmplatform.h ../rmdef/rmarchid.h ../rmdef/rmcompilerid.h
llad.o: ../rmdef/rmgcc.h ../rmdef/rmbtypes.h ../rmdef/rmforbid.h
llad.o: ../rmdef/rmstatus.h ../rmdef/rmstatus.inc ../rmdef/rmpanic.h
llad.o: ../rmdef/rmmacros_c.h ../rmdef/rmmacros_gcc.h
llad.o: ../rmdef/rmmacros_divisions.h ../rmdef/rmselfcheck.h
llad.o: ../rmdef/rmstreamid.h ../rmdef/rmdbg.h ../rmdef/rmmm.h
llad.o: ../rmdef/rmsync.h ../rmdef/rmpacketcommandops.h
llad.o: ../rmdef/rmnonasciitype.h ../rmchip/rmchip.h ../rmchip/rmchip_id.h
llad.o: ../rmchip/rmchip_smp8760r1.h ../rmchip/rmchip_common.h
llad.o: ../llad/network/include/sock.h
llad.o: ../llad/network/include/llad_protocol.h struct.h
utils.o: ../llad/include/llad.h ../rmdef/rmdef.h ../rmdef/rmem86xxid.h
utils.o: ../rmdef/rmplatform.h ../rmdef/rmarchid.h ../rmdef/rmcompilerid.h
utils.o: ../rmdef/rmgcc.h ../rmdef/rmbtypes.h ../rmdef/rmforbid.h
utils.o: ../rmdef/rmstatus.h ../rmdef/rmstatus.inc ../rmdef/rmpanic.h
utils.o: ../rmdef/rmmacros_c.h ../rmdef/rmmacros_gcc.h
utils.o: ../rmdef/rmmacros_divisions.h ../rmdef/rmselfcheck.h
utils.o: ../rmdef/rmstreamid.h ../rmdef/rmdbg.h ../rmdef/rmmm.h
utils.o: ../rmdef/rmsync.h ../rmdef/rmpacketcommandops.h
utils.o: ../rmdef/rmnonasciitype.h ../rmchip/rmchip.h ../rmchip/rmchip_id.h
utils.o: ../rmchip/rmchip_smp8760r1.h ../rmchip/rmchip_common.h
utils.o: ../llad/include/gbus.h ../llad/include/llad.h utils.h
