#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <filter.h>

Filter::Filter(void)
{
    ;
}

Filter :: ~Filter(void)
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

Shrinker :: ~Shrinker(void)
{
    ;
}

void LRCombine :: Execute()
{
    int i,j;

    output.ResetSize(input1->GetHeight(), input1->GetWidth() + input2->GetWidth(),output.GetMaxval());
    output.CreatePixels();
    
    for(i = 0; i < input1->GetWidth() + input2->GetWidth(); i++)
    {
        for(j = 0; j < input1->GetHeight(); j++)
        {
            if(i < input1->GetWidth())
            {
                output.GetPixels()[j * (input1->GetWidth() + input2->GetWidth()) + i].r = input1->GetPixels()[j * input1->GetWidth() + i].r;
                output.GetPixels()[j * (input1->GetWidth() + input2->GetWidth()) + i].g = input1->GetPixels()[j * input1->GetWidth() + i].g;
                output.GetPixels()[j * (input1->GetWidth() + input2->GetWidth()) + i].b = input1->GetPixels()[j * input1->GetWidth() + i].b;
            }
            else{
                output.GetPixels()[j * (input1->GetWidth() + input2->GetWidth()) + i].r = input2->GetPixels()[j * input2->GetWidth() + (i - input1->GetWidth())].r;
                output.GetPixels()[j * (input1->GetWidth() + input2->GetWidth()) + i].g = input2->GetPixels()[j * input2->GetWidth() + (i - input1->GetWidth())].g;
                output.GetPixels()[j * (input1->GetWidth() + input2->GetWidth()) + i].b = input2->GetPixels()[j * input2->GetWidth() + (i - input1->GetWidth())].b;
            }
        }
    }
}

LRCombine :: ~LRCombine(void)
{
    ;
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
    for(i = 0; i < input2->GetWidth() * input2->GetHeight(); i++)
    {
        output.GetPixels()[input1->GetWidth() * input1->GetHeight() + i].r = input2->GetPixels()[i].r;
        output.GetPixels()[input1->GetWidth() * input1->GetHeight() + i].g = input2->GetPixels()[i].g;
        output.GetPixels()[input1->GetWidth() * input1->GetHeight() + i].b = input2->GetPixels()[i].b;
    }
    
}

TBCombine :: ~TBCombine(void)
{
    ;
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

Blender :: ~Blender(void)
{
    ;
}
