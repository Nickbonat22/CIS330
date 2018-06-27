#include <stdio.h>
#include <string.h>
#include <image.h>
#include <functions.h>

void ReadImage(char *filename, Image &output)
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
 	
 	output.height = height;
 	output.width = width;
 	output.maxval = maxval;
 	output.pixels = (Pixel *) malloc(width * height * sizeof(Pixel));

 	fread(output.pixels, sizeof(Pixel), height*width, f_in);
 	fclose(f_in);
}


void WriteImage(char *filename, Image &img)
{
	FILE *f_out;
	f_out = fopen(filename, "w");
	if (f_out == NULL)
	{
		fprintf(stderr,"Unable to open the file!\nExiting\n");
		exit(EXIT_FAILURE);
	}

    fprintf(f_out, "P6\n%d %d\n%d\n", img.width, img.height, img.maxval);
	fwrite(img.pixels, sizeof(Pixel), img.height * img.width , f_out);
	fclose(f_out);

}

void HalfSize(Image &input, Image &output)
{
	int i, j;

	// in the case that there's an odd number of pixels(from piazza)
	output.width = (input.width + 1)/2;
	output.height = (input.height + 1)/2;
	output.pixels = (Pixel *)malloc(input.height * input.width * sizeof(Pixel));
	
	for(i = 0; i < output.height; i++)
	{
		for(j = 0; j < output.width; j++)
		{
			output.pixels[i * output.width + j] = input.pixels[(2 * i * input.width) + (j * 2)];
		}
		output.maxval = input.maxval;
	}

}

void LeftRightCombine(Image &leftInput, Image &rightinput, Image &output)
{
	int i,j;
	output.width = leftInput.width + rightinput.width;
	output.height = leftInput.height;
	output.pixels = (Pixel *)malloc(output.height * output.width * sizeof(Pixel));

	for(int i = 0; i < output.height; i++)
	{
		Pixel *left = leftInput.pixels + i * leftInput.width;
		Pixel *right = rightinput.pixels + i * rightinput.width;
		Pixel *pixwidth = output.pixels + i * output.width;

		// copying the appropriate memory to output
		memcpy(pixwidth, left, leftInput.width * sizeof(Pixel));
		memcpy(pixwidth + leftInput.width, right, rightinput.width * sizeof(Pixel));

	}
}

void TopBottomCombine(Image &topInput, Image &bottomInput, Image &output)
{
	int i;
	output.width = topInput.width;
	output.height = topInput.height + bottomInput.height;
	output.pixels = (Pixel *)malloc(output.height * output.width * sizeof(Pixel));

	for(i = 0; i < topInput.width * topInput.height; i++)
	{
		output.pixels[i].r = topInput.pixels[i].r;
		output.pixels[i].g = topInput.pixels[i].g;
		output.pixels[i].b = topInput.pixels[i].b;
	}
	for(i = 0; i < topInput.width * topInput.height; i++)
	{
		output.pixels[topInput.width * topInput.height + i].r = bottomInput.pixels[i].r;
		output.pixels[topInput.width * topInput.height + i].g = bottomInput.pixels[i].g;
		output.pixels[topInput.width * topInput.height + i].b = bottomInput.pixels[i].b;
	}
}
void Blend(Image &input1, Image &input2, double factor, Image &output)
{
	output.width = input1.width;
	output.height = input1.height;
	output.pixels = (Pixel *)malloc(output.height * output.width * sizeof(Pixel));

	for(int i = 0; i < output.width*output.height; i++){
		(output.pixels)[i].r = (input1.pixels)[i].r * factor + (input2.pixels)[i].r * (1 - factor); 
		(output.pixels)[i].g = (input1.pixels)[i].g * factor + (input2.pixels)[i].g * (1 - factor); 
		(output.pixels)[i].b = (input1.pixels)[i].b * factor + (input2.pixels)[i].b * (1 - factor); 
	}
}
