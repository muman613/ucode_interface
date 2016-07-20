


#ifndef __KLLAD_PROC_H__
#define __KLLAD_PROC_H__

#include <linux/proc_fs.h>
#include "directpool.h"

#define PROC_ENTRY_FILE_ACCESS 0444

extern unsigned long kdmapool_usage_mask;
extern struct kdmapool bufferpools[MAXDMAPOOL];

int proc_read_pool(char *, char **, off_t, int, int *, void *);

void add_driver_proc_entry(void);
void rm_driver_proc_entry(void);

void add_driver_proc_files(void);
void rm_driver_proc_files(void);
#endif /* __KLLAD_PROC_H__ */

