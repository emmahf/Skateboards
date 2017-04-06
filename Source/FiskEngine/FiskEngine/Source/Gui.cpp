#include "Gui.h"
#include <SFML/Graphics.hpp>

// Init static state

std::string Gui::m_saveFileName = "";

// Build panels
void Gui::buildNavGridEditPandel(
	std::vector<std::string> maps,
	loadMapPtr loadMapFunction,
	NavGrid *grid,
	saveMapPtr saveMapFunction,
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
	comboBox->setSize(sizeX - paddingLeft * 2, sizeTextBox);
	comboBox->setPosition(placeX + paddingLeft, placeY + paddingTop);
	for (auto file : maps)
	{
		comboBox->addItem(file);
	}
	comboBox->connect("ItemSelected", loadMapFunction, grid);

	tgui::Label::Ptr label = tgui::Label::create();
	label->setPosition(placeX + paddingLeft, comboBox->getPosition().y + sizeTextBox + paddingBetween);
	//label->setTextSize(18); 
	label->setText("SaveName");

	tgui::TextBox::Ptr textBox = tgui::TextBox::create();
	textBox->setSize(sizeX - paddingLeft * 2, sizeTextBox);
	textBox->setPosition(placeX + paddingLeft, label->getPosition().y + sizeTextBox + paddingBetween);
	textBox->setText("NavGridName");
	m_saveFileName = ("NavGridName");
	textBox->setTextSize(16);
	textBox->connect("TextChanged", &Gui::updateSaveName);
	
	panel->add(comboBox);
	panel->add(label);
	panel->add(textBox, "navGridNameInput");



	tgui::Button::Ptr saveButton = tgui::Button::create();
	saveButton->connect("pressed", &Gui::saveMapWrapperFunction, grid, saveMapFunction); //, saveMapFunction);


	saveButton->setSize(sizeX - paddingLeft * 2, sizeTextBox);
	saveButton->setPosition(placeX + paddingLeft, textBox->getPosition().y + sizeTextBox + paddingBetween);
	saveButton->setText("Save Map");
	saveButton->setTextSize(16);


	panel->add(saveButton);


	m_gui->add(panel, "EditNavgridPanel");
};