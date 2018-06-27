#include <source.h>

class PNMreader : public Source
{
	private:
		char *filename;
	public:
		PNMreader(char *f) {filename = (char *) malloc(strlen(f));strcpy(filename, f);}
		virtual void Execute();

};
