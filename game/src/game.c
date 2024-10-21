#include <engine/engine.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
	if (engine_init() != 0) {
		printf("Failed to initialize engine\n");
		return 1;
	}

	return 0;
}
