#pragma once
#include <TGUI\TGUI.hpp>
#include <string>

class GuiLoader
{
public:

	static void LoadMainMenuGui(tgui::Gui& gui);
	static void LoadSettingsOverlay2(tgui::Gui& gui);
	static void LoadGameWonOverlay(tgui::Gui& gui);
	static void LoadLevelWonOverlay(tgui::Gui& gui);
	static void LoadLevelLostOverlay(tgui::Gui& gui);

private:
	static const std::string GUI_CONFIG;
	static tgui::ChildWindow::Ptr GuiLoader::overlay;

	static void DestroySettingsOverlay(tgui::Gui& gui);
	static void DestroySettingsOverlay2(tgui::Gui& gui);
	static void LoadSettingsOverlay(tgui::Gui& gui);
	static void VolumeChanged(tgui::Slider::Ptr volumeSlider);
	static void QuitGame();

	GuiLoader(){}
	~GuiLoader(){}
};

