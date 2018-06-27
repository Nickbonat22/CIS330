#include <PNMwriter.h>
#include <stdio.h>

void PNMwriter :: Write(char *filename)
{
    FILE *f_out;
    f_out = fopen(filename, "w");
    
    fprintf(f_out, "P6\n%d %d\n%d\n", input1->width, input1->height, input1->maxval);
    fwrite(input1->pixels, sizeof(Pixel), input1->width * input1->height, f_out);
    
    fclose(f_out);
}


