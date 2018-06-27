#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <filter.h>

Filter::Filter(void)
{
    ;
}

void Filter :: Update()
{
	if(input1 != NULL)
	{
		input1->Update();
    	Execute();
	}
    
    if(input2 != NULL)
	{
		input2->Update();
    	Execute();
	}
}

void Shrinker :: Execute()
{
    int i, j;

    output.ResetSize((input1->GetHeight() + 1)/2, (input1->GetWidth() + 1)/2,output.GetMaxval());
    output.CreatePixels();
    
    for(i = 0; i < output.GetHeight(); i++)
    {
        for(j = 0; j < output.GetWidth(); j++)
        {
            output.GetPixels()[i * output.GetWidth() + j] = input1->GetPixels()[(2 * i * input1->GetWidth()) + (j * 2)];
        }
    }
}

void LRCombine :: Execute()
{
    int i,j;

    output.ResetSize(input1->GetHeight(), input1->GetWidth() + input2->GetWidth(),output.GetMaxval());
    output.CreatePixels();
    
    for(int i = 0; i < output.GetHeight(); i++)
    {
        Pixel *left = input1->GetPixels() + i * input1->GetWidth();
        Pixel *right = input2->GetPixels() + i * input2->GetWidth();
        Pixel *pixwidth = output.GetPixels() + i * output.GetWidth();
        
        memcpy(pixwidth, left, input1->GetWidth() * sizeof(Pixel));
        memcpy(pixwidth + input1->GetWidth(), right, input2->GetWidth() * sizeof(Pixel));
        
    }
}

void TBCombine :: Execute()
{
    
    int i;

    output.ResetSize(input1->GetHeight() + input2->GetHeight(), input1->GetWidth(),output.GetMaxval());
    output.CreatePixels();
    
    for(i = 0; i < input1->GetWidth() * input1->GetHeight(); i++)
    {
        output.GetPixels()[i].r = input1->GetPixels()[i].r;
        output.GetPixels()[i].g = input1->GetPixels()[i].g;
        output.GetPixels()[i].b = input1->GetPixels()[i].b;
    }
    for(i = 0; i < input1->GetWidth() * input1->GetHeight(); i++)
    {
        output.GetPixels()[input1->GetWidth() * input1->GetHeight() + i].r = input2->GetPixels()[i].r;
        output.GetPixels()[input1->GetWidth() * input1->GetHeight() + i].g = input2->GetPixels()[i].g;
        output.GetPixels()[input1->GetWidth() * input1->GetHeight() + i].b = input2->GetPixels()[i].b;
    }
    
}

void Blender :: Execute()
{
    output.ResetSize(input1->GetHeight(), input2->GetWidth(), output.GetMaxval());
    output.CreatePixels();
    
    for(int i = 0; i < output.GetWidth()*output.GetHeight(); i++){
        output.GetPixels()[i].r = (input1->GetPixels())[i].r * factor + (input2->GetPixels())[i].r * (1 - factor);
        output.GetPixels()[i].g = (input1->GetPixels())[i].g * factor + (input2->GetPixels())[i].g * (1 - factor);
        output.GetPixels()[i].b = (input1->GetPixels())[i].b * factor + (input2->GetPixels())[i].b * (1 - factor);
    }
}
