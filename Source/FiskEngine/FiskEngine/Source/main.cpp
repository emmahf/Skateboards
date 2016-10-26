#include <SFML/Graphics.hpp>
#include "engine.h"

int main()
{
	// Init engine
	Engine *engine = new Engine();

	if (engine->init() == false)
	{
		engine->fatalError("Error! Could not init engine!");
		return -1;
	}

	while (true)
	{
		engine->update();

		// TODO - Exit codes and stuff?
		if (engine->engineShouldShutDown())
			return -1;
	}

	return 0;
}