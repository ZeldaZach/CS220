/**
* @author: Zachary Halpern
* @date: 9/16/16
*/
unsigned int count_letters(unsigned long num)
{
	/* Get the x's */
	int x[9]; /* x[0], x[1], x[2], x[3], x[4], x[5], x[6], x[7], x[8] */
	int i;
	int letterCount = 0;
	int tmpNum = num;
	
	if (num == 0)
		return 4;
	else if (num == 1000000000)
		return 10;
	else if (num < 0 || num > 1000000000)
		return 0;
	
	for (i = 8; i >= 0; i--)
	{		
		x[i] = tmpNum % 10;
		tmpNum /= 10;
	}
	
	if (num < 1000)
	{
		letterCount += count_hundreds(x[6],x[7],x[8]);
	}
	else if (num < 1000000)
	{
		letterCount += count_thousands(x[3],x[4],x[5]);
		letterCount += count_hundreds(x[6],x[7],x[8]);
	}
	else if (num < 1000000000)
	{
		letterCount += count_millions(x[0],x[1],x[2]);
		letterCount += count_thousands(x[3],x[4],x[5]);
		letterCount += count_hundreds(x[6],x[7],x[8]);
	}

	return letterCount;
}

int count_ones(unsigned int num)
{
	int letterCount = 0;
	switch (num)
	{
		case 1:
		case 2:
		case 6:
		letterCount += 3;
		break;
		
		case 3:
		case 7:
		case 8:
		letterCount += 5;
		break;

		case 4:
		case 5:
		case 9:
		letterCount += 4;
		break;
	}
	return letterCount;
}

int count_hundreds(int x7, int x8, int x9)
{
	int letterCount = 0;
	if (x7 == 0 && x8 == 0 && x9 == 0)
		return 0;
	
	if (x7 != 0)
	{
		letterCount += count_ones(x7); /* TWO hundred */
		letterCount += 7; /* "Hundred" */
	}
	
	if (x8 == 1) /* A weird "teen" thing */
	{
		switch (x9)
		{
			case 0:
			letterCount += 3;
			break;

			case 1:
			case 2:
			letterCount += 6;
			break;
		
			case 3:
			case 4:
			case 9:
			letterCount += 8;
			break;
		
			case 5:
			case 6:
			letterCount += 7;
			break;
		
			case 7:
			case 8:
			letterCount += 9;
			break;
		}
	}
	else
	{
		switch (x8)
		{
			case 2:
			case 3:
			case 8:
			case 9:
			letterCount += 6;
			break;
			
			case 4:
			case 5:
			case 6:
			letterCount += 5;
			break;
			
			case 7:
			letterCount += 7;
			break;
		}
		
		if (x9 != 0)
			letterCount += count_ones(x9);
	}
	
	return letterCount;
}

int count_thousands(int x4, int x5, int x6)
{
	int letterCount = 0;
	letterCount += count_hundreds(x4,x5,x6);
	letterCount += 8; /* "Thousand" */
	return letterCount;
}

int count_millions(int x1, int x2, int x3)
{
	int letterCount = 0;
	letterCount += count_hundreds(x1,x2,x3);
	letterCount += 7; /* "Million" */
	return letterCount;
}