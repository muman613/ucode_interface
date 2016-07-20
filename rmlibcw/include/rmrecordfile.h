/*****************************************
 Copyright 2001-2010
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmrecordfile.h
  @brief

  Implementes a file handle with a lock file that signals the record status.

  @author Sebastian Frias Feltrer
  @date   2010-01-21
  @ingroup libcapi
*/

#ifndef __RMRECORDFILE_H__
#define __RMRECORDFILE_H__

#include "rmlibcw.h"

RM_EXTERN_C_BLOCKSTART

/** @addtogroup libcapi
 *  @{
 */

/**
   For custom files, open operation.

   Note that the input file will be opened once but the lock file will be opened
   and closed repeatedly (each time the lock needs to be tested).

   Should work exactly as RMOpenFile(...)
*/
typedef RMfile (*RMOpenFileCallback)(const RMnonAscii *pFilename, RMfileOpenMode Mode);

/**
   Opens a 'record' file with the rights specified in the mode.

   - If the file is opened for writing, a lock file is also created in the same path;
   the lock is updated each time there's a write to the file; The lock is removed when
   the file is closed.

   - If the file is opened for reading, both, the file and the associated lock file
   will be opened; If reading reaches the end of the file, RM_PENDING will be returned
   instead of RM_ERRORENDOFFILE, and that until the lock is marked as closed (either
   by removing it, or due to a timeout).

   A timeout will only be considered after the first update to the lock (ie: after the
   first write to the record file).

   @param pFilename : name of the file to open.
   @param Mode : rights applied to the file. Valid modes are:
		 RM_FILE_OPEN_READ (read if exists. Fails otherwise)
		 RM_FILE_OPEN_WRITE (creates if not exists. Overwrite otherwise)
   @param OpenFileCallback : if NULL regular RMOpenFile will be used, else, the
			     callback will be called.
   @param TimeOut_ms : if 0, don't timeout on the lock, else timeout after the
		       given amount of time has elapsed since the last update
		       to the lock.

   @return handle to the file opened, (RMfile)NULL on error.
*/
RM_LIBRARY_IMPORT_EXPORT RMfile RMRecordFileOpen(const RMnonAscii *pFilename, RMfileOpenMode Mode, RMOpenFileCallback OpenFileCallback, RMuint32 TimeOut_ms);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMRECORDFILE_H__
