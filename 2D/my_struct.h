typedef struct 
{
	double radius;
	double x;
	double y;
} Circle;

typedef struct 
{
	double minX;
	double minY;
	double maxX;
	double maxY;
} Rectangle;

typedef struct 
{
	double minY;
	double maxY;
	double pt2X;
	double pt1X;
} Triangle;

typedef union {
	Circle circ;
	Rectangle rec;
	Triangle tri;
} ShapeUnion;

// identifies whether it's a circle, rectangle, or triangle
typedef enum {c, r, t} ShapeType;

// so the compiler knows this will be defined later
struct Shape;

typedef struct {
	//function pointers
	double( *GetArea)(struct Shape *);
	void (* GetBoundingBox)(struct Shape *, double *);
} FunctionTable;

struct Shape {
	// data members for Shape
	ShapeUnion sunion;
	ShapeType stype;
	FunctionTable ft;
};