
#pragma once
#include <TGUI/TGUI.hpp>
#include "NavGrid.h"


using loadMapPtr = bool(NavGrid::*)(std::string);
using saveMapPtr = bool(NavGrid::*)(std::string);

// Todo: This should be moved out into the game
class Gui 
{

public:

	Gui(sf::RenderWindow * renderWindow, int windowWidth, int windowHeight) :
		m_rw(renderWindow),
		m_windowWidth(windowWidth),
		m_windowHeight(windowHeight)
	{
		m_gui = new tgui::Gui(*renderWindow);
			
	};

	~Gui() {};

	void init(NavGrid *grid)
	{
		buildNavGridEditPandel(
			grid->m_availableNavgrids,
			&NavGrid::loadMap,
			grid,
			&NavGrid::saveMapeToFile,
			0,
			0,
			m_windowWidth / 5,
			m_windowHeight);
	}

	void handleEvent(sf::Event e)
	{
		m_gui->handleEvent(e);
	}

	void draw()
	{
		m_gui->draw();
	}

private:


	sf::RenderWindow *m_rw;
	int m_windowWidth, m_windowHeight;

	tgui::Gui * m_gui;

	static void updateSaveName(std::string name)
	{
		m_saveFileName = name;
	}

	static bool saveMapWrapperFunction(NavGrid* grid, saveMapPtr saveFunction)
	{
		return (grid->*saveFunction)(m_saveFileName);
	}

	static std::string m_saveFileName;


	void buildNavGridEditPandel(
		std::vector<std::string> maps,
		loadMapPtr loadMapFunction,
		NavGrid *grid,
		saveMapPtr saveMapFunction,
		int placeX,
		int placeY,
		int sizeX,
		int sizeY);
};