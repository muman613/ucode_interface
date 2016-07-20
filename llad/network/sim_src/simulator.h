#ifndef SIMULATOR_H
#define SIMULATOR_H

/* Load a number of bytes from dm, pm or dram : return an array of bytes (big endian) */
#define COMMAND_LOADPM   0x0001
#define COMMAND_LOADDM   0x0002
#define COMMAND_LOADDRAM 0x0004
#define COMMAND_READMEM  0x0008


/* Put a number of bytes into dm, pm or dram */
#define COMMAND_SAVEPM   0x0010
#define COMMAND_SAVEDM   0x0020
#define COMMAND_SAVEDRAM 0x0040
#define COMMAND_WRITEMEM 0x0080


/* Make a host interruption */
#define COMMAND_BREAK 0x0100

/* Clear memory command */
#define COMMAMD_CLEARMEM 0x1000

/* Start, Reset or Stop mambo */
#define COMMAND_START		0x0200
#define COMMAND_RESET		0x0400
#define COMMAND_STOP		0x0800

/* Return the identity of the target */
#define COMMAND_IDENTIFY	0x2000
/* Return the overlay table */
#define COMMAND_OVLTABLE	0x3000
/* Return the number of cycles already done by the CPU */
#define COMMAND_CYCLES		0x4000
#define COMMAND_CYCLES2		0x4001
#define COMMAND_RESETCYCLES 0x8000

/* Return the status of the CPU */
#define COMMAND_GETSTATUS	0x10000

#define COMMAND_DUMPON		0x9000
#define COMMAND_DUMPOFF		0x9001

#define COMMAND_LAUNCH		0xA000

typedef struct
{
	/* The chip number to send the command */
	unsigned int chip;

	/* The command (see below) */
	unsigned int command;

	/* The address in bytes */
	unsigned int address;

	/* The number of bytes to load or to store */
	unsigned int nbytes;

}	hardlib_command_t;




// Status of the CPU...
#define MAMBO_OK 0                    // No error
#define MAMBO_ERROR_DEPENDENCY 0x0001 // Illegal instruction sequence
#define MAMBO_ERROR_ILLEGALOP  0x0002 // Illegal opcode
#define MAMBO_ERROR_DRAMACCESS 0x0003 // Illegal access to DRAM
#define MAMBO_ERROR_DMACCESS   0x0004 // Illegal access to DM
#define MAMBO_ERROR_PMACCESS   0x0005 // Illegal access to PM

#endif

/* End of simulator.h */
