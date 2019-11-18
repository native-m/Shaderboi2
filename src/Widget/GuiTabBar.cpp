#include "GuiTabBar.h"

GuiTabBar::GuiTabBar(const char* id)
	: id(id)
{	
}

void GuiTabBar::SetID(const char* newId)
{
	id = newId;
}

void GuiTabBar::AddTab(GuiTabItem* tabItem)
{
	tabs.push_back(tabItem);
}

void GuiTabBar::Draw()
{
	if (ImGui::BeginTabBar(id, ImGuiTabBarFlags_None))
	{
		for (auto t : tabs)
			t->Draw();
		ImGui::EndTabBar();
	}
}
