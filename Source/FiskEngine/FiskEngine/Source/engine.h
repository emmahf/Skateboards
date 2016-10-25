#pragma once
#include "config_manager.h"
#include "file_manager.h"
#include <SFML/Graphics.hpp>

class Engine
{
public:
	Engine();
	~Engine();

	bool init();
	void update();

	ConfigManager *getConfigManager();
	FileManager *getFileManager();
	void fatalError(const char *errorMessage);
	bool engineShouldShutDown() { return m_quitRequested; }
	sf::RenderWindow *renderWindow() { return m_renderWindow; }
	bool pollEvents();
	void shutDownEngine() { m_quitRequested = true; }

private:
	ConfigManager *m_configManager;
	FileManager *m_fileManager;
	sf::RenderWindow *m_renderWindow;

	bool m_quitRequested;
};