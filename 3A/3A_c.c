#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	unsigned char r, g, b;

} Pixel;

typedef struct
{
	Pixel *pixels;
	int width, height, maxval;

} Image;

Image *
ReadImage(char *filename)
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

 	Image *pnm = malloc(sizeof(Image));

 	// setting the width, height, and maxval from file to struct
 	pnm->width = width;
 	pnm->height = height;
 	pnm->maxval = maxval;

 	pnm->pixels = malloc(width * height * sizeof(Pixel));
 	fread(pnm->pixels, sizeof(Pixel), height*width, f_in);
 	fclose(f_in);

 	return pnm;
}


void WriteImage(Image *img, char *filename)
{
	FILE *f_out;
	f_out = fopen(filename, "w");
	if (f_out == NULL)
	{
		fprintf(stderr,"Unable to open the file!\nExiting\n");
		exit(EXIT_FAILURE);
	}

    fprintf(f_out, "P6\n%d %d\n%d\n", img->width, img->height, img->maxval);
	fwrite(img->pixels, sizeof(Pixel), img->height * img->width , f_out);
	fclose(f_out);

}

Image *
YellowDiagonal(Image *input)
{
	if(input == NULL)
	{
		fprintf(stderr,"NULL pointer\nExiting\n");
		exit(EXIT_FAILURE);
	}
	// copy input image using memcpy
	Image *new_pnm = malloc(sizeof(Image));
	new_pnm->pixels = malloc(input->width * input->height * sizeof(Pixel));
	memcpy(new_pnm->pixels, input->pixels, input->width * input->height * sizeof(Pixel));

	// set values from input to the new image
	new_pnm->width = input->width;
 	new_pnm->height = input->height;
 	new_pnm->maxval = input->maxval;

	int i, j;
	for(i = 0; i < new_pnm->width; i++)
	{
		for(j = 0; j < new_pnm->height; j++)
		{
			if (i == j)
			{
				new_pnm->pixels[i * new_pnm->width + j].r = new_pnm->maxval;
				new_pnm->pixels[i * new_pnm->width + j].g = new_pnm->maxval;
				new_pnm->pixels[i * new_pnm->width + j].b = 0;
			}
		}
	}
	return new_pnm;
}

int main(int argc, char *argv[])
{
	if (argc != 3)
	{
		fprintf(stderr, "Incorrect input\nExiting\n");
		exit(EXIT_FAILURE);
	}

	Image *pnm;
	pnm = ReadImage(argv[1]);

	Image *new_pnm;
	new_pnm = YellowDiagonal(pnm);

	free(pnm->pixels);
	free(pnm);

	WriteImage(new_pnm, argv[2]);

	free(new_pnm->pixels);
	free(new_pnm);

	return 0;
}
