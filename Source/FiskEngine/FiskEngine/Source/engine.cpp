#include "engine.h"

Engine::Engine()
{
	m_quitRequested = false;
}

Engine::~Engine()
{
	// TODO - Clear memory and stuff?
}

// Initalise whole engine
bool Engine::init()
{
	m_fileManager = new FileManager();
	m_configManager = new ConfigManager();
	m_renderWindow = new sf::RenderWindow(sf::VideoMode(640, 480), "Fisk Engine");

	return false;
}

// Unrecoverable error that will shut down the whole game
void Engine::fatalError(const char *errorMessage)
{
	// TODO - A big, huge error here - For now, just cause a breakpoint
	__debugbreak();
	m_quitRequested = false;
}

ConfigManager *Engine::getConfigManager()
{
	if (!m_configManager)
	{
		fatalError("Fatal error! Could not get Config Manager!");
		return nullptr;
	}

	return m_configManager;
}

FileManager *Engine::getFileManager()
{
	if (!m_fileManager)
	{
		fatalError("Fatal error! Could not get File Manager!");
		return nullptr;
	}

	return m_fileManager;
}

void Engine::update()
{
	if (pollEvents() == false)
		return;

	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	renderWindow()->clear();
	renderWindow()->draw(shape);
	renderWindow()->display();
}

bool Engine::pollEvents()
{
	sf::Event event;
	while (renderWindow()->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			renderWindow()->close();
			shutDownEngine();
			return false;
		}
	}

	return true;
}