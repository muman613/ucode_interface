/*****************************************
 Copyright (c) 2001-2003
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   rmfilecache.h
  @brief

  Describes the API that associates a file handler with a libcurl session.

  @author Edwin Stearns, Raul Chirinos
  @date   2010-05-10
  @ingroup libcapi
*/

#ifndef __RMCACHEFILE_H__
#define __RMCACHEFILE_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup libcapi
 *  @{
 */

/**
 * Open RMfile handle that caches a libcurl session.
 *
 * @param uncachedHandle - RMfile handle.
 * @param pCachedHandle - Return reference for cached RMfile.
 * @param pCacheBuffer- Application provider buffer of size nbuffers * buffersize
 * @param nbuffer - Number of buffers in cache.
 * @param buffersize - Size of buffers in cache.
 * @return RM_OK or RM_ERROR
 */
RM_LIBRARY_IMPORT_EXPORT RMstatus RMFileCacheOpen( RMfile uncachedHandle, RMfile *pCachedHandle, RMuint8 *pCacheBuffer, RMuint32  nbuffers,  RMuint32  buffersize );

/**
 * Keep a part of a file always cached. This part will use one or more of the buffer
 * we passed in the cache file so users must be aware of what they are doing to not
 * keep too many cached buffers.
 *
 * @param cachedHandle - a cached RMfile returned by RMFileCacheOpen().
 * @param startPosition - The start position of the part we want to keep in cache.
 * @param size - The size of the part we want to keep in cache.
 * @return RM_OK or RM_ERROR.
 */
RM_LIBRARY_IMPORT_EXPORT RMstatus RMFileCacheKeepPartCached ( RMfile cachedHandle, RMint64 startPosition, RMuint32 keepSize);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMCACHEFILE_H__
