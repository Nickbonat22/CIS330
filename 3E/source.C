#include <source.h>

Image * 
Source :: GetOutput()
{
	return &output;
}

void Source :: Update()
{
    Execute();
}

Source :: ~Source(void)
{
	;
}
