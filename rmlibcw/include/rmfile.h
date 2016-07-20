/*****************************************
 Copyright (c) 2001-2003
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   rmfile.h
  @ingroup libcapi
  @brief  Implements the standard libc I/O API

  @author Mathieu Lacage
  @date   2001-09-07
*/

#ifndef __RMFILE_H__
#define __RMFILE_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup libcapi
 *  @{
 */

/** type used to manipulate TEXT file */
typedef struct _RMfile *RMfile;



#define RMFILE_MAX_ENTRY_NAME_LENGTH	511

typedef struct _RMdirectory *RMdirectory;

typedef struct {
	RMnonAscii name[RMFILE_MAX_ENTRY_NAME_LENGTH];
} RMdirectoryEntry;

typedef enum {
	// read if exists. Fails otherwise
	RM_FILE_OPEN_READ,
	// creates if not exists. Overwrite otherwise
	RM_FILE_OPEN_WRITE,
	// read, write file if exists
	RM_FILE_OPEN_READ_WRITE,
	// read, write file ( also create if does not exist)
	RM_FILE_OPEN_READ_WRITE_CREATE,

} RMfileOpenMode;

typedef enum {
	// seek from start of file.
	RM_FILE_SEEK_START,
	// seek from current position in the file.
	RM_FILE_SEEK_CURRENT,
	// seek from end of file.
	RM_FILE_SEEK_END,
} RMfileSeekPos;

/**
   For custom files, read operation : Your function should transfer up to size
   bytes into the buffer, and return the number of bytes read, or zero to
   indicate end-of-file. You can return a value of -1 to indicate an error.
*/
typedef RMint32 (*RMReadOp) (void *cookie, RMuint8 *buffer, RMuint32 size);

/**
   For custom files, write operation : Your function should transfer up to size
   bytes from the buffer, and return the number of bytes written. You can
   return a value of -1 to indicate an error.
*/
typedef RMint32 (*RMWriteOp) (void *cookie, const RMuint8 *buffer, RMuint32 size);

/**
   For custom files, non-blocking read operation : Your function should transfer
   up to size bytes into the buffer, and return the number of bytes read. If your
   function has been working for more than timeout ms but did not read anything yet,
   it must return -RM_PENDING, otherwise it must stop reading and return the size
   read up to this point.
   Returning 0 indicates the end-of-file.

   For consistency, the non blocking read operation used with a timeout of 0
   should have the same behaviour as the blocking read. (In fact it is strongly
   advised for your blocking read to be only a shortcut to the non-blocking
   implementation).

   You can return a value of -1 to indicate an error.
*/
typedef RMint32 (*RMNonBlockReadOp) (void *cookie, RMuint8 *buffer, RMuint32 size, RMuint32 timeout);

/**
   For custom files, seek operation : After doing the seek operation, your
   function should store the resulting file position relative to the beginning
   of the file in position. Your function should return a value of 0 on success
   and -1 to indicate an error.
*/
typedef RMint32 (*RMSeekOp) (void *cookie, RMint64 *position, RMfileSeekPos whence);


/**
   For custom files, close operation : Your function should return -1 to
   indicate an error, and 0 otherwise.
*/
typedef RMint32 (*RMCloseOp) (void *cookie);


/**
   For custom files, file operations struct
*/
typedef struct {
	RMReadOp read;
	RMWriteOp write;
	RMSeekOp seek;
	RMCloseOp close;
	RMNonBlockReadOp read_nonblock;
} RMFileOps;

/**
   For custom directories, read operation : Your function should read one directory entry.
   Should return RM_OK on success, RM_ERRORNODIRECTORYENTRY if it cannot return a new entry,
   RM_ERROR on error.
   @remark the field entry should be valid till the user either call RMReadDirectory
	   or RMCloseDirectory. The user don't free this field himself.
*/
typedef RMstatus (*RMReadDirectoryOp) ( void*cookie, RMdirectoryEntry *const entry );

/**
   For custom directories, close operation.
   Should return RM_OK on success, RM_ERROR on error.
*/
typedef RMstatus (*RMCloseDirectoryOp) ( void*cookie );

/**
   For custom directories, tell operation.
   Should return RM_OK on success, RM_ERROR on error.
*/
typedef RMstatus (*RMTellDirectoryOp) ( void*cookie, RMint32* pPos );

/**
   For custom directories, seek operation.
   Should return RM_OK on success, RM_ERROR on error.
*/
typedef RMstatus (*RMSeekDirectoryOp) ( void*cookie, RMint32 position );

/**
   For custom directories, rewind operation.
   Should return RM_OK on success, RM_ERROR on error.
*/
typedef RMstatus (*RMRewindDirectoryOp) ( void*cookie );

/**
   For custom directories, directory operations struct
*/
typedef struct {
	RMReadDirectoryOp read;
	RMCloseDirectoryOp close;
	RMTellDirectoryOp tell;
	RMSeekDirectoryOp seek;
	RMRewindDirectoryOp rewind;
} RMDirectoryOps;

/**
   For directory scan.
   Should return TRUE for files names that pass the filter, else FALSE.
*/
typedef RMbool (*RMDirectoryFilter) (RMdirectoryEntry *pEntry, void* pContext);

/**
   Returns the size of the specified filename (doesn't work with custom files).

   The file should not already be open when calling RMSizeOfFile.

   This size is the number of bytes needed to store the file [whatever the file
   content is (unicode,...), and if the operating system needs some file
   termination character it includes these characters]

   @param filename
   @param pSize the size
   @return: does not return RM_OK on failure (non existent file...)
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMSizeOfFile(const RMnonAscii *filename,RMint64 *pSize);


/**
   Returns the size of the given file handle (works with customs files).

   The file should already be open when calling RMSizeOfFile.

   This size is the number of bytes needed to store the file [whatever the file
   content is (unicode,...), and if the operating system needs some file
   termination character it includes these characters]

   @param f
   @param pSize the size
   @return: does not return RM_OK on failure (non existent file...)
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMSizeOfOpenFile(RMfile f, RMint64 *pSize);


/**
   Opens a file with the rights specified in the mode.

   The obtained handle is a blocking handle, as a result RMReadFile_WithTimeout
   won't be able to respect its target time using file openned this way.

   @param filename : name of the file to open.
   @param mode : rights applied to the file. Valid modes are:
		 RM_FILE_OPEN_READ (read if exists. Fails otherwise)
		 RM_FILE_OPEN_WRITE (creates if not exists. Overwrite otherwise)
		 RM_FILE_OPEN_READ_WRITE (read, write file if exists)
   @return handle to the file opened, (RMfile)NULL on error.
*/
RM_LIBRARY_IMPORT_EXPORT RMfile RMOpenFile(const RMnonAscii *filename, RMfileOpenMode mode);


/**
   Opens a file with the rights specified in the mode, and use the given cookie
   and fileops to communicate with the underlying media. A read on this RMfile
   will call the read callback given in the RMFileOps structure. A write will
   call the write callback, seek will call the seek callback and close will
   call the close callback.  Each time a callback is called, the cookie will be
   passed to it, so it can be used to store private data.

   @param cookie : cookie to pass to file ops functions.
   @param mode : rights applied to the file. Valid modes are:
		 RM_FILE_OPEN_READ (read if exists. Fails otherwise)
		 RM_FILE_OPEN_WRITE (creates if not exists. Overwrite otherwise)
		 RM_FILE_OPEN_READ_WRITE (read, write file if exists)
   @param ops : pointer to the fileops for this custom stream.
   @return handle to the file opened, (RMfile)NULL on error.
*/
RM_LIBRARY_IMPORT_EXPORT RMfile RMOpenFileCookie(void *cookie, RMfileOpenMode mode, RMFileOps *ops);



/**
   Returns the cookie for a given fileHandle. If there's no cookie it returns
   RM_ERROR.

   @param FileHandle: a file handle
   @param pCookie: where to store the cookie
   @return RM_OK if there's a cookie, or RM_ERROR if there's no cookie
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMGetFileCookie(RMfile FileHandle, void **ppCookie);

/**
   Creates a temporary file.

   @param void
   @return handle to the file or NULL if the call failed.
*/
RM_LIBRARY_IMPORT_EXPORT RMfile RMCreateTmpFile(void);


/**
   Closes the filehandle.
   This call CANNOT fail.

   @param f filehandle to close.
   @return RM_ERRORCLOSEFILE or RM_ERRORFILELOCKED
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMCloseFile(const RMfile f);


/**
   Reads size bytes from filehandle f and stores them in buffer pbuffer.
   This read has no timeout, it will always return data unless there
   is an error or it reaches the end of file, and will wait indefinitely
   if that's what it takes.

   Don't expect *preadSize to always match size of course.

   @param f filehandle to read in.
   @param pbuffer buffer to store data into.
   @param size number of bytes the caller wants to read.
   @param preadSize number of bytes actually read.
   @return RM_OK if succesful, RM_ERRORENDOFFILE if end of file
	   or RM_ERRORREADFILE is unsuccessful.
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMReadFile (const RMfile f, RMuint8 *pbuffer, RMuint32 size, RMuint32 *preadSize);


/**
   Reads size bytes from filehandle f and stores them in buffer pbuffer.
   This read has no timeout, it will always return data unless there
   is an error or it reaches the end of file, and will wait indefinitely
   if that's what it takes.

   Don't expect *preadSize to always match size of course.

   @param f filehandle to read in.
   @param pbuffer buffer to store data into.
   @param size number of bytes the caller wants to read.
   @param preadSize number of bytes actually read.
   @param timeout If timeout is 0, function will behave as RMReadFile,
	if timeout is not zero, it will try to exit if the call
	took more than timeout ms and return any data that could
	be read this far. This function only promises that it will
	do its best to respect the timeout, depending on where the
	file is stored (local disk, network share, http server)
	it may not be able to keep that promise. Please refer to the
	documentation of the file handle creation routine you used for
	more information.
   @return RM_OK if succesful, RM_ERRORENDOFFILE if end of file
	   RM_ERRORREADFILE is unsuccessful.
	   Also, returns RM_PENDING if timeout was reached but
	   nothing was read, although no error occured. Meaning
	   that you should try again a bit later.
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMReadFile_WithTimeout (const RMfile f, RMuint8 *pbuffer, RMuint32 size, RMuint32 *preadSize, RMuint32 timeout);

/**
   Writes size bytes to filehandle f.

   @param f filehandle to write in.
   @param pbuffer buffer to read data from.
   @param size number of bytes to write.
   @param pwrittenSize number of bytes written.
   @return RM_OK if succesful, RM_ERRORENDOFFILE if end of file
	   or RM_ERRORWRITEFILE is unsuccessful.
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMWriteFile (const RMfile f, const RMuint8 *pbuffer, RMuint32 size, RMuint32 *const pwrittenSize);


/**
   Copy the entire src file in the dest file. The current file
   position is not modified.

   @param dest
   @param src
   @return RM_OK or RM_ERROR
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMCopyFile(const RMfile dest, const RMfile src);


/**
   Prints a string in a file.

   @param f
   @param fmt
   @param  ...
   @return RM_OK if successful or RM_ERRORWRITEFILE is unsuccesful.
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMPrintFile(RMfile f, const RMascii *fmt, ...);


/**
   Move the position of the file handle f to offset starting at position.

   @param f file handle.
   @param offset offset to move to.
   @param position starting position.
 */
RM_LIBRARY_IMPORT_EXPORT RMstatus RMSeekFile (const RMfile f, RMint64 offset, RMfileSeekPos position);


/**
   tests end of file.

   @param f file handle to test.
   @return TRUE is end of file, FALSE otherwise.
 */
RM_LIBRARY_IMPORT_EXPORT RMbool RMEndOfFile (const RMfile f);


/**
   flushes the file to the HD.

   @param f file to flush.
 */
RM_LIBRARY_IMPORT_EXPORT RMstatus RMFlushFile (RMfile f);


/**
   reads one line in the file. Read at most maxsize bytes.

   @param f
   @param line
   @param maxsize
   @return RM_OK upon success.
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMReadLineFile(RMfile f, RMascii *line, RMuint32 maxsize);

/**
   Lock the file to the current thread. This thread and only this one
   hase full access to the file. However, it cannot close it until it
   unlocks the file. To allow another thread to access the file, the
   thread must call unlock.

   @param f
   @return
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMLockFile(RMfile f);


/**
   Unlock the file to allow other threads to access it.
   @param f
   @return
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMUnLockFile(RMfile f);


/**
   Sets the current working directory.

   @param directory to change to.

   @returns RM_OK on success.
	    RM_ERROROPENFILE in case of error.
 */
RM_LIBRARY_IMPORT_EXPORT RMstatus RMChangeCurrentDirectory(const RMnonAscii *const directory);


/**
   Open current directory.

   @param dir a pointer to the structure representing a directory.
   @returns RM_OK on success.
	    RM_ERROROPENFILE in case of error.
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMOpenCurrentDirectory (RMdirectory *const dir);

/**
   Open directory to browse its entries.

   @param directory the name of the directory to open.
   @param dir a pointer to the returned directory.
   @return RM_OK on success.
	   RM_ERROROPENFILE in case of error.
 */
RM_LIBRARY_IMPORT_EXPORT RMstatus RMOpenDirectory (const RMnonAscii *const directory, RMdirectory *const dir);

/**
   Open a custom directory to browse its entries and use the given cookie
   and directoryops to communicate with the underlying media. A read (or close) on
   this RMdirectory will call the read (or close) callback given in the RMDirectoryOps
   structure. Each time a callback is called, the cookie will be
   passed to it, so it can be used to store private data.
   @param dir a pointer to the returned directory.
   @param cookie : cookie to pass to directory ops functions.
   @param ops : pointer to the directory ops for this custom directory.
   @return RM_OK.
 */
RM_LIBRARY_IMPORT_EXPORT RMstatus RMOpenDirectoryCookie (RMdirectory *const dir, void* cookie, RMDirectoryOps *ops);

/**
   Close a directory opened with RMOpenDirectory

   @return RM_OK on success.
	   RM_ERRORCLOSEFILE in case of error.
 */
RM_LIBRARY_IMPORT_EXPORT RMstatus RMCloseDirectory (RMdirectory directory);

/**
   Read one directory entry.

   @param directory the directory to read entries from.
   @param entry pointer where to store the next entry.
   @return RM_OK on success.
	   RM_ERRORNODIRECTORYENTRY if it cannot return a new entry.

   @remark the fields in entry are valid till the user either call RMReadDirectory
	   or RMCloseDirectory. The user should _not_ free these fields himself.
 */
RM_LIBRARY_IMPORT_EXPORT RMstatus RMReadDirectory (RMdirectory directory, RMdirectoryEntry *const entry);

/**
   Tell directory current position.

   @param directory the directory to tell the position from.
   @param pPos position into the directory (to use with RMSeekDirectory).
   @return RM_OK on success.
	   RM_ERROR on error
 */
RM_LIBRARY_IMPORT_EXPORT RMstatus RMTellDirectory (RMdirectory directory, RMint32* pPos);

/**
   Seek in a directory.

   @param directory the directory where to seek.
   @param position position where to seek in the directory (retrieved by RMTellDirectory).
   @return RM_OK on success.
	   RM_ERROR on error
 */
RM_LIBRARY_IMPORT_EXPORT RMstatus RMSeekDirectory (RMdirectory directory, RMint32 position);

/**
   Rewind a directory to its beginning.

   @param directory the directory to rewind
   @return RM_OK on success.
	   RM_ERROR on error
 */
RM_LIBRARY_IMPORT_EXPORT RMstatus RMRewindDirectory (RMdirectory directory);

/**
   Count the entries from a directory.

   @param directory the directory to count the entries from.
   @param pCount number of counted entries. Cannot be NULL.
   @param filter filter callback (returns TRUE for valid entries). Can be NULL to skip filtering.
   @param pFilterContext context to be passed to the callback. Can be NULL.
   @return RM_OK on success.
	   RM_ERROR on error
 */
RM_LIBRARY_IMPORT_EXPORT RMstatus RMCountDirectoryEntries (RMdirectory directory, RMuint32 *pCount, RMDirectoryFilter filter, void* pFilterContext);

/**
   Scan a directory with filter.

   @param directory the directory to scan. The directory will be completely scanned.
   @param pEntryTable already allocated table of RMdirectoryEntry pointers. The size of the table must not exceed max_entries elements. Cannot be NULL.
   @param max_entries max entries to store in the table.
   @param pCount number of entries actually stored in the table. Cannot be NULL.
   @param filter filter callback (returns TRUE for valid entries). Can be NULL to skip filtering.
   @param pFilterContext context to be passed to the callback. Can be NULL.
   @return RM_OK on success.
	   RM_ERROR on error
 */
RM_LIBRARY_IMPORT_EXPORT RMstatus RMScanDirectory (RMdirectory directory, RMdirectoryEntry* pEntryTable, RMuint32 max_entries, RMuint32 *pCount, RMDirectoryFilter filter, void* pFilterContext);

/**
   Rename a file from oldpath to newpath.

   @param oldpath
   @param newpath
   @return RM_OK on success
	   RM_ERROR on failure
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMFileRename(RMnonAscii *oldpath,RMnonAscii *newpath);

/**
   Create a directory with write, read and execute access

   @param pathname
   @return RM_OK on success
	   RM_ERROR on failure
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMFileMkdir(RMnonAscii *pathname);

/**
   deletes a name from the filesystem.

   @param pathname
   @return RM_OK on success
	   RM_ERROR on failure
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMFileUnlink(RMnonAscii *pathname);

/**
   Get the current poision in the file (offset from the beginning)�

   @param f : file handle
   @param position : current position
   @return RM_OK on success
	   RM_ERROR on failure
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMGetCurrentPositionOfFile (const RMfile f, RMint64 *position);

/**

   Check if the passed file is a cookie and the operation passed correspond to
   those inside the cookie.

   @param f The file handle.
   @param ops The operation that should be in the file cookie.
   @return TRUE if it correspond, FALSE otherwise.
 */
RM_LIBRARY_IMPORT_EXPORT RMbool RMCheckFileOps(const RMfile f, const RMFileOps *ops);

/**

   Open an unseekable file from the file given in parameters.

   @param f The file handle
   @return A file handle corresponding to the file handle gives as parameter but where
		the seek command will always failed or NULL if an error occur.
 */
RM_LIBRARY_IMPORT_EXPORT RMfile RMMakeUnseekableFile(const RMfile f);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMFILE_H__
