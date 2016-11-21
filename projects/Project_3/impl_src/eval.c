#include "stats.h"
#include <stdio.h>

#define TLB_ACCESS_TIME       10 /* 10 ns */
#define MEM_ACCESS_TIME      100 /* 100 ns */
#define DISK_IO_TIME   	10000000 /* 10 million ns = 10 ms */

double compute_access_time() {
	
	double timeForFaults, timeForHits, timeForMisses;
	
   /* TASK 6: Compute the average mean access time.  You should only need the
    * numbers contained in the following variables. You may or may not need to
    * use them all:
    *    pagefaults_count   - the number of page faults that occurred
    *                         (note: this _does_ include the unavoidable page
    *                                fault when a process is first brought into
    *                                memory upon starting)
    *    tlbhits_count      - the number of tlbhits that occurred
    *    writes_count       - the number of stores/writes that occurred
    *    reads_count        - the number of reads that occurred
    *
    * Any other values you might need are composites of the above values.  Some
    * of these computations have been done for you, in case you need them.
    */
	
	timeForFaults = (pagefaults_count * DISK_IO_TIME);
	timeForHits = (tlbhits_count * TLB_ACCESS_TIME);
	timeForMisses = ((writes_count + reads_count - tlbhits_count) * MEM_ACCESS_TIME * 2);
	
	/*
	Sample1
	Reads:                  5
	Writes:                 8
	TLB Hits:               6
	Page Faults:            6
	Disk IO:          		0
	60000060 (Off by 1400) [14]
	
	Sample2
	Reads:                 11
	Writes:                14
	TLB Hits:               9 (mine reports 8)
	Page Faults:           12
	Disk IO:         		5
	120000090 (Off by 3200) [32]
	
	Sample3
	Reads:                 10
	Writes:                 5
	TLB Hits:              12
	Page Faults:            3
	Disk IO:        		0
	30000120 (Off by 600) [6]
	
	Sample4
	Reads:                  3
	Writes:                13
	TLB Hits:               0
	Page Faults:           14
	Disk IO:          		8
	140000000 (Off by 3200) [32]
	*/
		
	return timeForFaults + timeForHits + timeForMisses; 
	
	
	return 0;
}
