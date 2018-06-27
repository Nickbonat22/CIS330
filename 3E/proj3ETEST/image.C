#include <image.h>
#include <source.h>

Image :: Image(void)
{
    height = 0;
    width = 0;
    maxval = 255;
}

Image :: Image(const Image &img)
{
    height = img.height;
    width = img.width;
    maxval = img.maxval;
    pixels = (Pixel *)malloc(height * width * sizeof(Pixel));
}

Image :: Image(Pixel * pix, int h, int w, int maxv)
{
    pixels = pix;
    height = h;
    width = w;
    maxval = maxv;
}

void Image :: ResetSize(int h, int w, int maxv)
{
    height = h;
    width = w;
    maxval = maxv;
}

void Image :: CreatePixels()
{
    pixels = (Pixel *) malloc(height * width * sizeof(Pixel));
}

void Image :: Update()
{
    source->Update();
}
