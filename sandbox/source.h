#ifndef SOURCE_H
#define SOURCE_H

#include <image.h>
#include <logging.h>
#include <string.h>

class Source
{
	protected:
		Image  output;
		virtual void Execute() = 0;
	public:
		Source(){output.SetSource(this);}
		virtual Image * GetOutput();
		virtual void Update();
		virtual const char *SourceName() = 0;
};

#endif
