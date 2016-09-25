#include <stdlib.h>
#include <stdio.h>

typedef struct {
	float x;
	float y;
	float z;
	struct Point *next;
} Point = {0,0,0,NULL};


int contains_loop(Point *p);
Point* transform_points(Point *p1, Point *p2);