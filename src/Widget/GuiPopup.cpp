#include "GuiPopup.h"

GuiPopup::GuiPopup(const char* id)
	: id(id)
{
}

void GuiPopup::Draw()
{
	if (BeginDraw(id, nullptr, windowFlags))
	{
		DrawComponent();
		EndDraw();
	}
}

