//File Written by Samuel Amantea-Collins
#include "stdafx.h"
#include "GuiLoader.h"
#include "Game.h"

//This is a standard TGUI config, but in theory, it could be replaced with completely custom graphics for all gui elements
const std::string GuiLoader::GUI_CONFIG = "Gui/Black.conf";
tgui::ChildWindow::Ptr GuiLoader::overlay;
int GuiLoader::previousScrolbarValue = 0;

void GuiLoader::LoadMainMenuGui(tgui::Gui& gui, const vector<string>& levelNames)
{
	tgui::Label::Ptr selectLevelLabel(gui);
	selectLevelLabel->setText("Please select a level:");
	selectLevelLabel->setTextSize(44);
	selectLevelLabel->setPosition((gui.getWindow()->getSize().x / 2.f) - (selectLevelLabel->getSize().x / 2.f),
		(gui.getWindow()->getSize().y / 15.f));
	selectLevelLabel->setTextColor(sf::Color::Cyan);

	tgui::Button::Ptr settingsButton(gui);
	settingsButton->load(GUI_CONFIG);
	settingsButton->setSize(100, 40);
	settingsButton->setPosition(gui.getWindow()->getSize().x - 100.f, 0);
	settingsButton->setText("Settings");
	settingsButton->setTextColor(sf::Color::White);
	settingsButton->setTextSize(24);
	settingsButton->setTransparency(125);
	settingsButton->bindCallback(std::bind(GuiLoader::LoadSettingsOverlay, std::ref(gui)), tgui::Button::LeftMouseClicked);

	// Create the panel(gui.getWindow()->getSize().x / 2.f) - 100.f, (gui.getWindow()->getSize().y / 6.f) + yOffset
	tgui::Panel::Ptr panel(gui);
	panel->setPosition((gui.getWindow()->getSize().x / 2.f) - 100.f, (gui.getWindow()->getSize().y / 6.f));
	panel->setSize(200, gui.getWindow()->getSize().y - panel->getPosition().y);
	panel->setTransparency(255);

	tgui::Scrollbar::Ptr scrollbar(gui);
	scrollbar->load(GUI_CONFIG);
	scrollbar->setSize(15, gui.getWindow()->getSize().y - panel->getPosition().y);
	scrollbar->setPosition(panel->getPosition() + sf::Vector2f(panel->getSize().x, 0));
	scrollbar->setArrowScrollAmount(30);
	scrollbar->setLowValue(360); // Viewable area (height of the panel)
	scrollbar->setMaximum((levelNames.size()-1) * 105); // Total area (height of the 5 images)

	// Call the scrollPanel function that we defined above when scrolling
	scrollbar->bindCallbackEx(std::bind(ScrollBarMoved, panel, std::placeholders::_1), tgui::Scrollbar::ValueChanged);
	previousScrolbarValue = 0;

	int yOffset = 0;
	int offsetInc = 105;

	for (int i = 0; i < levelNames.size(); ++i)
	{
		tgui::Button::Ptr l1(*panel);
		l1->load(GUI_CONFIG);
		l1->setSize(200, 100);
		l1->setPosition(0, yOffset);
		l1->setText(stripExtention(levelNames[i]));
		l1->setTextColor(sf::Color::White);
		l1->setTextSize(20);
		l1->setTransparency(125);
		l1->bindCallback(tgui::Button::LeftMouseClicked);
		l1->setCallbackId(i + 1);
		yOffset += offsetInc;
	}
}

