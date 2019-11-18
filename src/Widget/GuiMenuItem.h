#pragma once

#include <unordered_map>
#include <functional>
#include "GuiComponent.h"
#include "imgui.h"

class GuiMenuItem : public GuiComponent
{
public:
	typedef struct MenuItem
	{
		bool separator = false;
		const char* name;
		const char* shortcut = nullptr;
		GuiMenuItem* menuItem = nullptr;
		std::function<void(const MenuItem&)> callbackFunction;
	} MenuItem;

	typedef struct Listener
	{
		virtual void OnMenuItem(unsigned int id, const MenuItem& menuItem) {}
	} Listener;

public:
	GuiMenuItem();

	void AddListener(Listener* listener);

	void AddItem(
		unsigned int id,
		const char* name,
		const char* shortcut = nullptr,
		GuiMenuItem* menuItem = nullptr);

	void AddItem(
		unsigned int id,
		const char* name,
		const char* shortcut,
		GuiMenuItem* menuItem,
		std::function<void(const MenuItem&)>&& callback);

	void SetItem(unsigned int id,
		const char* name,
		const char* shortcut = nullptr,
		GuiMenuItem* menuItem = nullptr);

	void AddSeparator();

	void Draw() override;

private:
	Listener* listener;
	std::unordered_map<unsigned int, MenuItem> menuItems;
};

