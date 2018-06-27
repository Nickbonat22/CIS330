#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <filter.h>
#include <logging.h>

Filter::Filter(void)
{
    ;
}

const char *Filter :: SourceName()
{
    return FilterName();
}

const char *Filter :: SinkName()
{
    return FilterName();
}

void Filter :: Update()
{
    char msg[128];

    if(input1 != NULL)
    {
        char msg[128];
        sprintf(msg, "%s: about to update input1", SourceName());
        Logger::LogEvent(msg);
        input1->Update();
        sprintf(msg, "%s: done updating input1", SourceName());
        Logger::LogEvent(msg);
    }
    if(input2 != NULL)
    {
        char msg[128];
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
    else
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
    }// end else
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
    if(input1->GetHeight() != input2->GetHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: heights must match: %d, %d", SinkName(), input1->GetHeight(),input2->GetHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(input1->GetWidth() != input2->GetWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d", SinkName(), input1->GetWidth(),input2->GetWidth());
        DataFlowException e(SinkName(), msg);
        throw e;
    }

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
    if(input1->GetHeight() != input2->GetHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: heights must match: %d, %d", SinkName(), input1->GetHeight(),input2->GetHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(input1->GetWidth() != input2->GetWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d", SinkName(), input1->GetWidth(),input2->GetWidth());
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
    for(i = 0; i < input1->GetWidth() * input1->GetHeight(); i++)
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
    if(input1->GetHeight() != input2->GetHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: heights must match: %d, %d", SinkName(), input1->GetHeight(),input2->GetHeight());
        DataFlowException e(SinkName(), msg);
        throw e;
    }
    if(input1->GetWidth() != input2->GetWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: widths must match: %d, %d", SinkName(), input1->GetWidth(),input2->GetWidth());
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
    
    for(int i = 0; i < output.GetWidth()*output.GetHeight(); i++){
        output.GetPixels()[i].r = (input1->GetPixels())[i].r * factor + (input2->GetPixels())[i].r * (1 - factor);
        output.GetPixels()[i].g = (input1->GetPixels())[i].g * factor + (input2->GetPixels())[i].g * (1 - factor);
        output.GetPixels()[i].b = (input1->GetPixels())[i].b * factor + (input2->GetPixels())[i].b * (1 - factor);
    }
}
