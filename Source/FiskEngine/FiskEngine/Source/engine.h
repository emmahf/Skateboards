#pragma once
#include "config_manager.h"
#include "file_manager.h"
#include "hexMap.h"
#include "Enemies.h" //Move out of engine! 
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
	sf::Font *getDefaultFont() { return m_debugFont; }

private:
	ConfigManager *m_configManager;
	FileManager *m_fileManager;

	NavGrid *m_debugTestMap;
	sf::RenderWindow *m_renderWindow;
	sf::Font *m_debugFont;
	Enemies *m_debugEnemies;

	bool m_quitRequested;
};