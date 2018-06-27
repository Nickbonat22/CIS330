#ifndef SINK_H
#define SINK_H

#include <image.h>
#include <string.h>

class Sink
{
	protected:
		const Image *input1, *input2;
	public:
		void SetInput(Image *input1);
		void SetInput2(Image *input2);
		virtual const char *SinkName() = 0;
		Sink();
};

#endif
