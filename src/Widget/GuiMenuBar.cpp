#include "GuiMenuBar.h"

GuiMenuBar::GuiMenuBar()
{
}

void GuiMenuBar::AddItem(unsigned int id, const char* name, GuiMenuItem* item)
{
	MenuBarSlot slot;
	slot.name = name;
	slot.menuItem = item;

	menuBarItem.insert({ id, slot });
}

void GuiMenuBar::AddItem(unsigned int id, const char* name, GuiMenuItem* item, std::function<void(const MenuBarSlot&)>&& callbackFunction)
{
	MenuBarSlot slot;
	slot.name = name;
	slot.menuItem = item;
	slot.callbackFunction = callbackFunction;

	menuBarItem.insert({id, slot});
}

void GuiMenuBar::Draw()
{
	if(BeginMenuBarDraw())
	{
		for (auto item : menuBarItem)
		{
			MenuBarSlot& slot = item.second;

			if (ImGui::BeginMenu(slot.name))
			{
				if (slot.callbackFunction)
					slot.callbackFunction(slot);

				if (slot.menuItem)
					slot.menuItem->Draw();

				ImGui::EndMenu();
			}
		}

		EndMenuBarDraw();
	}
}
