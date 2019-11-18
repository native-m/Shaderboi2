#include "GuiCheckbox.h"
#include "imgui.h"

GuiCheckbox::GuiCheckbox(const char* label, bool isChecked)
	: label(label), checked(isChecked), listener(nullptr)
{
}

void GuiCheckbox::Draw()
{
	ImGui::Checkbox(label, &checked);
}
