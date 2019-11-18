#pragma once
#include "imgui.h"
#include "GuiComponent.h"

class GuiSelectable : public GuiComponent
{
public:
	typedef struct
	{
		virtual void OnSelected(GuiSelectable* selectable) {}
	} Listener;

public:
	GuiSelectable(const char* label = nullptr, bool* select = nullptr, ImGuiSelectableFlags flags = 0, const ImVec2& size = ImVec2(0.f, 0.f));

	void AddListener(Listener* listener);
	void SetText(const char* label);
	void SetSize(float x, float y);

	void Draw() override;

private:
	const char* label;
	bool* select;
	ImGuiSelectableFlags flags;
	ImVec2 size;
	Listener* listener;
};
