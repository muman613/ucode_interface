/*****************************************
 Copyright © 2001-2012
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   rmsocket.h
  @brief  Implementation of Linux sockets
  @ingroup libcapi
*/

#ifndef __RMSOCKET_H__
#define __RMSOCKET_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup libcapi
 *  @{
 */

/** type used to manipulate socket */
typedef struct _RMsocket *RMsocket;

/// 
/**
   open a stream socket (connected socket)

   @param ip    
   @param port  
   @return 0 on failure
*/
RM_LIBRARY_IMPORT_EXPORT RMsocket RMSocketOpenStream(const RMascii *ip, RMuint16 port);

/// 
/**
   open a stream socket (connected socket), with a timeout specified

   @param ip    
   @param port  
   @param connect_timeout
   @return 0 on failure
*/
RM_LIBRARY_IMPORT_EXPORT RMsocket RMSocketOpenStreamWithTimeout(const RMascii *ip, RMuint16 port, RMuint32 connect_timeout);

/// 
/**
   open a datagram socket (non connected soocket)

   @param ip    
   @param port  
   @return 0 on failure
*/
RM_LIBRARY_IMPORT_EXPORT RMsocket RMSocketOpenDgram(const RMascii *ip, RMuint16 port);

/// 
/**
   wait on multiple sockets

   @param  tabSocket			 : table of sockets to wait for
   @param  nbEltInTabSocket		 : nb element in tab socket
   @param  nbMicroSecondsTimeOut : timeout (microseconds value)   
   @param  tabSocketRes			 : table of sockets that have data ready.
   @return the number of sockets that have data ready,
           0 means timeout expired and -1 means failure.
*/
RM_LIBRARY_IMPORT_EXPORT RMint16 RMSocketSelect(RMsocket *tabSocket, RMuint8 nbEltInTabSocket, RMuint32 nbMicroSecondsTimeOut, RMsocket *stabSocketRes);

/// 
/**
   Sends request (Laurent to document)
   
   (Send may be used only when the socket is in a connected state)

   @param  sock					 : the socket 
   @param  request				 : request to send
   @return RM_OK if all could be sent.
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMSocketSend(RMsocket sock, RMuint8 * request, RMuint32 sizeOFRequest);

/// 
/**
   sends data (Laurent to document)

   @param sock  
   @param request       
   @param sizeOFRequest 
   @param ip    
   @param port  
   @return RM_OK if all could be sent.
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMSocketSendto(RMsocket sock, RMuint8 * request, RMuint32 sizeOFRequest, const RMascii *ip, RMuint16 port);

/// 
/**
   receives data from a connected socket (SOCK_STREAM)
   (The recv call is normally used only on a connected socket)

   @param sock  
   @param buffer        
   @param maxSizeOfBuffer       
   @return the number of bytes actually received.
*/
RM_LIBRARY_IMPORT_EXPORT RMint32 RMSocketRecv(RMsocket sock, RMuint8 * buffer, RMuint32 maxSizeOfBuffer);

/// 
/**
   close a socket

   @param  socket
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMSocketClose(RMsocket sock);

/// 
/**
   Join a multicast session

   @param sock : socket we want to add to the multicast session
   @return RM_OK if no error occurs
*/

RM_LIBRARY_IMPORT_EXPORT RMstatus RMSocketJoinMulticastSession(RMsocket sock, const RMascii *ip, RMuint32 ttl);

/// 
/**
   Get host address 

   @return host adress in ascii
*/

RM_LIBRARY_IMPORT_EXPORT RMascii * RMSocketGetHostAddress(void);

/// 
/**
   convert ip address into a binary data
   this function should not be there, but we need that for concurrent module !!!!!

   @param ip : adress ip
   @return 0 if wrong ip binary data otherwise
*/

RM_LIBRARY_IMPORT_EXPORT RMuint32 RMSocketInetAddr(RMascii *ip);

/// 
/**
   convert an hote name into an ip adress (standardized notation)

   @param name : host name

   @return host adress in ascii
*/

RM_LIBRARY_IMPORT_EXPORT RMascii *RMSocketGetAddressFromName(RMascii *name);

/// 
/**
   Check if the socket is still connected to the server

   @param sock : socket descriptor

   @return TRUE if connected FALSE otherwise
*/

RM_LIBRARY_IMPORT_EXPORT RMbool RMSocketIsAlive(RMsocket sock);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMSOCKET_H__
