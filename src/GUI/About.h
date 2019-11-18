#pragma once
#include "../Widget/GuiButton.h"
#include "../Widget/GuiWindow.h"

class About : public GuiWindow, GuiButton::Listener
{
public:
	About()
		: GuiWindow("About", false)
	{
		closeBtn.AddListener(this);
		closeBtn.SetText("OK");

		// -- Arrange Start
		AddText("Shaderboi", true);
		AddText("Native-M");
		AddSeparator();
		AddComponent(&closeBtn);
		// -- Arrange End

		SetResizable(false);
	}

	void OnButtonClickListener(GuiButton* btn)
	{
		if (btn == &closeBtn)
			SetOpen(false);
	}

private:
	GuiButton closeBtn;
};
