#include <sink.h>
#include <image.h>

class PNMwriter : public Sink
{
	public:
		void Write(char *filename);
		virtual const char *SinkName(){return "PNMwriter";}
};
