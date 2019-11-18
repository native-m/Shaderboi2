#pragma once
#include "../Widget/GuiWindow.h"
#include "../Widget/GuiButton.h"
#include "../Widget/GuiInput.h"

class GlobalUniform : public GuiWindow, GuiButton::Listener, InputType<double>::Listener
{
public:
	GlobalUniform();

	void OnButtonClickListener(GuiButton* btn) override;
	void OnInputDoubleChanged(GuiInputDouble* input) override;

	void Draw() override;

private:
	GuiButton timerReset;
	GuiButton timerPause;
	GuiInputDouble timerEdit;
	GuiInputDouble deltaTimeEdit;
};
