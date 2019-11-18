#pragma once

#include "GuiComponent.h"
#include "GuiMenuItem.h"
#include "GuiMenuBar.h"
#include "imgui.h"

class GuiMainMenuBar : public GuiMenuBar
{
public:
	GuiMainMenuBar();

	virtual bool BeginMenuBarDraw() override { return ImGui::BeginMainMenuBar(); }
	virtual void EndMenuBarDraw() override { ImGui::EndMainMenuBar(); }
};
