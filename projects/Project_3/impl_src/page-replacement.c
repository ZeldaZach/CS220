#include <stdlib.h>

#include "types.h"
#include "pagetable.h"
#include "global.h"
#include "process.h"
#include "macros.h"

/*******************************************************************************
 * Finds a free physical frame. If none are available, uses a clock sweep
 * algorithm to find a used frame for eviction.
 *
 * @return The physical frame number of a free (or evictable) frame.
 */

/* A physical page is also called a physical frame or frame */
pfn_t get_free_frame(void)
{
	pfn_t pfn;
	int i, cont;

	cont = 1;
	
	/* TASK 4a: Iterate through the reverse lookup table to see if there is a free frame. If so, return it. 
	 * HINT: The pcb (or the owning process) for a free frame will be NULL. 
	 */
	
	/* For each entry in the rlt, see if we have an empty one */
	for (i = 0; i < NUM_PHYS_PAGES; i++)
		if (rlt[i].pcb == NULL)
			return (pfn_t)i; 

	/* TASK 4b: If none of the frames are free, we must evict a frame.
	 * For each frame, if it is used, set it as unused. If it is already unused, return the frame. 
	 * Repeat the previous step till you find an unused frame. 
	 */ 
	
	/* Loop around looking for an empty page frame, once found return it */
	while (cont)
	{
		for (i = 0; i < NUM_PHYS_PAGES; i++)
		{	
			if (IS_SET(rlt[i].pcb->pagetable[rlt[i].vpn].flags, VALID))
			{
				CLEAR_BIT(rlt[i].pcb->pagetable[rlt[i].vpn].flags, VALID);
			}
			else
			{
				pfn = rlt[i].pcb->pagetable[rlt[i].vpn].pfn;
				return pfn;
			}
		}
	}

	/* This final return is just to satisfy the compiler. 
	 * Control should never reach here. We should have found a frame earlier. 
	 */
	return pfn;

}
