#include <stdlib.h>
#include <stdio.h>




struct Point{
	float x;
	float y;
	float z;
	struct Point *next;
};


int contains_loop(Point *p);
Point* transform_points(Point *p1, Point *p2);