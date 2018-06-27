#ifndef SINK_H
#define SINK_H

#include <image.h>
#include <string.h>

class Sink
{
	protected:
		const Image *input1;
		const Image *input2;
	public:
		Sink();
		void SetInput(Image *input1);
		void SetInput2(Image *input2);
		virtual const char *SinkName() = 0;
};

#endif
