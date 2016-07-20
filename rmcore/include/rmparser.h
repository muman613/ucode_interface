/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
   @file   rmparser.h
   @brief  Generic parsing functions

   These functions can be used to parse ASCII / Unicode coded text to RMstring
   buffers.

   @author Pascal Cannenterre
   @date   2001-04-16
   @ingroup rmcoreapi
*/
#ifndef __RMPARSER_H__
#define __RMPARSER_H__

RM_EXTERN_C_BLOCKSTART

/** @addtogroup rmcoreapi
 *  @{
 */

/**
   A URL including a board number looks like [3]FILE@MP4://...; this functions
   sets *pBoardNumber to 3 and urlWithoutBoardNumber is FILE@MP4://...

   @param url   
   @param urlWithoutBoardNumber 
   @param pBoardNumber  
   @return not RM_OK if URL does not begin with `['
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMGetBoardNumberFromUrl(const RMascii *url, RMascii **urlWithoutBoardNumber, RMuint32 *pBoardNumber);

/**
   A URL including a many properties looks like [3,674,78,698]FILE@MP4://...; this functions
   sets **properties to "3,674,78,698" and urlWithoutProperties is FILE@MP4://...

   @param url   
   @param urlWithoutProperties
   @param properties int array that will contain properties
   @return not RM_OK if URL does not begin with `['
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMGetBoardPropertiesFromUrl(const RMascii *url, RMascii **urlWithoutProperties, RMascii **properties);


/**
   On EM86XX, the board number is used to pass a handle to RUA, so it looks like :
     "0,980956809568,0,1"

   This function splits the sting to get an array of RMuint32 :
     {0,980956809568,0,1}
   
   @param boardNumberAsString 
   @param properties Array used to get properties
   @param size size of the array
   @return RMuint32 0 upon error, otherwise number of properties affected in properties
*/
RM_LIBRARY_IMPORT_EXPORT RMuint32 RMGetPropertiesFromBoardNumber(const RMascii *boardNumberAsString, RMuint32 *properties, RMuint32 size);


/**
   

   @param url   
   @param prefix        
   @param newUrl        
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMGetUrlPrefix(const RMascii *url, RMascii **prefix, RMascii **newUrl);


/**
   get the server IP from an url

   @param url : url
   @param serverIP : server IP found
   @return RM_ERROR if url is wrong
*/

RM_LIBRARY_IMPORT_EXPORT RMstatus RMGetServerIPFromUrl(RMascii *url, RMascii **serverIP);


/**   
   get server port from an url
   url has to be like : rtsp://server.ip/filename#parameter1=value1, ..., paramterN=valueN
   (parameters are optional)

   @param url : url to parse
   @param port : port number
   @return RM_ERROR if wrong url
*/

RM_LIBRARY_IMPORT_EXPORT RMstatus RMGetServerPortFromUrl(RMascii *url, RMuint16 *port);


/**
   get filename from an url
   url has to be like : rtsp://server.ip/filename#parameter1=value1, ..., paramterN=valueN
   (parameters are optional)

   @param url : url to parse
   @param fileName
   @return RM_ERROR if wrong url
*/

RM_LIBRARY_IMPORT_EXPORT RMstatus RMGetFileNameFromUrl(RMascii *url, RMascii **fileName);


/**
   parse the url to found the value of a parameter.

   @param url   url to parse.
   @param name  name of the parameter
   @param value parameter value
   @return RM_ERROR if parameter not found
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMGetParameterFromUrl(RMascii *url, RMascii *name, RMuint32 *value);

/**
   parse the url to found the value of a parameter.

   @param url   url to parse.
   @param name  name of the parameter
   @param value parameter value
   @return RM_ERROR if parameter not found
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMGetRealParameterFromUrl(RMascii *url, RMascii *name, RMreal *value);



/**
   parse the url to found a parameter. The parameter is an ascii string.

   @param url   
   @param name  
   @param value the pre allocated ascii string.
   @param maxLength the length of value    
   @return 
*/
RM_LIBRARY_IMPORT_EXPORT RMstatus RMGetAsciiParameterFromUrl(RMascii *url, RMascii *name, RMascii *value, RMuint32 maxLength);

/**
   get the url with no vod parameters 

   @param url : original url   
   @param newUrl : url wuthout vod parameters
   @return RM_ERROR if wrong url
*/

RM_LIBRARY_IMPORT_EXPORT RMstatus RMGetUrlWithoutParametersFromUrl(RMascii *url, RMascii **newUrl);

/// 
/**
   get the string query from url (rtsp://my_server/my_file?my_query=my_value

   @param url : original url  
   @param query : query string
   @return  RM_ERROR if wrong url
*/

RM_LIBRARY_IMPORT_EXPORT RMstatus RMGetQueryFromUrl(RMascii *url, RMascii **query);

/** @}*/

RM_EXTERN_C_BLOCKEND

#endif // __RMPARSER_H__
