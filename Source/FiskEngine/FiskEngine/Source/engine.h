#pragma once
#include "config_manager.h"
#include "file_manager.h"
#include "Gui.h"
#include "NavGrid.h"
#include "Enemies.h" //Move out of engine! 
#include <SFML/Graphics.hpp>


//TODO: Use the config stuff
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

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

	std::string * getCurrentText(tgui::Panel::Ptr * panel)
	{
		return  & ( std::string((*panel)->get<tgui::TextBox>("navGridNameInput")->getText() ));
	}

	ConfigManager *m_configManager;
	FileManager *m_fileManager;
	sf::RenderWindow *m_renderWindow;
	Gui * m_gui;

	NavGrid *m_debugTestMap;
	sf::Font *m_debugFont;
	Enemies *m_debugEnemies;

	bool m_quitRequested;
};