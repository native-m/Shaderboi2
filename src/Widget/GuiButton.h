#pragma once
#include "GuiComponent.h"
#include "imgui.h"

class GuiButton : public GuiComponent
{
public:
	typedef struct
	{
		virtual void OnButtonClickListener(GuiButton* button) {}
		virtual void OnButtonHoldListener(GuiButton* button) {}
		virtual void OnButtonPressedListener(GuiButton* button) {}
	} Listener;

public:
	GuiButton(const char* text = nullptr, ImVec2 size = ImVec2(0, 0));

	void AddListener(Listener* listener);
	void SetText(const char* newText);
	void SetSize(float x, float y);
	void SetSmall(bool shouldSmall = true);
	void SetEnable(bool shouldEnable = true);

	void Draw() override;

private:
	const char* text;
	ImVec2 size;
	Listener* listener;
	bool small;
	bool enable;
};
