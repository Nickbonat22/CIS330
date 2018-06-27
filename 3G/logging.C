#include <logging.h>

FILE *Logger::logger = NULL;

DataFlowException :: DataFlowException(const char *type, const char *error)
{
	sprintf(msg, "Throwing exception: (%s), %s", type, error);
    Logger::LogEvent(msg);
}

void Logger :: LogEvent(const char *event)
{
	if(Logger::logger == NULL)
	{
		// creating my own logger to compare
		Logger::logger=fopen("logger", "w");
	}
	fprintf(Logger::logger, "%s\n", event);
}

void Logger :: Finalize()
{
	fclose(logger);
}