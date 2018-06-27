#include <PNMreader.h>
#include <stdio.h>
#include <image.h>

void PNMreader :: Execute()
{
    FILE *f_in;
    char magicNum[128];
    int width, height, maxval;
    f_in = fopen(filename, "r");
    
    if (f_in == NULL)
    {
        fprintf(stderr, "Unable to open the file!\nExiting\n");
        exit(EXIT_FAILURE);
    }
    
    fscanf(f_in, "%s\n%d %d\n%d\n", magicNum, &width, &height, &maxval);
    
    if (strcmp(magicNum, "P6") != 0)
    {
        fprintf(stderr,"File is not in pnm P6 format\nExiting\n");
        exit(EXIT_FAILURE);
    }
    
    output.pixels = (Pixel *) malloc(width * height * sizeof(Pixel));
    fread(output.pixels, sizeof(Pixel), height*width, f_in);
    
    output.height = height;
    output.width = width;
    output.maxval = maxval;
    
    fclose(f_in);
}
