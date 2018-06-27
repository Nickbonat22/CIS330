#include <source.h>

class PNMreader : public Source
{
	private:
		char *filename;
	public:
		virtual void Update();
		PNMreader(char *f) {filename = (char *) malloc(strlen(f)+1);strcpy(filename, f);}
		virtual void Execute();
		virtual const char *SourceName();
};
