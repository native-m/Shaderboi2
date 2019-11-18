#pragma once

#include "GuiComponent.h"
#include "GuiMenuItem.h"
#include "imgui.h"

class GuiMenuBar : public GuiComponent
{
public:

	typedef struct MenuBarSlot
	{
		const char* name;
		GuiMenuItem* menuItem = nullptr;
		std::function<void(const MenuBarSlot&)> callbackFunction;
	} MenuBarSlot;

public:
	GuiMenuBar();

	void AddItem(unsigned int id, const char* name, GuiMenuItem* item = nullptr);
	void AddItem(unsigned int id, const char* name, GuiMenuItem* item, std::function<void(const MenuBarSlot&)>&& callbackFunction);

	virtual bool BeginMenuBarDraw() { return ImGui::BeginMenuBar(); }
	virtual void EndMenuBarDraw() { ImGui::EndMenuBar(); }
	void Draw() override;

private:
	std::unordered_map<unsigned int, MenuBarSlot> menuBarItem;
};
