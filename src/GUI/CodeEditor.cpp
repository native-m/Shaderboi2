#include "CodeEditor.h"
#include "../Main.h"
#include "../Shaderboi.h"
#include "SDL.h"
#include <iostream>

CodeEditor::CodeEditor(const char* editorLabel)
	: GuiWindow("Editor", false, ImGuiWindowFlags_MenuBar),
	editorLabel(std::string("Editor - ") + editorLabel)
{
	// Init menu
	editorBar.AddItem(0, "File", &fileMenuItem);
	editorBar.AddItem(1, "Edit", &editMenuItem);
	editorBar.AddItem(2, "View", &viewMenuItem);

	fileMenuItem.AddListener(this);
	fileMenuItem.AddItem(MENU_OPEN, "Open");
	fileMenuItem.AddItem(MENU_SAVE, "Save");
	fileMenuItem.AddSeparator();
	fileMenuItem.AddItem(MENU_CLOSE, "Close");

	compileBtn.AddListener(this);
	compileBtn.SetText("Compile");

	autocompileChkbox.SetLabel("Auto-compile");

	glslLang.reset(new TextEditor::LanguageDefinition(TextEditor::LanguageDefinition::GLSL()));
	InitGLSLKeyword(*glslLang);

	textEditor.AddListener(this);
	textEditor.SetLanguageDefinition(*glslLang);

	// auto-compile callback function
	auto textEditorTimerCallback = [this](uint32_t interval, void* data) {
		SDL_Event event;
		SDL_UserEvent userEvent;

		// We can't compile shader asynchronously in separate thread..
		// So we have to throw it back to the main thread.. :(
		userEvent.type = SDL_USEREVENT;
		userEvent.code = Shaderboi::Event::SB_COMPILESHADER;
		userEvent.data1 = reinterpret_cast<void*>(this); // We send this editor.
		userEvent.data2 = reinterpret_cast<void*>(&compileBtn); // We also have to send the compile button.

		event.type = SDL_USEREVENT;
		event.user = userEvent;

		SDL_PushEvent(&event);
	};

	textEditorTimer.SetCallbackFunction(textEditorTimerCallback);

	AddComponent(&editorBar);
	SameLine();
	AddComponent(&compileBtn);
	AddComponent(&autocompileChkbox);
	EndSameLine();
	AddComponent(&textEditor);

	SetTitle(this->editorLabel.c_str());
	SetSize(640, 300);
}

void CodeEditor::SetAssociatedBuffer(int num)
{
	assocBuffer = num;
}

void CodeEditor::SetLabel(const char* newLabel)
{
	editorLabel = std::string("Editor - ") + newLabel;
	SetTitle(editorLabel.c_str());
}

void CodeEditor::SetText(const std::string& newText)
{
	textEditor.SetText(newText);
}

void CodeEditor::OnMenuItem(unsigned int id, const GuiMenuItem::MenuItem& item)
{
	switch (id)
	{
	case MENU_CLOSE:
		SetOpen(false);
		break;
	}
}

void CodeEditor::OnButtonClickListener(GuiButton* btn)
{
	if (btn == &compileBtn)
	{
		if (assocBuffer == 0)
		{
			gInstance->SetMainShaderStr(textEditor.GetText());
			gInstance->CompileMainShader();
		}
	}
}

void CodeEditor::OnTextEditorChangedListener(GuiTextEditor* textEditor)
{
	if (textEditor == &this->textEditor && autocompileChkbox.IsChecked())
	{
		compileBtn.SetEnable(false);
		compileBtn.SetText("Compiling...");

		if (textEditorTimer.GetTimerID())
			textEditorTimer.StopTimer();

		textEditorTimer.StartTimer(500);
	}
}

void CodeEditor::InitGLSLKeyword(TextEditor::LanguageDefinition& langDef)
{
	static const char* keywords[] = {
		"vec2", "vec3", "vec4",
		"dvec2", "dvec3", "dvec4",
		"ivec2", "ivec3", "ivec4",
		"uvec2", "uvec3", "uvec4",
		"in", "out"
	};

	for (auto& key : keywords)
		langDef.mKeywords.insert(key);
}
