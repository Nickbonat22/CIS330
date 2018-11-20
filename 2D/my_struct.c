#include <prototypes.h>

// Circle
void InitializeCircle(struct Shape *shape, double radius, double originX, double originY)
{
	shape->stype = c;
	shape->sunion.circ.radius = radius;
	shape->sunion.circ.x = originX;
	shape->sunion.circ.y = originY;

	shape->ft.GetArea = GetCircleArea;
	shape->ft.GetBoundingBox = GetCircleBoundingBox;
}

double GetCircleArea(struct Shape *shape)
{
	return 3.14159 * shape->sunion.circ.radius * shape->sunion.circ.radius;
}

void GetCircleBoundingBox(struct Shape *shape, double *bbox)
{
	bbox[0] = shape->sunion.circ.x - shape->sunion.circ.radius;
	bbox[1] = shape->sunion.circ.x + shape->sunion.circ.radius;
	bbox[2] = shape->sunion.circ.y - shape->sunion.circ.radius;
	bbox[3] = shape->sunion.circ.y + shape->sunion.circ.radius;
}

// Rectangle
void InitializeRectangle(struct Shape *shape, double minX, double maxX, double minY, double maxY)
{
	shape->stype = r;
	shape->sunion.rec.minX = minX;
	shape->sunion.rec.maxX = maxX;
	shape->sunion.rec.minY = minY;
	shape->sunion.rec.maxY = maxY;

	shape->ft.GetArea = GetRectangleArea;
	shape->ft.GetBoundingBox = GetRectangleBoundingBox;

}

double GetRectangleArea(struct Shape *shape)
{
	return (shape->sunion.rec.maxX - shape->sunion.rec.minX) * (shape->sunion.rec.maxY - shape->sunion.rec.minY);
}

void GetRectangleBoundingBox(struct Shape *shape, double *bbox)
{
	bbox[0] = shape->sunion.rec.minX;
	bbox[1] = shape->sunion.rec.maxX;
	bbox[2] = shape->sunion.rec.minY;
	bbox[3] = shape->sunion.rec.maxY;
}

// Triangle
void InitializeTriangle(struct Shape *shape, double pt1X, double pt2X, double minY, double maxY)
{
	shape->stype = t;
	shape->sunion.tri.pt1X = pt1X;
	shape->sunion.tri.pt2X = pt2X;
	shape->sunion.tri.minY = minY;
	shape->sunion.tri.maxY = maxY;

	shape->ft.GetArea = GetTriangleArea;
	shape->ft.GetBoundingBox = GetTriangleBoundingBox;
}
double GetTriangleArea(struct Shape *shape)
{
	return (shape->sunion.tri.pt2X - shape->sunion.tri.pt1X) * (shape->sunion.tri.maxY - shape->sunion.tri.minY) / 2;
}

void GetTriangleBoundingBox(struct Shape *shape, double *bbox)
{
	bbox[0] = shape->sunion.tri.pt1X;
	bbox[1] = shape->sunion.tri.pt2X;
	bbox[2] = shape->sunion.tri.minY;
	bbox[3] = shape->sunion.tri.maxY;
}