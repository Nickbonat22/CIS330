#ifndef SINK_H
#define SINK_H

#include <image.h>
#include <string.h>

class Sink
{
	protected:
		Image *input1, *input2;
	public:
        Sink();
		virtual ~Sink(void);
		void SetInput(Image *input1);
		void SetInput2(Image *input2);
};

#endif
