#include "GuiButton.h"
#include "imgui_internal.h"

GuiButton::GuiButton(const char* text, ImVec2 size)
	: text(text), size(size), small(false), listener(nullptr)
{
}

void GuiButton::AddListener(Listener* listener)
{
	this->listener = listener;
}

void GuiButton::SetText(const char* newText)
{
	text = newText;
}

void GuiButton::SetSize(float x, float y)
{
	size.x = x;
	size.y = y;
}

void GuiButton::SetSmall(bool shouldSmall)
{
	small = shouldSmall;
}

void GuiButton::SetEnable(bool shouldEnable)
{
	enable = shouldEnable;
}

void GuiButton::Draw()
{
	const char* t = (text != nullptr) ? text : "";

	if (!enable)
	{
		ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);
		ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
	}

	if ((small ? ImGui::SmallButton(t) : ImGui::Button(t, size)))
		if(listener)
			listener->OnButtonClickListener(this);

	if (!enable)
	{
		ImGui::PopItemFlag();
		ImGui::PopStyleVar();
	}

	if (listener)
	{
		if (ImGui::IsItemActive())
			listener->OnButtonHoldListener(this);

		if (ImGui::IsItemActivated())
			listener->OnButtonPressedListener(this);
	}
}
