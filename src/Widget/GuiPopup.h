#pragma once
#include "imgui.h"
#include "GuiWindow.h"

class GuiPopup : public GuiWindow
{
public:
	GuiPopup(const char* id);

	bool BeginDraw(const char* name, bool* pOpen, ImGuiWindowFlags windowFlags) override
	{
		return ImGui::BeginPopup(name, windowFlags);
	}

	void EndDraw() override
	{
		ImGui::EndPopup();
	}

	void Draw() override;

private:
	const char* id;
};
