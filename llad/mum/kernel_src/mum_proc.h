/*****************************************
 Copyright © 2001-2005  
 Sigma Designs, Inc. All Rights Reserved
 Proprietary and Confidential
 *****************************************/

/**
  @file   mum_proc.h
  @brief  /proc related functions headers
             for mum kernel module
  @author Sylvain Garrigues
  @date   2005-12-14
*/

#ifndef __MUM_PROC_H__
#define __MUM_PROC_H__

#include <linux/proc_fs.h>
#include "common.h"

#define PROC_ENTRY_FILE_ACCESS 0444

struct _pool_data {
               	struct realmagicprivate *pR; 
                unsigned long dmapool_id;
}; 

struct mum_proc_private {
        struct proc_dir_entry *driver_dir;
        struct proc_dir_entry *board_dir; 
        struct proc_dir_entry *DMA_dir;
        struct _pool_data pool_data[MAXDMAPOOL];
};

extern struct mum_proc_private proc_data[MAXLLAD];

int proc_read_pool(char *, char **, off_t, int, int *, void *);

void add_driver_proc_entry(void);
void rm_driver_proc_entry(void);

void add_board_proc_entry(int);
void rm_board_proc_entry(int);

void add_board_proc_files(int);
void rm_board_proc_files(int);
#endif /* __MUM_PROC_H__ */

