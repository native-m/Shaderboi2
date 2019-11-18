#pragma once
#include <list>
#include <memory>
#include <string>
#include "GuiComponent.h"
#include "imgui.h"

class GuiWindow : public GuiComponent
{
	enum DrawMode
	{
		// probably will add another mode...
		DRAW_COMPONENT,
		DRAW_TEXT,
		DRAW_TEXTFORMATTED,
		DRAW_SEPARATOR,
		DRAW_SAMELINE,
		DRAW_ENDSAMELINE,
		DRAW_BULLET,
		DRAW_ENDBULLET
	};

	typedef struct
	{
		float offsetX;
		float spacing;
	} SameLine_Data;

	struct DrawItem
	{
		DrawMode drawMode;
		GuiComponent* components = nullptr;
		const char* text;
		bool wrappedText;

		union
		{
			SameLine_Data sameLine;
		};

		DrawItem() {}
		~DrawItem() {}
	};

public:
	GuiWindow(const char* name = nullptr, bool shouldOpen = true, ImGuiWindowFlags windowFlags = 0);
	~GuiWindow();

	void AddComponent(GuiComponent* component);
	void AddText(const char* text, bool wrapped = false);
	void AddTextFormatted(bool wrapping, const char* fmt, ...);
	void AddSeparator();
	void SetSize(float x, float y);
	void SetPosition(float x, float y);
	void SetTitle(const char* title);
	void SetResizable(bool isResizable);
	void SetOpen(bool shouldOpen);

	bool IsOpen() { return open; }

	void SameLine(float offsetX = 0.0f, float spacing = 0.0f);
	void EndSameLine();

	void Bullet();
	void EndBullet();

	virtual bool BeginDraw(const char* name, bool* pOpen, ImGuiWindowFlags windowFlags) { return ImGui::Begin(name, pOpen, windowFlags); }
	virtual void EndDraw() { ImGui::End(); }
	void Draw() override;
	void DrawComponent();

public:
	std::list<DrawItem*> drawList;
	ImVec2 size, pos;
	const char* name;
	bool open;
	bool preSized = false;
	ImGuiWindowFlags windowFlags = 0;
};
