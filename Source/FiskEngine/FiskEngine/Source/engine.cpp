#include "engine.h"
#define THEME_CONFIG_FILE "../../widgets/Black.conf"

//TODO: Use the config stuff
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

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
	m_renderWindow = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Fisk Engine");

	m_gui = new tgui::Gui(*m_renderWindow);


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
	
	m_debugTestMap = new NavGrid(6, 7, 40.0, WINDOW_WIDTH/5, 50 , MapShape_Rectangular);
	m_debugTestMap->computeDistanceField(Hex(3, 3));
	m_debugTestMap->setGoal(3, 3);
	NavGrid::loadAvailableNavgrids();
	m_debugEnemies = new Enemies(m_debugTestMap, 1);
	

	buildNavGridEditPandel(*m_gui, m_debugTestMap->m_availableNavgrids, 0, 0, WINDOW_WIDTH/5, WINDOW_HEIGHT);
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


	m_gui->draw();
	renderWindow()->draw(text);
	renderWindow()->display();
}

bool Engine::pollEvents()
{
	sf::Event event;


	while (renderWindow()->pollEvent(event))
	{
		m_gui->handleEvent(event);

		if (event.type == sf::Event::Closed)
		{
			renderWindow()->close();
			shutDownEngine();
			return false;
		}

		sf::Vector2i localPosition = sf::Mouse::getPosition(*renderWindow());
		sf::Vector2u currentWindowSize = renderWindow()->getSize();
		sf::Vector2u originalWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); //Change to config setting

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
			if (event.key.code == sf::Keyboard::F1)
			{
				m_debugTestMap->saveMapeToFile(m_gui->get<tgui::TextBox>("navGridNameInput")->getText());
			}

		}
		Hex dh = m_debugTestMap->getHexFromPixelPosition(localPosition.x, localPosition.y);
		m_debugTestMap->dq = dh.x;
		m_debugTestMap->dr = dh.y;
	}



	
	return true;
}