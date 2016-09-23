/**
* @author: Zachary Halpern
* @date: 9/16/16
*/
unsigned int count_ones(int n)
{
	int bin[32] = {0}; /* Set all values in this array to 0 */
	int flip = 0;
	int counter = 31; /* We will fill the array backwards */
	int retVal = 0;
	int rem;
	int i;

	
	/* Inform us that we need to flip the bits */
	if (n < 0)
	{
		n = -n;
		flip = 1;
	}
	
	while (n != 0)
	{
		rem = n % 2; /* Determine if the binary is a 1 or a 0 */
		n /= 2; /* Divide n by two to continue determining binary */
		bin[counter] = rem; /* Place the binary in the array */
		counter--;
	}
	
	if (flip != 0)
	{
		/* Step 1: Flip all the bits in the bin */
		for (i = 0; i < 32; i++)
		{
			if (bin[i] == 1)
				bin[i] = 0;
			else
				bin[i] = 1;
		}
		
		/* Step 2: Add 1 to the bin, and add to other rows if needed */
		for (i = 31; i >= 0; i--)
		{
			/* Ok, so we'll need to move over to the next row */
			if (bin[i] == 1)
			{
				bin[i] = 0;
			}
			else
			{
				bin[i] = 1;
				break; /* The row will get one added, no need to continue */
			}
		}
	}
	
    for (i = 0; i < 32; i++)
		if (bin[i] == 1)
			retVal++;

	return retVal;
}