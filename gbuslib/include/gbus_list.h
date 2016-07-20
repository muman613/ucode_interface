/*****************************************
 Copyright © 2001-2003  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/
/**
  @file   gbus_list.h
  @brief  This is a duoble linked list implementation

  @author Julien Soulier
  @date   2003-04-11
*/

#ifndef __GBUS_LIST_H__
#define __GBUS_LIST_H__

#include "llad/include/gbus.h"

RM_EXTERN_C_BLOCKSTART

struct gbus_list {
	RMuint32 next;
	RMuint32 prev;
};

/**
   Initializes the next and prev pointers to create an empty list

   @param pgbus 
   @param gbus_addr     
*/
struct gbus_list *gbus_list_open(struct gbus *pgbus, RMuint32 gbus_addr);


/**
   Closes the list

   @param pgbus 
   @param list  
*/
void gbus_list_close(struct gbus *pgbus, struct gbus_list *list);

/**
   Adds one entry in the double linked list (algorithm in O(1))

   @param pgbus 
   @param head  
   @param entry      
*/
void gbus_list_add_entry(struct gbus *pgbus, struct gbus_list *head, struct gbus_list *entry);

/**
   Removes one entry from the double linked list (algorithm in O(1))

   @param pgbus 
   @param entry 
*/
void gbus_list_del_entry(struct gbus *pgbus, struct gbus_list *entry);

/**
   returns next entry in list

   @param pgbus 
   @param entry 
*/
struct gbus_list *gbus_list_next_entry(struct gbus *pgbus, struct gbus_list *entry);

/**
   returns previous entry in list

   @param pgbus 
   @param entry 
*/
struct gbus_list *gbus_list_prev_entry(struct gbus *pgbus, struct gbus_list *entry);

RM_EXTERN_C_BLOCKEND

#endif // __GBUS_LIST_H__

