#ifndef SOURCE_H
#define SOURCE_H

#include <image.h>
#include <string.h>

class Source
{
	protected:
		Image  output;
		virtual void Execute() = 0;
	public:
		virtual void Update() = 0;
		Image * GetOutput();
		Source(){output.SetSource(this);}
};

#endif
