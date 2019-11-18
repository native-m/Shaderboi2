#include "GuiComponent.h"
#include "GuiTabItem.h"
#include <vector>

class GuiTabBar : public GuiComponent
{
public:
	GuiTabBar(const char* id = "TabBar");

	void SetID(const char* newId);
	void AddTab(GuiTabItem* tabItem);
	GuiTabItem* GetTabItem(int index) { return tabs[index]; }
	const char* GetID() { return id; }

	void Draw() override;

private:
	const char* id;
	std::vector<GuiTabItem*> tabs;
};
