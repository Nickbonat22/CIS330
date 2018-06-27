#include <PNMwriter.h>
#include <stdio.h>

void PNMwriter :: Write(char *filename)
{
    FILE *f_out;
    f_out = fopen(filename, "w");
    
    fprintf(f_out, "P6\n%d %d\n%d\n", input1->GetWidth(), input1->GetHeight(), input1->GetMaxval());
    fwrite(input1->GetPixels(), sizeof(Pixel), input1->GetWidth() * input1->GetHeight(), f_out);
    
    fclose(f_out);
}

const char *PNMwriter :: SinkName()
{
	return "PNMwriter";
}