void GuiLoader::LoadLevelLostOverlay(tgui::Gui& gui)
{
	//We must always enable the mouse, in case the current scene has made it invisible
	((sf::RenderWindow*)gui.getWindow())->setMouseCursorVisible(true);
	gui.remove(overlay);
	Game::gamePaused = true;

	overlay = tgui::ChildWindow::Ptr(gui);
	overlay->load(GUI_CONFIG);
	overlay->setSize((gui.getWindow()->getSize().x / 20.f) * 18.f, (gui.getWindow()->getSize().y / 15.f) * 13.f);
	overlay->setBackgroundColor(sf::Color(80, 80, 80));
	overlay->setPosition((gui.getWindow()->getSize().x / 20.f), (gui.getWindow()->getSize().y / 15.f));
	overlay->setTitle("Child window");
	overlay->setBorders();
	overlay->setTitleBarHeight(0);

	tgui::Label::Ptr youWonLabel(*overlay);
	youWonLabel->setTextSize(34);
	youWonLabel->setText("You died :(");
	youWonLabel->setPosition((overlay->getSize().x / 2.f) - (youWonLabel->getSize().x / 2.f),
		(overlay->getSize().y / 6.f) * 1.6f);

	tgui::Button::Ptr mainMenuButton(*overlay);
	mainMenuButton->load(GUI_CONFIG);
	mainMenuButton->setSize(150, 40);
	mainMenuButton->setPosition((overlay->getSize().x / 2.f) - 75.f, (overlay->getSize().y / 6.f) * 3.f);
	mainMenuButton->setText("Main Menu");
	mainMenuButton->setTextColor(sf::Color::White);
	mainMenuButton->setTextSize(24);
	mainMenuButton->bindCallback(tgui::Button::LeftMouseClicked);
	mainMenuButton->setCallbackId(1);

	tgui::Button::Ptr nextLevelButton(*overlay);
	nextLevelButton->load(GUI_CONFIG);
	nextLevelButton->setSize(150, 40);
	nextLevelButton->setPosition((overlay->getSize().x / 2.f) - 75.f, (overlay->getSize().y / 6.f) * 4.f);
	nextLevelButton->setText("Retry");
	nextLevelButton->setTextColor(sf::Color::White);
	nextLevelButton->setTextSize(24);
	nextLevelButton->bindCallback(tgui::Button::LeftMouseClicked);
	nextLevelButton->setCallbackId(3);
}

void GuiLoader::LoadLevelWonOverlay(tgui::Gui& gui)
{
	((sf::RenderWindow*)gui.getWindow())->setMouseCursorVisible(true);
	gui.remove(overlay);
	Game::gamePaused = true;

	overlay = tgui::ChildWindow::Ptr(gui);
	overlay->load(GUI_CONFIG);
	overlay->setSize((gui.getWindow()->getSize().x / 20.f) * 18.f, (gui.getWindow()->getSize().y / 15.f) * 13.f);
	overlay->setBackgroundColor(sf::Color(80, 80, 80));
	overlay->setPosition((gui.getWindow()->getSize().x / 20.f), (gui.getWindow()->getSize().y / 15.f));
	overlay->setTitle("Child window");
	overlay->setBorders();
	overlay->setTitleBarHeight(0);

	tgui::Label::Ptr youWonLabel(*overlay);
	youWonLabel->setTextSize(34);
	youWonLabel->setText("You've completed the level!");
	youWonLabel->setPosition((overlay->getSize().x / 2.f) - (youWonLabel->getSize().x / 2.f),
		(overlay->getSize().y / 6.f) * 1.6f);

	tgui::Button::Ptr mainMenuButton(*overlay);
	mainMenuButton->load(GUI_CONFIG);
	mainMenuButton->setSize(150, 40);
	mainMenuButton->setPosition((overlay->getSize().x / 2.f) - 75.f, (overlay->getSize().y / 6.f) * 3.f);
	mainMenuButton->setText("Main Menu");
	mainMenuButton->setTextColor(sf::Color::White);
	mainMenuButton->setTextSize(24);
	mainMenuButton->bindCallback(tgui::Button::LeftMouseClicked);
	mainMenuButton->setCallbackId(1);

	tgui::Button::Ptr nextLevelButton(*overlay);
	nextLevelButton->load(GUI_CONFIG);
	nextLevelButton->setSize(150, 40);
	nextLevelButton->setPosition((overlay->getSize().x / 2.f) - 75.f, (overlay->getSize().y / 6.f) * 4.f);
	nextLevelButton->setText("Next Level");
	nextLevelButton->setTextColor(sf::Color::White);
	nextLevelButton->setTextSize(24);
	nextLevelButton->bindCallback(tgui::Button::LeftMouseClicked);
	nextLevelButton->setCallbackId(2);
}

