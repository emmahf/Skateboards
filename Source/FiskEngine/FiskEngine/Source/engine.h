#pragma once
#include "config_manager.h"
#include "file_manager.h"
#include "NavGrid.h"
#include "Enemies.h" //Move out of engine! 
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

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

	// Todo: Move gui-stuff somwhere else

	void buildNavGridEditPandel(
		tgui::Gui &gui, 
		std::vector<std::string> maps,
		int placeX,
		int placeY,
		int sizeX,
		int sizeY) 
	{
		tgui::Panel::Ptr panel = tgui::Panel::create();
		panel->setSize(sizeX, sizeY);
		panel->setPosition(0, 0);

		int sizeTextBox = 21;
		
		//Todo: padding should be defined in a style config somewhere?
		int paddingLeft = 5;
		int paddingTop = 25;
		int paddingBottom = 5;
		int paddingBetween = 5;

		// GUI Stuff - should be moved away from here
		// A way of loading maps
		tgui::ComboBox::Ptr comboBox = tgui::ComboBox::create();
		comboBox->setSize(sizeX - paddingLeft*2, sizeTextBox);
		comboBox->setPosition(placeX + paddingLeft, placeY + paddingTop);
		for (auto file : maps)
		{
			comboBox->addItem(file);
		}
		comboBox->connect("ItemSelected", &NavGrid::loadMap, m_debugTestMap);

		tgui::Label::Ptr label = tgui::Label::create();
		label->setPosition(placeX + paddingLeft, comboBox->getPosition().y + sizeTextBox + paddingBetween);
		//label->setTextSize(18); 
		label->setText("SaveName");

		tgui::TextBox::Ptr textBox = tgui::TextBox::create();
		textBox->setSize(sizeX - paddingLeft*2, sizeTextBox);
		textBox->setPosition(placeX + paddingLeft, label->getPosition().y + sizeTextBox + paddingBetween);
		textBox->setText("NavGridName");
		textBox->setTextSize(16);


		panel->add(comboBox);
		panel->add(label);
		panel->add(textBox, "navGridNameInput");


		gui.add(panel, "EditNavgridPanel");
	}

	ConfigManager *m_configManager;
	FileManager *m_fileManager;
	sf::RenderWindow *m_renderWindow;
	tgui::Gui * m_gui;

	NavGrid *m_debugTestMap;
	sf::Font *m_debugFont;
	Enemies *m_debugEnemies;

	bool m_quitRequested;
};