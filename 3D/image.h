#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>

struct Pixel
{
    unsigned char r, g, b;
    
};

class Image
{
	public:
	    Pixel *pixels;
	    int width, height, maxval;
	    Image(void);
	    Image(const Image &);
	    Image(Pixel *pix, int h, int w, int maxv);

};

#endif
