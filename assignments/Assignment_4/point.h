#ifndef POINT_H
#define POINT_H

struct _Point{
	float x;
	float y;
	float z;
	struct _Point *next;
};

typedef struct _Point Point;


int contains_loop(Point *p);
Point* transform_points(Point *p1, Point *p2);

#endif