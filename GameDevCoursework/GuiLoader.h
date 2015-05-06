#pragma once
#include <TGUI\TGUI.hpp>
#include <string>
#include <vector>

using namespace std;

class GuiLoader
{
public:

	static void LoadMainMenuGui(tgui::Gui& gui, const vector<string>& levelNames);
	static void LoadSettingsOverlay2(tgui::Gui& gui);
	static void LoadGameWonOverlay(tgui::Gui& gui);
	static void LoadLevelWonOverlay(tgui::Gui& gui);
	static void LoadLevelLostOverlay(tgui::Gui& gui);

private:
	static const std::string GUI_CONFIG;
	static tgui::ChildWindow::Ptr GuiLoader::overlay;
	static int previousScrolbarValue;

	static void DestroySettingsOverlay(tgui::Gui& gui);
	static void DestroySettingsOverlay2(tgui::Gui& gui);
	static void LoadSettingsOverlay(tgui::Gui& gui);
	static void VolumeChanged(tgui::Slider::Ptr volumeSlider);
	static void ScrollBarMoved(tgui::Panel::Ptr panel, const tgui::Callback& callback);
	static void QuitGame();

	static string stripExtention(const string& name);

	GuiLoader(){}
	~GuiLoader(){}
};

