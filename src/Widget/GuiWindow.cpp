#include "GuiWindow.h"
#include <cstdlib>

GuiWindow::GuiWindow(const char* name, bool shouldOpen, ImGuiWindowFlags windowFlags)
	: name(name), open(shouldOpen), windowFlags(windowFlags)
{
}

GuiWindow::~GuiWindow()
{
	for (auto i : drawList)
		delete i;
}

void GuiWindow::AddComponent(GuiComponent* component)
{
	DrawItem* item = new DrawItem();

	item->drawMode = DRAW_COMPONENT;
	item->components = component;

	drawList.push_back(item);
}

void GuiWindow::AddText(const char* str, bool wrapped)
{
	DrawItem* item = new DrawItem();

	item->drawMode = DRAW_TEXT;
	item->text = str;
	item->wrappedText = wrapped;

	drawList.push_back(item);
}

void GuiWindow::AddTextFormatted(bool wrapping, const char* fmt, ...)
{
	DrawItem* item = new DrawItem();
	
	item->drawMode = DRAW_TEXTFORMATTED;
	item->text = fmt;

	drawList.push_back(item);
}

void GuiWindow::AddSeparator()
{
	DrawItem* item = new DrawItem();

	item->drawMode = DRAW_SEPARATOR;

	drawList.push_back(item);
}

void GuiWindow::SetSize(float x, float y)
{
	preSized = true;
	size.x = x;
	size.y = y;
}

void GuiWindow::SetPosition(float x, float y)
{
	pos.x = x;
	pos.y = y;
}

void GuiWindow::SetTitle(const char* title)
{
	name = title;
}

void GuiWindow::SetResizable(bool isResizable)
{
	windowFlags = (isResizable) ? windowFlags & ~ImGuiWindowFlags_NoResize : windowFlags | ImGuiWindowFlags_NoResize;
}

void GuiWindow::SetOpen(bool shouldOpen)
{
	open = shouldOpen;
}

void GuiWindow::SameLine(float offsetX, float spacing)
{
	DrawItem* item = new DrawItem();

	item->drawMode = DRAW_SAMELINE;
	item->sameLine = { offsetX, spacing };

	drawList.push_back(item);
}

void GuiWindow::EndSameLine()
{
	DrawItem* item = new DrawItem();

	item->drawMode = DRAW_ENDSAMELINE;

	drawList.push_back(item);
}

void GuiWindow::Bullet()
{
	DrawItem* item = new DrawItem();

	item->drawMode = DRAW_BULLET;

	drawList.push_back(item);
}

void GuiWindow::EndBullet()
{
	DrawItem* item = new DrawItem();

	item->drawMode = DRAW_ENDBULLET;

	drawList.push_back(item);
}

void GuiWindow::Draw()
{
	if (preSized)
		ImGui::SetNextWindowSize(size, ImGuiCond_FirstUseEver);

	ImGui::SetNextWindowPos(pos, ImGuiCond_FirstUseEver);

	if(open)
	{
		if(BeginDraw((name != nullptr) ? name : "", &open, windowFlags))
			DrawComponent();

		EndDraw();
	}
}

void GuiWindow::DrawComponent()
{
	bool sameLine = false;
	bool doSameLine = false;
	bool bullet = false;

	for (auto item : drawList)
	{
		if (item->drawMode == DRAW_ENDSAMELINE)
		{
			sameLine = false;
			doSameLine = false;
			continue;
		}

		if (item->drawMode == DRAW_ENDBULLET)
		{
			bullet = false;
			continue;
		}

		if (sameLine && !doSameLine)
			ImGui::SameLine();

		if (bullet)
			ImGui::Bullet();

		doSameLine = false;

		switch (item->drawMode)
		{
		case DRAW_COMPONENT:
			item->components->Draw();
			break;
		case DRAW_TEXT:
			if (!item->wrappedText)
			{
				ImGui::Text(item->text);
				break;
			}

			ImGui::TextWrapped(item->text);
			break;
		case DRAW_SEPARATOR:
			ImGui::Separator();
			break;
		case DRAW_SAMELINE:
			sameLine = true;
			doSameLine = true;
			break;
		case DRAW_BULLET:
			bullet = true;
			break;
		}
	}
}
