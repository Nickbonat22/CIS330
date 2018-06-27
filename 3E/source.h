#ifndef SOURCE_H
#define SOURCE_H

#include <image.h>
#include <string.h>

class Source
{
	protected:
		Image  output;
	public:
        Source(){output.SetSource(this);}
        Image * GetOutput();
		virtual ~Source(void);
		virtual void Execute() = 0;
    	virtual void Update();
};

#endif
