#include <stdlib.h>
#include <stdio.h>
#include "point.h"

int contains_loop(Point *p)
{
	short int retVal = 0;
	Point *current, *ahead_2;

	/* Step 1: Does p->next even exist? */
	if (p->next != NULL)
	{
		/* Step 2: Ok there's another pointer. Does it point to itself? */
		if (p == p->next)
		{
			/* This is ok, then it's a perma loop! */
			retVal = 1;
		}
		else
		{
			/* Step 3: Ok, so p != p->next ... lets start our increments and loops */
			if (p->next->next != NULL)
			{
				current = p;
				ahead_2 = p->next->next;

				while (1)
				{
					/* We need to make sure none of the upcoming elements are NULLs, otherwise who cares */
					if (
						current == NULL ||
						current->next == NULL ||
						ahead_2 == NULL ||
						ahead_2->next == NULL ||
						ahead_2->next->next == NULL
					   )
					{
						break;
					}
					else if (current == ahead_2)
					{
						retVal = 1;
						break;
					}

					current = current->next;
					ahead_2 = ahead_2->next->next;
				}
			}
		}
	}
	return retVal;
}

Point* transform_points(Point *points, Point *origin)
{
	Point *newPointList = malloc(sizeof(Point)*16);
	short int lastLoop = 0;
	/**
	*points is a pointer to the first point in a list of points
	AKA *points -> [1:Point] -> [2:Point] -> [3:Point]
	*/

	/**
	Use *origin.x, .y, and .z and add them to the old values
	AKA new Point(*points.x + *origin.x, *points.y + *origin.y, *points.z + *origin.z)
	Use malloc when necessary
	*/

	while (1)
	{
		newPointList->x = points->x + origin->x;
		newPointList->y = points->y + origin->y;
		newPointList->z = points->z + origin->z;
		newPointList->next = points->next;

		points = points->next;
		newPointList = newPointList->next;

		printf("Points X: %f\nOrigin X: %f\nNew X: %f\n", points->x, origin->x, newPointList->x);

		if (lastLoop)
			break;
		else if (points->next == NULL)
			lastLoop = 1;

	}
}

int main()
{
	Point test1;
	Point test2;
	Point test3;
	Point test4;

	test4.x = 4.0;
	test4.y = 4.5;
	test4.z = 4.66;
	test4.next = NULL;

	test3.x = 3.0;
	test3.y = 3.5;
	test3.z = 3.66;
	test3.next = &test4;

	test2.x = 1.0;
	test2.y = 1.5;
	test2.z = 1.66;
	test2.next = &test3;

	test1.x = 2.05;
	test1.y = 2.51;
	test1.z = 2.63;
	test1.next = &test2;

	printf("Loop: %d\n", contains_loop(&test1));

	transform_points(&test1, &test4);

	return 0;
}
