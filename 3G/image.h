#ifndef IMAGE_H
#define IMAGE_H

#include <stdlib.h>

class Source;

struct Pixel
{
    unsigned char r, g, b;
    
};

class Image
{
	private:
		Pixel *pixels;
	    Source *source;
	    int width, height, maxval;
	public:
	    Image(void);
	    Image(const Image &);
	    Image(Pixel *pix, int h, int w, int maxv);

	    void ResetSize(int h, int w, int maxv);
	    void CreatePixels();

	    int GetHeight() const {return height;}
	    int GetWidth() const {return width;}
	    int GetMaxval() const {return maxval;}
	    Pixel *GetPixels() const {return pixels;}

	    void Update() const;
	    void SetSource(Source *s){source = s;}
};

#endif
