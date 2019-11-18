#include "MainGui.h"
#include <iostream>
#include "../Main.h"
#include "../Shaderboi.h"

enum MainGuiMenu
{
	MENU_OPEN,
	MENU_SAVE,
	MENU_SAVEAS,
	MENU_VIEWOUTLINE,
	MENU_VIEWCONSOLE,
	MENU_ABOUT
};

MainGui::MainGui()
{
	aboutWindow.reset(new About());
	outlineWindow.reset(new Outline());
	mainImageCodeEditorWindow.reset(new CodeEditor("Main Image"));
	shaderViewWindow.reset(new ShaderView());
	globalUniformWindow.reset(new GlobalUniform());

	mainImageCodeEditorWindow->SetText(gInstance->GetMainShader());
	mainImageCodeEditorWindow->SetAssociatedBuffer(0);

	mainMenu.AddItem(0, "File", &fileMenuItem);
	mainMenu.AddItem(1, "View", &viewMenuItem);
	mainMenu.AddItem(2, "Help", &helpMenuItem);

	fileMenuItem.AddListener(this);
	fileMenuItem.AddItem(MENU_OPEN, "Open..", "Ctrl+O");
	fileMenuItem.AddItem(MENU_SAVE, "Save", "Ctrl+S");
	fileMenuItem.AddItem(MENU_SAVEAS, "Save as..", "Ctrl+Shift+S");

	viewMenuItem.AddListener(this);
	viewMenuItem.AddItem(MENU_VIEWOUTLINE, "Outline", "Ctrl+Alt+O");

	helpMenuItem.AddListener(this);
	helpMenuItem.AddItem(MENU_ABOUT, "About", "Ctrl+A", nullptr);
}

void MainGui::ShowEditorWindow(int editorId, bool shouldShow)
{
	if(editorId == 0)
		mainImageCodeEditorWindow->SetOpen(shouldShow);
}

bool MainGui::IsEditorShown(int editorId)
{
	if(editorId == 0)
		return mainImageCodeEditorWindow->IsOpen();
	return false;
}

void MainGui::OnMenuItem(unsigned int id, const GuiMenuItem::MenuItem& item)
{
	switch (id)
	{
	case MENU_OPEN:
	case MENU_SAVE:
	case MENU_SAVEAS:
		break;
	case MENU_VIEWOUTLINE:
		if (outlineWindow->IsOpen())
			outlineWindow->SetOpen(false);
		else
			outlineWindow->SetOpen(true);
		break;
	case MENU_ABOUT:
		aboutWindow->SetOpen(true);
		break;
	}
}

void MainGui::Draw()
{
	aboutWindow->Draw();
	outlineWindow->Draw();
	mainImageCodeEditorWindow->Draw();
	shaderViewWindow->Draw();
	globalUniformWindow->Draw();
	mainMenu.Draw();
}
