#include "Outline.h"
#include "../Shaderboi.h"
#include "../GUI/MainGui.h"

Outline::Outline()
	: GuiWindow("Outline", true)
{
	addBtn.AddListener(this);
	addBtn.SetText("+");

	editMainBtn.AddListener(this);
	editMainBtn.SetText("Edit");
	editMainBtn.SetSmall();

	addPopup.reset(new AddPopup());

	// -- Arrange Start --
	AddComponent(addPopup.get());
	SameLine();
		AddText("Main Image");
		AddComponent(&editMainBtn);
	EndSameLine();
	AddComponent(&addBtn);
	// -- Arrange End -- 

	// Set initial size and position
	SetSize(200, 400);
	SetPosition(80, 50);
}

void Outline::OnButtonClickListener(GuiButton* btn)
{
	if (btn == &addBtn)
		ImGui::OpenPopup("add_popup");
	else if (btn == &editMainBtn)
	{
#ifdef _DEBUG
		assert(gMainGUI != nullptr);
#endif
		if (!gMainGUI->IsEditorShown(0)) gMainGUI->ShowEditorWindow(0, true);
		else gMainGUI->ShowEditorWindow(0, false);
	}
}

Outline::AddPopup::AddPopup()
	: GuiPopup("add_popup")
{
	addBuffer.AddListener(this);
	addBuffer.SetText("Buffer");

	addTexture.AddListener(this);
	addTexture.SetText("Texture");

	AddText("Add..");
	AddSeparator();
	AddComponent(&addBuffer);
	AddComponent(&addTexture);
}

void Outline::AddPopup::OnSelected(GuiSelectable* selectable)
{
	if (selectable == &addBuffer)
	{
		// TODO: Add buffer
	}
	else if (selectable == &addTexture)
	{
		// TODO: Add texture
	}
}
