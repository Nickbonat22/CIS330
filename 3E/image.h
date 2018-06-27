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

	    virtual ~Image(void);

	    int GetHeight(){return height;}
	    int GetWidth(){return width;}
	    int GetMaxval(){return maxval;}
	    Pixel *GetPixels(){return pixels;}

	    void Update();
    void SetSource(Source *s);
};

#endif
