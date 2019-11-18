#pragma once
#include "../Widget/GuiWindow.h"
#include "../Widget/GuiBufferView.h"
#include "../Widget/GuiTabBar.h"

class ShaderView : public GuiWindow
{
public:
	ShaderView();

private:
	std::unique_ptr<GuiBufferView> mainBuffer;
	GuiTabBar tabs;
	GuiTabItem mainBufferTab;
	GuiBufferView bufView;
};
