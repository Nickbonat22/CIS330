#include <PNMreaderCPP.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <image.h>

using namespace std;

void PNMreaderCPP :: Execute()
{
    ifstream f_in;
    f_in.open(filename, ios::binary);

    char magicNum[128];
    int width, height, maxval;

    f_in >> magicNum >> width >> height >> maxval;
    
    if (strcmp(magicNum, "P6") != 0)
    {
        fprintf(stderr,"File is not in pnm P6 format\nExiting\n");
        exit(EXIT_FAILURE);
    }
    
    output.pixels = (Pixel *) malloc(width * height * sizeof(Pixel));
    f_in.seekg(1, ios::cur);
    f_in.read((char *) output.pixels, height*width*3);
    
    output.height = height;
    output.width = width;
    output.maxval = maxval;
    
    f_in.close();
}
