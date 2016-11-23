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
	m_debugTestMap = new HexMap(7, 9, 40.0, MapShape_Rectangular);

	m_configManager->addConfigSetting("test_string", "string");
	m_configManager->addConfigSetting("test_bool", "true");
	m_configManager->addConfigSetting("test_int", "5");
	m_configManager->addConfigSetting("test_float", "10.9");

	// We need a default (and fallback) font
	m_debugFont = new sf::Font();

	// TODO - Use the file manager to load it properly instead of using this temporary path!
	if (m_debugFont->loadFromFile("..\\..\\..\\Game\\fonts\\debugfont.ttf") == false)
	{	
		fatalError("Error! Could not load default debug font!");
		return false;
	}

	return true;
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

	sf::Text text;
	text.setFont(*getDefaultFont());

	text.setString("Hexes man!");
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	sf::RenderWindow* rw = renderWindow();
	rw->clear();

	m_debugTestMap->drawMap(rw, getDefaultFont());


	renderWindow()->draw(text);
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
		
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {

				//Todo: deal with input properly
				sf::Vector2i localPosition = sf::Mouse::getPosition(*renderWindow());
				m_debugTestMap->debugMouseInput(localPosition);
			}
		}
	}

	return true;
}