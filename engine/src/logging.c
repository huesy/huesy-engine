#include "engine/logging.h"

EngineResult
logging_system_init(LoggingSystem *system, const LoggingSystemConfig *config)
{
	system->level = config->level;
	system->file = config->file;
	return ENGINE_SUCCESS;
}

void
logging_system_shutdown(LoggingSystem *system)
{
	system->level = LOG_LEVEL_INFO;
	system->file = NULL;
}
