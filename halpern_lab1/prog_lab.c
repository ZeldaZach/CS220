/* Implementation of the fact function goes here. */

int fact(int n)
{
	int result = 1;
	int count = n;
	
	if (n <= 1)
		return result;
	
	while (count > 1)
	{
		result *= count;
		count--;
	}
	
	return result;
}
