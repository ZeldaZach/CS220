#ifndef _MACROS_H
#define _MACROS_H

/* Bit positions */
#define VALID			0
#define DIRTY			1
#define USED			2

#define BIT_MASK(n)		/* TASK 1a: Define a mask with nth bit set */

/* bit corresponds to the bit number in flags. Least significant bit is 0 */
#define IS_SET(flags,bit)	/* TASK 1b: Test if bit is set in flags */
#define SET_BIT(flags,bit)	/* TASK 1c: Set the bit in flags to 1 */
#define CLEAR_BIT(flags,bit)	/* TASK 1d: Set the bit in flags to 0 */

#define VADDR_PAGENUM(addr) 0   /* TASK 1e: Get the page number from a virtual address. */

#define VADDR_OFFSET(addr)  0   /* TASK 1f: Get the page number from a virtual address. */

#endif
