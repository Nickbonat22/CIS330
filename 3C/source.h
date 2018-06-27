#ifndef SOURCE_H
#define SOURCE_H

#include <image.h>
#include <string.h>

class Source
{
	protected:
		Image  output;
	public:
		virtual void Execute() = 0;
		Image * GetOutput();
};

#endif
