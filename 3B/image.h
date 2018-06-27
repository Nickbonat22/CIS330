#ifndef IMAGE_H
#define IMAGE_H
#include <stdlib.h>

struct Pixel
{
	unsigned char r, g, b;

};

class Image
{
	Pixel *pixels;
	int width, height, maxval;

public:
	Image(void);
	Image(const Image &);
	Image(Pixel *pix, int h, int w, int maxv);
	//~Image(void);
};

#endif