#include <stdio.h>

int main()
{
	const int *p1;
	int * const p2;

	printf("Initial *p1.address= %p *p1.value= %x\n", &p1, p1);
	printf("Initial *p2.address= %p *p2.value= %x\n", &p2, p2);

	/* Increment *p1 and *p2 -- DOES NOT WORK!!! */
	/*(*p1)++;
	(*p2)++;*/

	/* Increment p1 and p2 */
	p1++; /* p1.val += 4 */
	p2++; /* p2.val += 4 */

	printf("(p1)++; RESULT: *p1.address= %p *p1.value= %x\n", &p1, p1);
	printf("(p2)++; RESULT: *p2.address= %p *p2.value= %x\n", &p2, p2);

	/* Sets p1.val = p2.val */
	p1 = p2;
	printf("p1 = p2; RESULT: *p1.address= %p *p1.value= %x\n", &p1, p1);

	return 0;
}