void GuiLoader::LoadGameWonOverlay(tgui::Gui& gui)
{
	((sf::RenderWindow*)gui.getWindow())->setMouseCursorVisible(true);
	gui.remove(overlay);
	Game::gamePaused = true;

	overlay = tgui::ChildWindow::Ptr(gui);
	overlay->load(GUI_CONFIG);
	overlay->setSize((gui.getWindow()->getSize().x / 20.f) * 18.f, (gui.getWindow()->getSize().y / 15.f) * 13.f);
	overlay->setBackgroundColor(sf::Color(80, 80, 80));
	overlay->setPosition((gui.getWindow()->getSize().x / 20.f), (gui.getWindow()->getSize().y / 15.f));
	overlay->setTitle("Child window");
	overlay->setBorders();
	overlay->setTitleBarHeight(0);

	tgui::Label::Ptr youWonLabel(*overlay);
	youWonLabel->setTextSize(34);
	youWonLabel->setText("You've completed the game!");
	youWonLabel->setPosition((overlay->getSize().x / 2.f) - (youWonLabel->getSize().x / 2.f),
		(overlay->getSize().y / 6.f) * 1.6f);

	tgui::Button::Ptr mainMenuButton(*overlay);
	mainMenuButton->load(GUI_CONFIG);
	mainMenuButton->setSize(150, 40);
	mainMenuButton->setPosition((overlay->getSize().x / 2.f) - 75.f, (overlay->getSize().y / 6.f) * 3.f);
	mainMenuButton->setText("Main Menu");
	mainMenuButton->setTextColor(sf::Color::White);
	mainMenuButton->setTextSize(24);
	mainMenuButton->bindCallback(tgui::Button::LeftMouseClicked);
	mainMenuButton->setCallbackId(1);
}

void GuiLoader::LoadSettingsOverlay2(tgui::Gui& gui)
{
	Game::gamePaused = true;
	((sf::RenderWindow*)gui.getWindow())->setMouseCursorVisible(true);
	gui.remove(overlay);

	overlay = tgui::ChildWindow::Ptr(gui);
	overlay->load(GUI_CONFIG);
	overlay->setSize((gui.getWindow()->getSize().x / 20.f) * 18.f, (gui.getWindow()->getSize().y / 15.f) * 13.f);
	overlay->setBackgroundColor(sf::Color(80, 80, 80));
	overlay->setPosition((gui.getWindow()->getSize().x / 20.f), (gui.getWindow()->getSize().y / 15.f));
	overlay->setTitle("Child window");
	overlay->setBorders();
	overlay->setTitleBarHeight(0);

	tgui::Label::Ptr volumeLabel(*overlay);
	volumeLabel->setTextSize(24);
	volumeLabel->setText("Volume:");
	volumeLabel->setPosition((overlay->getSize().x / 2.f) - (volumeLabel->getSize().x / 2.f),
		(overlay->getSize().y / 6.f) * 1.6f);

	tgui::Slider::Ptr volumeSlider(*overlay);
	volumeSlider->load(GUI_CONFIG);
	volumeSlider->setSize(300, 25);
	volumeSlider->setVerticalScroll(false);
	volumeSlider->setPosition((overlay->getSize().x / 2.f) - 150, (overlay->getSize().y / 6.f) * 2.f);
	volumeSlider->setMaximum(100);
	volumeSlider->setValue(AudioManager::getInstance().getVolume());
	volumeSlider->bindCallback(std::bind(GuiLoader::VolumeChanged, volumeSlider), tgui::Slider::ValueChanged);
	
	tgui::Button::Ptr mainMenuButton(*overlay);
	mainMenuButton->load(GUI_CONFIG);
	mainMenuButton->setSize(150, 40);
	mainMenuButton->setPosition((overlay->getSize().x / 2.f) - 75.f, (overlay->getSize().y / 6.f) * 3.f);
	mainMenuButton->setText("Main Menu");
	mainMenuButton->setTextColor(sf::Color::White);
	mainMenuButton->setTextSize(24);
	mainMenuButton->bindCallback(tgui::Button::LeftMouseClicked);
	mainMenuButton->setCallbackId(1);

	tgui::Button::Ptr quitButton(*overlay);
	quitButton->load(GUI_CONFIG);
	quitButton->setSize(150, 40);
	quitButton->setPosition((overlay->getSize().x / 2.f) - 75, (overlay->getSize().y / 6.f) * 4.f);
	quitButton->setText("Quit Game");
	quitButton->setTextColor(sf::Color::White);
	quitButton->setTextSize(24);
	quitButton->bindCallback(QuitGame, tgui::Button::LeftMouseClicked);

	tgui::Button::Ptr closeButton(*overlay);
	closeButton->load(GUI_CONFIG);
	closeButton->setSize(80, 40);
	closeButton->setPosition((overlay->getSize().x / 2.f) - 40, (overlay->getSize().y / 6.f) * 5.f);
	closeButton->setText("Close");
	closeButton->setTextColor(sf::Color::White);
	closeButton->setTextSize(24);
	closeButton->bindCallback(std::bind(GuiLoader::DestroySettingsOverlay2, std::ref(gui)), tgui::Button::LeftMouseClicked);
}

