#include <source.h>

class PNMreader : public Source
{
	private:
		char *filename;
	public:
		PNMreader();
		~PNMreader();
		PNMreader(char *f);
		virtual void Execute();
};
