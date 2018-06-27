#include <source.h>

class PNMreaderCPP : public Source
{
	private:
		char *filename;
	public:
		PNMreaderCPP(char *f){filename = (char *) malloc(strlen(f));strcpy(filename, f);}
		virtual void Execute();

};
