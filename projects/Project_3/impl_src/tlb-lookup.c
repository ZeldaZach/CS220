#include <stdlib.h>
#include <stdio.h>
#include "tlb.h"
#include "pagetable.h"
#include "global.h" /* for tlb_size */
#include "stats.h"
#include "macros.h"

/*******************************************************************************
 * Looks up an address in the TLB. If no entry is found, attempts to access the
 * current page table via cpu_pagetable_lookup().
 *
 * @param vpn The virtual page number to lookup.
 * @param write If the access is a write, this is 1. Otherwise, it is 0.
 * @return The physical frame number of the page we are accessing.
 */

pfn_t tlb_lookup(vpn_t vpn, int write)
{
	pfn_t pfn;
	int i, evicted;

	pfn = 0;
	/*
	 * TASK 2a : Implement TLB lookup
	 * Search the TLB for the given VPN. Make sure to increment tlbhits counter if
	 * it was a hit!
	 */
	
	/* 
	 * STEPS: 
	 * Iterate through the TLB entries: 
	 *    If the entry is valid and the virtual page number is the same
	 * as what is provided as input, then:
	 *        Set the used bit (because we are using it)
	 * 	  If this is a write access, also set the dirty bit. 
	 * 	  We have found the physical page, so we are done. Return the physical page. 
	 */
	
	/* For each entry in the tlb */
	for (i = 0; i < tlb_size; i++)
	{
		/* if valid == true */
		if (IS_SET(tlb[i].flags, VALID))
		{
			/* if tlb->vpn == lookup vpn */
			if (tlb[i].vpn == vpn)
			{
				/* Increment tlbhits since it was a hit */
				tlbhits_count++;

				/* if write is enabled, set write flag */
				if (write)
					SET_BIT(tlb[i].flags, DIRTY);

				/* set used flag */
				SET_BIT(tlb[i].flags, USED);
				
				/* set pfn */
				pfn = tlb[i].pfn;
			}

			/* if pfn is not null */
			if (pfn)
				return pfn;
		}
	}


	/* TASK 2b: If it was a TLB miss, call pagetable_lookup to obtain the physical page. */
	pfn = pagetable_lookup(vpn, write);
	
	/* TASK 2c: Evict an invalid entry and update the TLB with the new page */
	evicted = 0;
	for (i = 0; i < tlb_size; i++)
	{
		/* Get the first invalid entry */
		if (!(IS_SET(tlb[i].flags, VALID)))
		{
			tlb_clearone(tlb[i].vpn);

			tlb[i].vpn = vpn;
			tlb[i].pfn = pfn;
			SET_BIT(tlb[i].flags, VALID);
			
			evicted = 1;
			break;
		}
	}
	
	/* TASK 2d: If no invalid entry was found, we must kick out an unused entry */

	/* STEPS: 
	 * For each entry in the TLB:
	 *   If the entry is unused:
	 *      set the virtual and physical page mapping and mark the entry as used and valid.
	 * 	we have successfully completed the eviction process. we are done. Return the physical page. 
	 *   else:
	 * 	mark the entry as unused, so we can kick it out the next time it is encountered. This is called performing a clock-sweep, because we are mimicking a movement of time. 
	 * Repeat the for STEPS till we find a victim entry to kick out. 
	 */
	
	while (!evicted)
	{
		for (i = 0; i < tlb_size; i++)
		{
			if (!(IS_SET(tlb[i].flags, USED)))
			{
				tlb[i].vpn = vpn;
				tlb[i].pfn = pfn;
				SET_BIT(tlb[i].flags, USED);
				SET_BIT(tlb[i].flags, VALID);
				evicted = 1;
				break;
			}
			else
			{
				CLEAR_BIT(tlb[i].flags, VALID);
			}
		}
	}

	return pfn;
}

