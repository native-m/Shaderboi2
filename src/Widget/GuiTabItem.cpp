#include "GuiTabItem.h"
#include "imgui.h"

GuiTabItem::GuiTabItem(const char* title)
	: GuiWindow(title), closeable(false)
{
	SetOpen(true);
}

void GuiTabItem::SetCloseable(bool canClose)
{
	closeable = canClose;
}

void GuiTabItem::Draw()
{
	if (ImGui::BeginTabItem(name, (closeable) ? &open : nullptr, 0))
	{
		GuiWindow::DrawComponent();
		ImGui::EndTabItem();
	}
}
