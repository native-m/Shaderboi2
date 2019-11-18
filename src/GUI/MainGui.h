#pragma once
#include "../Widget/GuiMainMenuBar.h"
#include "../Widget/GuiWindow.h"
#include "About.h"
#include "Outline.h"
#include "CodeEditor.h"
#include "ShaderView.h"
#include "GlobalUniform.h"
#include "imgui.h"

class Shaderboi;

class MainGui : GuiMenuItem::Listener
{
public:
	MainGui();

	void ShowEditorWindow(int editorId, bool shouldShow);
	bool IsEditorShown(int editorId);

	void OnMenuItem(unsigned int id, const GuiMenuItem::MenuItem& item) override;

	void Draw();

private:
	GuiMainMenuBar mainMenu;

	// Menu items
	GuiMenuItem fileMenuItem;
	GuiMenuItem viewMenuItem;
	GuiMenuItem helpMenuItem;

	// Window
	std::unique_ptr<About> aboutWindow;
	std::unique_ptr<Outline> outlineWindow;
	std::unique_ptr<CodeEditor> mainImageCodeEditorWindow;
	std::unique_ptr<ShaderView> shaderViewWindow;
	std::unique_ptr<GlobalUniform> globalUniformWindow;

	bool showAbout = false;
};
