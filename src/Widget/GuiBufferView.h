#pragma once
#include "GuiComponent.h"
#include "imgui.h"

class Buffer;

class GuiBufferView : public GuiComponent
{
public:
	GuiBufferView(int w = 128, int h = 128);

	void SetBuffer(Buffer* buffer);

	void Draw() override;

private:
	int width, height;
	Buffer* buf;
};
