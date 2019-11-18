#include "GuiMenuItem.h"

GuiMenuItem::GuiMenuItem()
	: listener(nullptr)
{
}

void GuiMenuItem::AddListener(Listener* listener)
{
	this->listener = listener;
}

void GuiMenuItem::AddItem(unsigned int id, const char* name, const char* shortcut, GuiMenuItem* menuItem)
{
	MenuItem item;
	item.name = name;
	item.shortcut = shortcut;
	item.menuItem = menuItem;

	menuItems.insert({ id, item });
}

void GuiMenuItem::AddItem(unsigned int id, const char* name, const char* shortcut, GuiMenuItem* menuItem, std::function<void(const MenuItem&)>&& callbackFunction)
{
	MenuItem item;
	item.name = name;
	item.shortcut = shortcut;
	item.menuItem = menuItem;
	item.callbackFunction = callbackFunction;

	menuItems.insert({ id, item });
}

void GuiMenuItem::SetItem(unsigned int id, const char* name, const char* shortcut, GuiMenuItem* menuItem)
{
	MenuItem item;
	item.name = name;
	item.shortcut = shortcut;
	item.menuItem = menuItem;

	menuItems[id] = item;
}

void GuiMenuItem::AddSeparator()
{
	MenuItem item;
	item.separator = true;
	menuItems.insert({ -1, item });
}

void GuiMenuItem::Draw()
{
	for (auto each : menuItems)
	{
		MenuItem& item = each.second;

		if (item.separator)
		{
			ImGui::Separator();
			continue;
		}

		if (item.menuItem)
		{
			if (ImGui::BeginMenu(item.name))
			{
				item.menuItem->Draw();
				ImGui::EndMenu();
			}
		}
		else
		{
			if (ImGui::MenuItem(item.name, item.shortcut))
			{
				if (item.callbackFunction)
					item.callbackFunction(item);

				if (listener)
					listener->OnMenuItem(each.first, item);
			}
		}
	}
}
