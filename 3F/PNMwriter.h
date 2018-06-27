#include <sink.h>

class PNMwriter : public Sink
{
	public:
		void Write(char *filename);
		virtual const char *SinkName();
};
