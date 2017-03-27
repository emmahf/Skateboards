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

	
	//Things that should be created by Game and moved out of engine (probably)
	
	m_debugTestMap = new NavGrid(7, 9, 40.0, MapShape_Rectangular);
	m_debugTestMap->computeDistanceField(Hex(3, 3));
	m_debugTestMap->setGoal(3, 3);
	m_debugEnemies = new Enemies(m_debugTestMap, 1);


	// Debug test file manager
	//m_debugTestMap->saveMapeToFile(std::string("NavGrid"));
	//m_debugTestMap->saveMapeToFile(std::string("NavGridTest"));
	//m_debugTestMap->loadMap(std::string("NavGridTest"));

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

	//Todo: This should not be here but in Game?

	// update
	m_debugEnemies->update();

	// draw
	m_debugTestMap->drawMap(rw, getDefaultFont());
	m_debugTestMap->setGoal(3,3);
	m_debugEnemies->draw(rw);


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

		sf::Vector2i localPosition = sf::Mouse::getPosition(*renderWindow());
		sf::Vector2u currentWindowSize = renderWindow()->getSize();
		sf::Vector2u originalWindowSize(640, 480); //Change to config setting

		sf::Vector2f scale( (float) currentWindowSize.x / (float) originalWindowSize.x, (float) currentWindowSize.y  / (float) originalWindowSize.y);
		localPosition.x = (int) round(localPosition.x / scale.x); //Really, there are no functions element mult for this?
		localPosition.y = (int)round(localPosition.y / scale.y);

		if (event.type == sf::Event::MouseButtonPressed) {


			//Update terrain
			if (event.mouseButton.button == sf::Mouse::Left) {

				//Todo: deal with input properly
				m_debugTestMap->debugMouseInput(localPosition);
			}

			//Set goal
			if (event.mouseButton.button == sf::Mouse::Right) {

				//Todo: deal with input properly
				m_debugTestMap->setGoal(localPosition);
				m_debugTestMap->computeDistanceField();
			}

			if (event.type == sf::Event::Resized)
			{
			}

		}

		//Re-initalize enemies with i
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::I)
			{
				m_debugEnemies->initEnemiesSingleBurst(100);
			}
			if (event.key.code == sf::Keyboard::S)
			{
				m_debugTestMap->saveMapeToFile("NavGridTest");
			}
			if (event.key.code == sf::Keyboard::L)
			{
				m_debugTestMap->loadMap("NavGridTest");
			}
		}


		Hex dh = m_debugTestMap->getHexFromPixelPosition(localPosition.x, localPosition.y);
		m_debugTestMap->dq = dh.x;
		m_debugTestMap->dr = dh.y;
	}

	return true;
}