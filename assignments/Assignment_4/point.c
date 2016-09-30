#include <stdlib.h>
#include "point.h"

int contains_loop(Point *p)
{
	short int retVal = 0;
	Point *current, *ahead_2;

	/* Step 1: Does p->next even exist? */
	if (p != NULL && p->next != NULL)
	{
		/* Step 2: Ok there's another pointer. Does it point to itself? */
		if (p == p->next)
		{
			/* This is ok, then it's a perma loop! */
			retVal = 1;
		}
		else
		{
			/*
			Step 3: Ok, so p != p->next ... lets start our increments and loops
			If p->next->next is NULL, then we have no reason to do anything and know this is not a perma loop
			*/
			if (p->next->next != NULL)
			{
				/* We're gonna do a skip 2. A fast runner will eventually lap a slow runner on a circlular track */
				current = p;
				ahead_2 = p->next->next;

				while (1)
				{
					/* We need to make sure none of the upcoming elements are NULLs, otherwise who cares, it's not a loop */
					if ( current == NULL || current->next == NULL || ahead_2 == NULL || ahead_2->next == NULL )
					{
						break;
					}
					else if (current == ahead_2)
					{
						retVal = 1;
						break;
					}
					
					/* Ok, so lets increment the "runners". current takes 1 step, ahead_2 takes 2 */
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
	Point *newPointList = malloc(sizeof(Point));
	Point *beginning = newPointList; /* Store beginning of new pointer chain to return */
	short int lastLoop = 0;

	/* If points is null, then this function is null */
	if (points == NULL)
		return NULL;
	
	/* For each points in the list... */
	while (points != NULL)
	{
		/* new = old+origin */
		newPointList->x = points->x + origin->x;
		newPointList->y = points->y + origin->y;
		newPointList->z = points->z + origin->z;
		
		/* Break out if we have no next point */
		if (points->next == NULL)
			break;
		
		/* Ok so there's a next point; lets allocate memory to store it in */
		newPointList->next = malloc(sizeof(Point));
		
		/* Incremenet the two lists to the next pointer in their fields */
		newPointList = newPointList->next;
		points = points->next;
	}

	return beginning;
}