void GuiLoader::LoadSettingsOverlay(tgui::Gui& gui)
{
	gui.remove(overlay);

	overlay = tgui::ChildWindow::Ptr(gui);
	overlay->load(GUI_CONFIG);
	overlay->setSize((gui.getWindow()->getSize().x / 20.f) * 18.f, (gui.getWindow()->getSize().y / 15.f) * 13.f);
	overlay->setBackgroundColor(sf::Color(80, 80, 80));
	overlay->setPosition((gui.getWindow()->getSize().x / 20.f), (gui.getWindow()->getSize().y / 15.f));
	overlay->setTitle("Child window");
	overlay->setBorders();
	overlay->setTitleBarHeight(0);

	tgui::Label::Ptr volumeLabel(*overlay);
	volumeLabel->setTextSize(24);
	volumeLabel->setText("Volume:");
	volumeLabel->setPosition((overlay->getSize().x / 2.f) - (volumeLabel->getSize().x / 2.f),
		(overlay->getSize().y / 6.f) * 1.6f);

	tgui::Slider::Ptr volumeSlider(*overlay);
	volumeSlider->load(GUI_CONFIG);
	volumeSlider->setSize(300, 25);
	volumeSlider->setVerticalScroll(false);
	volumeSlider->setPosition((overlay->getSize().x / 2.f) - 150, (overlay->getSize().y / 6.f) * 2.f);
	volumeSlider->setMaximum(100);
	volumeSlider->setValue(AudioManager::getInstance().getVolume());
	volumeSlider->bindCallback(std::bind(GuiLoader::VolumeChanged, volumeSlider), tgui::Slider::ValueChanged);

	tgui::Button::Ptr quitButton(*overlay);
	quitButton->load(GUI_CONFIG);
	quitButton->setSize(150, 40);
	quitButton->setPosition((overlay->getSize().x / 2.f) - 75, (overlay->getSize().y / 6.f) * 4.f);
	quitButton->setText("Quit Game");
	quitButton->setTextColor(sf::Color::White);
	quitButton->setTextSize(24);
	quitButton->bindCallback(QuitGame, tgui::Button::LeftMouseClicked);

	tgui::Button::Ptr closeButton(*overlay);
	closeButton->load(GUI_CONFIG);
	closeButton->setSize(80, 40);
	closeButton->setPosition((overlay->getSize().x / 2.f) - 40, (overlay->getSize().y / 6.f) * 5.f);
	closeButton->setText("Close");
	closeButton->setTextColor(sf::Color::White);
	closeButton->setTextSize(24);
	closeButton->bindCallback(std::bind(GuiLoader::DestroySettingsOverlay, std::ref(gui)), tgui::Button::LeftMouseClicked);

}

void GuiLoader::VolumeChanged(tgui::Slider::Ptr volumeSlider)
{
	AudioManager::getInstance().setVolume(volumeSlider->getValue());
}

void GuiLoader::QuitGame()
{
	Game::continueGame = false;
}

void GuiLoader::DestroySettingsOverlay(tgui::Gui& gui)
{
	gui.remove(overlay);
	Game::gamePaused = false;
}

void GuiLoader::DestroySettingsOverlay2(tgui::Gui& gui)
{
	((sf::RenderWindow*)gui.getWindow())->setMouseCursorVisible(false);
	gui.remove(overlay);
	Game::gamePaused = false;
}

void GuiLoader::ScrollBarMoved(tgui::Panel::Ptr panel, const tgui::Callback& callback)
{
	int distanceToMove = previousScrolbarValue - callback.value;

	// Move all widgets that are inside the panel
	for (auto& widget : panel->getWidgets())
		widget->setPosition(widget->getPosition().x, widget->getPosition().y + distanceToMove);

	previousScrolbarValue = callback.value;
}

string GuiLoader::stripExtention(const string& s)
{
	int lastindex = s.find_last_of(".");
	return s.substr(0, lastindex);
}