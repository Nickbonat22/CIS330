#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <filter.h>
#include <logging.h>

const char *Filter :: SourceName()
{
    return FilterName();
}

const char *Filter :: SinkName()
{
    return FilterName();
}

// global variable
int count = 0;

void Filter :: Update()
{
    char msg[128];
    count ++;
    int stack = 1000;
    
    if(count > stack)
    {
        sprintf(msg, "%s: An error has occurred!", SourceName());
        Logger::LogEvent(msg);
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    if(input1 != NULL)
    {
        sprintf(msg, "%s: about to update input1", SourceName());
        Logger::LogEvent(msg);
        input1->Update();
        sprintf(msg, "%s: done updating input1", SourceName());
        Logger::LogEvent(msg);
    }
    if(input2 != NULL)
    {
        sprintf(msg, "%s: about to update input2", SourceName());
        Logger::LogEvent(msg);
        input2->Update();
        sprintf(msg, "%s: done updating input2", SourceName());
        Logger::LogEvent(msg);
    }

    sprintf(msg, "%s: about to execute", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: done executing", SourceName());
    Logger::LogEvent(msg);
}

void Shrinker :: Execute()
{
    if(input1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    int i, j;

    output.ResetSize((input1->GetHeight())/2, (input1->GetWidth())/2,output.GetMaxval());
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
    if(input1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(input2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(!(input1->GetHeight() == input2->GetHeight()))
    {
        char msg[1024];
        sprintf(msg, "%s: heights must match: %d, %d", SinkName(), input1->GetHeight(), input2->GetHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    int i,j;

    output.ResetSize(input1->GetHeight(), input1->GetWidth() + input2->GetWidth(), output.GetMaxval());
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

void TBCombine :: Execute()
{
    if(input1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(input2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(!(input1->GetWidth() == input2->GetWidth()))
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d", SinkName(), input1->GetWidth(), input2->GetWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
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

void Blender :: Execute()
{
    if(input1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(input2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(!(input1->GetHeight() == input2->GetHeight()))
    {
        char msg[1024];
        sprintf(msg, "%s: heights must match: %d, %d", SinkName(), input1->GetHeight(), input2->GetHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(!(input1->GetWidth() == input2->GetWidth()))
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d", SinkName(), input1->GetWidth(), input2->GetWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    if(factor < 0.0 or factor > 1.0)
    {
        char msg[1024];
        sprintf(msg, "Invalid factor for Blender: %f", factor);
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    output.ResetSize(input1->GetHeight(), input2->GetWidth(), output.GetMaxval());
    output.CreatePixels();
    
    for(int i = 0; i < output.GetWidth() * output.GetHeight(); i++){
        output.GetPixels()[i].r = (input1->GetPixels())[i].r * factor + (input2->GetPixels())[i].r * (1 - factor);
        output.GetPixels()[i].g = (input1->GetPixels())[i].g * factor + (input2->GetPixels())[i].g * (1 - factor);
        output.GetPixels()[i].b = (input1->GetPixels())[i].b * factor + (input2->GetPixels())[i].b * (1 - factor);
    }
}

void Mirror :: Execute()
{
    if(input1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    int i, j;

    output.ResetSize(input1->GetHeight(), input1->GetWidth(), output.GetMaxval());
    output.CreatePixels();

    for(i = 0; i < output.GetHeight(); i++)
    {
        for(j = 0; j < output.GetWidth(); j++)
        {
            output.GetPixels()[i * output.GetWidth() + j] = input1->GetPixels()[i * output.GetWidth() + (output.GetWidth() - 1 - j)];
        }
    }
}

void Rotate :: Execute()
{
    if(input1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    int i, j;

    output.ResetSize(input1->GetWidth(), input1->GetHeight(), output.GetMaxval());
    output.CreatePixels();

    for(i = 0; i < output.GetHeight(); i++)
    {
        for(j= 0; j < output.GetWidth(); j++)
        {
            output.GetPixels()[i * output.GetWidth() + j] = input1->GetPixels()[(output.GetWidth() - 1 - j) * output.GetHeight() + i];
        }
    }
}

void Subtract :: Execute()
{
    if(input1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(input2 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input2!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    
    if(!(input1->GetHeight() == input2->GetHeight()))
    {
        char msg[1024];
        sprintf(msg, "%s: heights must match: %d, %d", SinkName(), input1->GetHeight(), input2->GetHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(!(input1->GetWidth() == input2->GetWidth()))
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d", SinkName(), input1->GetWidth(), input2->GetWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    int i, j;

    output.ResetSize(input1->GetHeight(), input1->GetWidth(), output.GetMaxval());
    output.CreatePixels();

    for(i = 0; i < output.GetWidth(); i++)
    {
        for(j = 0; j < output.GetHeight(); j++)
        {
            if(input1->GetPixels()[j * input1->GetWidth() + i].r > input2->GetPixels()[j * input2->GetWidth() + i].r)
            {
                output.GetPixels()[j * output.GetWidth() + i].r = input1->GetPixels()[j * input1->GetWidth() + i].r - input2->GetPixels()[j * input1->GetWidth() + i].r;
            }
            else {
                output.GetPixels()[j * output.GetWidth() + i].r = 0;
            }
            if(input1->GetPixels()[j * input1->GetWidth() + i].g > input2->GetPixels()[j * input2->GetWidth() + i].g)
            {
                output.GetPixels()[j * output.GetWidth() + i].g = input1->GetPixels()[j * input1->GetWidth() + i].g - input2->GetPixels()[j * input1->GetWidth() + i].g;
            }
            else {
                output.GetPixels()[j * output.GetWidth() + i].g = 0;
            }
            if(input1->GetPixels()[j * input1->GetWidth() + i].b > input2->GetPixels()[j * input2->GetWidth() + i].b)
            {
                output.GetPixels()[j * output.GetWidth() + i].b = input1->GetPixels()[j * input1->GetWidth() + i].b - input2->GetPixels()[j * input1->GetWidth() + i].b;
            }
            else {
                output.GetPixels()[j * output.GetWidth() + i].b = 0;
            }
        }
    }
}

void Grayscale :: Execute()
{
    if(input1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    int i;

    output.ResetSize(input1->GetHeight(), input1->GetWidth(), output.GetMaxval());
    output.CreatePixels();

    for(i = 0; i < output.GetHeight() * output.GetWidth(); i++)
    {
        output.GetPixels()[i].r = (unsigned char) (input1->GetPixels()[i].r / 5 + input1->GetPixels()[i].g / 2 + input1->GetPixels()[i].b / 4);
        output.GetPixels()[i].g = (unsigned char) (input1->GetPixels()[i].r / 5 + input1->GetPixels()[i].g / 2 + input1->GetPixels()[i].b / 4);
        output.GetPixels()[i].b = (unsigned char) (input1->GetPixels()[i].r / 5 + input1->GetPixels()[i].g / 2 + input1->GetPixels()[i].b / 4);
    }
}

void Blur :: Execute()
{
    if(input1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    int i, j;

    output.ResetSize(input1->GetHeight(), input1->GetWidth(), output.GetMaxval());
    output.CreatePixels();

    for(i = 0; i < output.GetHeight(); i++)
    {
        for(j = 0; j < output.GetWidth(); j++)
        {
            if(i == 0 || i == (output.GetHeight() - 1) || j == 0 || j == (output.GetWidth() - 1))
            {
                output.GetPixels()[i * output.GetWidth() + j] = input1->GetPixels()[i * output.GetWidth() + j];
            }
            else
            {
                output.GetPixels()[i*output.GetWidth()+j].r = input1->GetPixels()[(i-1) * output.GetWidth()+j-1].r / 8 + input1->GetPixels()[(i-1)*output.GetWidth()+j].r / 8 + input1->GetPixels()[(i-1)*output.GetWidth()+j+1].r / 8 + 
                input1->GetPixels()[i*output.GetWidth()+j-1].r / 8 + input1->GetPixels()[i*output.GetWidth()+j+1].r / 8 + input1->GetPixels()[(i+1)*output.GetWidth()+j-1].r / 8 + input1->GetPixels()[(i+1)*output.GetWidth()+j].r / 8 + 
                input1->GetPixels()[(i+1) * output.GetWidth()+j+1].r / 8;

                output.GetPixels()[i*output.GetWidth()+j].g =  input1->GetPixels()[(i-1)*output.GetWidth()+j-1].g/8 + input1->GetPixels()[(i-1)*output.GetWidth()+j].g / 8 + input1->GetPixels()[(i-1)*output.GetWidth()+j+1].g / 8 + 
                input1->GetPixels()[i*output.GetWidth()+j-1].g / 8 + input1->GetPixels()[i*output.GetWidth()+j+1].g/8 + input1->GetPixels()[(i+1)*output.GetWidth()+j-1].g / 8 + input1->GetPixels()[(i+1)*output.GetWidth()+j].g / 8 + 
                input1->GetPixels()[(i+1)*output.GetWidth()+j+1].g / 8;

                output.GetPixels()[i*output.GetWidth()+j].b =  input1->GetPixels()[(i-1) * output.GetWidth()+j-1].b / 8 + input1->GetPixels()[(i-1)*output.GetWidth()+j].b/8 + input1->GetPixels()[(i-1)*output.GetWidth()+j+1].b / 8 + 
                input1->GetPixels()[i*output.GetWidth()+j-1].b / 8 + input1->GetPixels()[i*output.GetWidth()+j+1].b / 8 + input1->GetPixels()[(i+1)*output.GetWidth()+j-1].b/8 + input1->GetPixels()[(i+1)*output.GetWidth()+j].b / 8 + 
                input1->GetPixels()[(i+1)*output.GetWidth()+j+1].b / 8;
            }
        }
    }
}

Color :: Color(int w, int h, unsigned char r, unsigned char g, unsigned char b)
{
    width = w;
    height = h;
    red = r;
    green = g;
    blue = b;
}

void Color :: Execute()
{

    if (red > 255 || red < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: must be 0-255!", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    if (green > 255 || green < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: must be 0-255!", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    if (blue > 255 || blue < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: must be 0-255!", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }

    if(height < 1)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid height: %d", SourceName(), height);
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    if(width < 1)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid width: %d", SourceName(), width);
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    
    int i;

    output.ResetSize(height, width, output.GetMaxval());
    output.CreatePixels();

    for(i = 0; i < height * width; i++)
    {
        output.GetPixels()[i].r = red;
        output.GetPixels()[i].g = green;
        output.GetPixels()[i].b = blue;
    }
}

void CheckSum :: OutputCheckSum(const char *filename)
{   
    if(input1 == NULL)
    {
        char msg[1024];
        sprintf(msg, "%s: no input1!", SinkName());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

    int i;
    FILE *f_in;
    f_in = fopen(filename, "w");

    unsigned char red = 0;
    unsigned char green = 0;
    unsigned char blue = 0;

    for(i = 0; i < input1->GetHeight() * input1->GetWidth(); i++)
    {
        red += input1->GetPixels()[i].r;
        green += input1->GetPixels()[i].g;
        blue += input1->GetPixels()[i].b;
    }

    fprintf(f_in, "CHECKSUM: %d, %d, %d\n", red, green, blue);
    fclose(f_in);
}
