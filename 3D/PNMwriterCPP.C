#include <PNMwriterCPP.h>
#include <iostream>
#include <fstream>
#include <stdio.h>

using namespace std;

void PNMwriterCPP :: Write(char *filename)
{
    ofstream f_out;
    f_out.open(filename, ios::binary);

    // writing the headers
    f_out << "P6\n" << input1->width << " " << input1->height << "\n" << input1->maxval << endl;
    f_out.write((char *) input1->pixels, input1->width * input1->height * 3);
    
    f_out.close();
}


