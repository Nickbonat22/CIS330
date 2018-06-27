#include <source.h>

Image * Source :: GetOutput() {
	return &output;
}

void Source :: Update()
{
    char msg[128];
    sprintf(msg, "%s: start executing", SourceName());
    Logger::LogEvent(msg);
    Execute();
    sprintf(msg, "%s: finished executing", SourceName());
    Logger::LogEvent(msg);
}