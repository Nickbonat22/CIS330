#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <filter.h>

Filter::Filter(void)
{
    ;
}

void Shrinker :: Execute()
{
    int i, j;
    
    // in the case that there's an odd number of pixels(from piazza)
    output.width = (input1->width + 1)/2;
    output.height = (input1->height + 1)/2;
    output.pixels = (Pixel *)malloc(input1->height * input1->width * sizeof(Pixel));
    
    for(i = 0; i < output.height; i++)
    {
        for(j = 0; j < output.width; j++)
        {
            output.pixels[i * output.width + j] = input1->pixels[(2 * i * input1->width) + (j * 2)];
        }
        output.maxval = input1->maxval;
    }
}

void LRCombine :: Execute()
{
    int i,j;
    output.width = input1->width + input2->width;
    output.height = input1->height;
    output.pixels = (Pixel *)malloc(output.height * output.width * sizeof(Pixel));
    
    for(int i = 0; i < output.height; i++)
    {
        Pixel *left = input1->pixels + i * input1->width;
        Pixel *right = input2->pixels + i * input2->width;
        Pixel *pixwidth = output.pixels + i * output.width;
        
        memcpy(pixwidth, left, input1->width * sizeof(Pixel));
        memcpy(pixwidth + input1->width, right, input2->width * sizeof(Pixel));
        
    }
}

void TBCombine :: Execute()
{
    
    int i;
    output.width = input1->width;
    output.height = input1->height + input2->height;
    output.pixels = (Pixel *)malloc(output.height * output.width * sizeof(Pixel));
    
    for(i = 0; i < input1->width * input1->height; i++)
    {
        output.pixels[i].r = input1->pixels[i].r;
        output.pixels[i].g = input1->pixels[i].g;
        output.pixels[i].b = input1->pixels[i].b;
    }
    for(i = 0; i < input1->width * input1->height; i++)
    {
        output.pixels[input1->width * input1->height + i].r = input2->pixels[i].r;
        output.pixels[input1->width * input1->height + i].g = input2->pixels[i].g;
        output.pixels[input1->width * input1->height + i].b = input2->pixels[i].b;
    }
    
}

void Blender :: Execute()
{
    output.width = input1->width;
    output.height = input1->height;
    output.pixels = (Pixel *)malloc(output.height * output.width * sizeof(Pixel));
    
    for(int i = 0; i < output.width*output.height; i++){
        (output.pixels)[i].r = (input1->pixels)[i].r * factor + (input2->pixels)[i].r * (1 - factor);
        (output.pixels)[i].g = (input1->pixels)[i].g * factor + (input2->pixels)[i].g * (1 - factor);
        (output.pixels)[i].b = (input1->pixels)[i].b * factor + (input2->pixels)[i].b * (1 - factor);
    }
}
