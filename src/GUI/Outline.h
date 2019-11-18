#pragma once
#include "../Main.h"
#include "../Widget/GuiWindow.h"
#include "../Widget/GuiPopup.h"
#include "../Widget/GuiButton.h"
#include "../Widget/GuiSelectable.h"
#include "../Widget/GuiBufferView.h"

class MainGui;

class Outline : public GuiWindow, GuiButton::Listener
{
	class AddPopup : public GuiPopup, GuiSelectable::Listener
	{
	public:
		AddPopup();

		void OnSelected(GuiSelectable* selectable) override;

	private:
		GuiSelectable addBuffer;
		GuiSelectable addTexture;
	};

public:
	Outline();

	void OnButtonClickListener(GuiButton* btn);

private:
	std::unique_ptr<AddPopup> addPopup;
	GuiButton addBtn;
	GuiButton editMainBtn;

	bool showMain = false, editMain = false;
};
