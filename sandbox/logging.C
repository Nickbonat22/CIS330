#include <logging.h>

DataFlowException :: DataFlowException(const char *type, const char *error)
{
	sprintf(msg, "Throwing exception: (%s), %s", type, error);
    Logger::LogEvent(msg);
}

FILE *Logger::logger = NULL;

void Logger :: LogEvent(const char *event)
{
	if(Logger::logger == NULL)
	{
		Logger::logger=fopen("logger", "w");
	}
	fprintf(Logger::logger, "%s\n", event);
}

void Logger :: Finalize()
{
	fclose(logger);
	logger = NULL;
}
