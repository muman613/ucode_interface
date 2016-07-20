/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
   @file rmsax.h
   @brief Implementation of a Simple API XML parser

   @ingroup rmcoreapi
*/


#ifndef __RMSAX_H__
#define __RMSAX_H__

/** @addtogroup rmcoreapi
 *  @{
 */

/**
   Called when the parser encounters a start element.
   ie: when it encounters <foo> or <foo/>

   @param name contains the name of the element. 
               Here, "foo".
   @param attributes contains the list of attributes.
                     It is a NULL-terminated array.
		     It must be freed by by the callee.
   @param context the context.
 */
typedef void (*RMsaxStartElement) (const RMascii *name, 
				   const RMascii **attributes,
				   void *context);
/**
   Called when the parser encounters a start element.
   ie: when it encounters </foo> or <foo/>

   @param name contains the name of the element. 
               Here, "foo".
   @param context the context.
 */
typedef void (*RMsaxEndElement) (const RMascii *name, 
				 void *context);
/**
   Called upon parsing error.

   @param context the context.
 */
typedef void (*RMsaxFail) (void *context);

typedef struct {
	RMsaxStartElement  startElementCallback;
	RMsaxEndElement    endElementCallback;
	RMsaxFail          failCallback;
} RMsaxVTable;

/**
   This function will parse the input string.
   This function is of course thread-safe 
   (ie: it does not use any global variables).

   @param pbuffer a NULL-terminated ASCII string.
   @param vtable the list of callback functions to be called during
                 parsing.
   @param context the context pointer to pass to all callback functions.
 */
RM_LIBRARY_IMPORT_EXPORT RMstatus RMParseSax (RMascii *pbuffer,
		     const RMsaxVTable *vtable,
		     void *context);

/** @}*/

#endif // __RMSAX_H__
