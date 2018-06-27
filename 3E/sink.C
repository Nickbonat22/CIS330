#include <sink.h>

Sink :: Sink()
{
    input1 = NULL;
    input2 = NULL;
}

void Sink :: SetInput(Image *input)
{
	input1 = input;
}

void Sink :: SetInput2(Image *input)
{
	input2 = input;
}

Sink :: ~Sink(void)
{
	;
}
