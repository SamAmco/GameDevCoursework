#pragma once
#include <TGUI\TGUI.hpp>
#include <string>


class GuiLoader
{
public:

	static void LoadMainMenuGui(tgui::Gui& gui);
	static void LoadSettingsOverlay(tgui::Gui& gui);
	static void DestroySettingsOverlay(tgui::Gui& gui);

private:
	static const std::string GUI_CONFIG;
	static tgui::ChildWindow::Ptr GuiLoader::settingsOverlay;
	GuiLoader(){}
	~GuiLoader(){}
};

