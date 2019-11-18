#pragma once
#include "GuiComponent.h"

class GuiCheckbox : public GuiComponent
{
public:
	struct Listener
	{
		void OnCheckboxClickedListener(GuiCheckbox* checkbox) { }
	};

public:
	GuiCheckbox(const char* label = "Checkbox", bool isChecked = false);

	void SetLabel(const char* newLabel) { label = newLabel; }
	void SetChecked(bool shouldCheck) { checked = shouldCheck; }
	void AddListener(Listener* listener) { this->listener = listener; }
	bool IsChecked() { return checked; }

	void Draw() override;

private:
	bool checked;
	const char* label;
	Listener* listener;
};
