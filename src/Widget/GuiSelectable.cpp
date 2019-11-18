#include "GuiSelectable.h"

GuiSelectable::GuiSelectable(const char* label, bool* select, ImGuiSelectableFlags flags, const ImVec2& size)
	: label(label), select(select), flags(flags), size(size), listener(nullptr)
{
}

void GuiSelectable::AddListener(Listener* listener)
{
	this->listener = listener;
}

void GuiSelectable::SetText(const char* label)
{
	this->label = label;
}

void GuiSelectable::SetSize(float x, float y)
{
	size.x = x;
	size.y = y;
}

void GuiSelectable::Draw()
{
	const char* l = (label ? label : "Selectable");

	if ((select ? ImGui::Selectable(l, select, flags, size) : ImGui::Selectable(l, false, flags, size)))
		listener->OnSelected(this);
}
