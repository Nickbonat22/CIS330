#include <image.h>
#include <source.h>

Image :: Image()
{
    height = 0;
    width = 0;
    maxval = 255;
    pixels = NULL;
}

Image :: Image(const Image &img)
{
    height = img.height;
    width = img.width;
    maxval = img.maxval;
    pixels = (Pixel *) malloc(height * width * sizeof(Pixel));

    for(int i = 0; i < width * height; i++)
    {
        pixels[i] = img.pixels[i];
    }
}

Image :: Image(Pixel * pix, int h, int w, int maxv)
{
    height = h;
    width = w;
    maxval = maxv;

    pixels = (Pixel *) malloc(height * width * sizeof(Pixel));

    for(int i = 0; i < width * height; i++)
    {
        pixels[i] = pix[i];
    }
}

Image :: ~Image(void)
{
    if(pixels != NULL)
    {
        free(pixels);
    }
    pixels = NULL;
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

void Image :: SetSource(Source *s)
{
    if(s != NULL)
    {
        source = s;
    }
}

void Image :: Update() const
{
    source->Update();
}
