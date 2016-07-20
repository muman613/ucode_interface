/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   rmxml.h
  @brief  XML Abstraction layer.

  An XML abstraction to parse XML configuration files.

  @ingroup rmcoreapi
*/

#ifndef __RMXML_H__
#define __RMXML_H__

/** @addtogroup rmcoreapi
 *  @{
 */

typedef struct _RMxmlNode RMxmlNode;
typedef struct _RMxmlDocument RMxmlDocument;

/**
   RMParseXMLFile
   
   The newly allocated RMxmlDocument should be freed with
   RMFreeXMLDocument when the user has finished parsing 
   the XML tree.

   @param filename the xml file to parse. This file handle must
                   represent a 7-bit ascii xml text file.
   @returns a newly allocated RMxmlDocument representing the xml document.
 */
RM_LIBRARY_IMPORT_EXPORT RMxmlDocument *RMParseXMLFile (const RMnonAscii *filename);

/**
   RMParseXMLBuffer
   
   The newly allocated RMxmlDocument should be freed with
   RMFreeXMLDocument when the user has finished parsing 
   the XML tree. The input pbuffer buffer should not be freed
   before RMxmlDocument.

   @param pbuffer the xml buffer to parse. This filled with 7 bit US-ASCII
                   characters. The function will return NULL otherwise.
   @param bufferSize the size of the buffer to parse.
   @returns a newly allocated RMxmlDocument representing the xml document.
 */
RM_LIBRARY_IMPORT_EXPORT RMxmlDocument *RMParseXMLBuffer (RMascii *str);

/**
   RMFreeXMLDocument

   @param pdoc frees the xmlDocument and all its associated nodes.
               After calling this function, all RMxmlNodes associated
	       to pdoc are invalid.
 */
RM_LIBRARY_IMPORT_EXPORT void RMFreeXMLDocument (RMxmlDocument *pdoc);

/**
   RMGetRootNodeXMLDocument

   @param pdoc an XML document.
   @returns the root node of the XML document.
 */
RM_LIBRARY_IMPORT_EXPORT RMxmlNode *RMGetRootNodeXMLDocument (RMxmlDocument *pdoc);

/**
   RMGetChildXMLNode

   @param pnode an XML node.
   @returns a child node of pnode.
 */
RM_LIBRARY_IMPORT_EXPORT RMxmlNode *RMGetChildXMLNode (RMxmlNode *pnode);

/**
   RMGetNextXMLNode

   @param pnode an XML node.
   @returns the next sibbling node of pnode.
 */
RM_LIBRARY_IMPORT_EXPORT RMxmlNode *RMGetNextXMLNode (RMxmlNode *pnode);

/**
   RMGetNameXMLNode
   
   @param pnode an XML node.
   @returns the Node's name.
 */
RM_LIBRARY_IMPORT_EXPORT const RMascii *RMGetNameXMLNode (RMxmlNode *pnode);

/**
   RMGetPropertyXMLNode

   @param pnode an XML node.
   @param propertyName a property name.
   @returns the property value.
 */
RM_LIBRARY_IMPORT_EXPORT const RMascii *RMGetPropertyXMLNode (RMxmlNode *pnode, const RMascii *propertyName);

/** @}*/

#endif // __RMXML_H__
