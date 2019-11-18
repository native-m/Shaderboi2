#include "GuiBufferView.h"
#include "glad/glad.h"
#include "../Buffer.h"
#include "SDL.h"

GuiBufferView::GuiBufferView(int w, int h)
	: width(w), height(h), buf(nullptr)
{
}

void GuiBufferView::SetBuffer(Buffer* buffer)
{
	buf = buffer;
	buf->SetFramebufferSize(width, height);
}

void GuiBufferView::Draw()
{
	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImVec2 contentSize = ImVec2((float)width + 4.f, (float)height + 4.f);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(2.0f, 2.0f));

	if (drawList && ImGui::BeginChild("BufferCanvas", contentSize, true))
	{
		ImVec2 p = ImGui::GetCursorScreenPos();
		ImVec2 max = ImGui::GetWindowContentRegionMax();

		drawList->AddRect(p, ImVec2(p.x + (float)width, p.y + (float)height), ImColor());
		drawList->AddImage((ImTextureID)buf->GetFramebufferTexture(), p, ImVec2(p.x + (float)width, p.y + (float)height));
		ImGui::EndChild();
	}

	ImGui::PopStyleVar();
}
