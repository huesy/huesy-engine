#include "engine/application.h"

EngineResult
application_create(Application *application)
{
	application->engine = 0;

	return ENGINE_SUCCESS;
}

void
application_destroy(Application *application)
{
}
