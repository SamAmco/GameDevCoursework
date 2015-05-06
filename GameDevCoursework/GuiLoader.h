//File Written by Samuel Amantea-Collins
#pragma once
#include <TGUI\TGUI.hpp>
#include <string>
#include <vector>

using namespace std;

//This is where all the code is for loading TGUI elements and displaying them
class GuiLoader
{
public:

	static void LoadMainMenuGui(tgui::Gui& gui, const vector<string>& levelNames);
	static void LoadSettingsOverlay2(tgui::Gui& gui);
	static void LoadGameWonOverlay(tgui::Gui& gui);
	static void LoadLevelWonOverlay(tgui::Gui& gui);
	static void LoadLevelLostOverlay(tgui::Gui& gui);

private:
	//TGUI provides support for config files (which act like style sheets)
	static const std::string GUI_CONFIG;
	//stores the current overlay
	static tgui::ChildWindow::Ptr GuiLoader::overlay;
	//This is used for the scroll bar in the main menu
	static int previousScrolbarValue;

	static void DestroySettingsOverlay(tgui::Gui& gui);
	//This is used in the level scene
	static void DestroySettingsOverlay2(tgui::Gui& gui);
	//This is used in the menu scene
	static void LoadSettingsOverlay(tgui::Gui& gui);
	//This is called when the volume slider value is changed
	static void VolumeChanged(tgui::Slider::Ptr volumeSlider);
	//This is called when the scroll bar is moved in the main menu
	static void ScrollBarMoved(tgui::Panel::Ptr panel, const tgui::Callback& callback);
	static void QuitGame();

	static string stripExtention(const string& name);

	GuiLoader(){}
	~GuiLoader(){}
};

