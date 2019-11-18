#pragma once
#include "../Widget/GuiWindow.h"
#include "../Widget/GuiMenuBar.h"
#include "../Widget/GuiTextEditor.h"
#include "../Widget/GuiButton.h"
#include "../Widget/GuiCheckbox.h"
#include "../TimerFunction.h"

class CodeEditor : public GuiWindow, GuiMenuItem::Listener, GuiButton::Listener, GuiTextEditor::Listener
{
	enum CodeEditorMenu
	{
		MENU_OPEN,
		MENU_SAVE,
		MENU_CLOSE,
		MENU_UNDO,
		MENU_REDO,
		MENU_COPY,
		MENU_CUT,
		MENU_DELETE,
		MENU_PASTE,
		MENU_SELECTALL
	};

public:
	CodeEditor(const char* editorLabel = nullptr);

	void SetAssociatedBuffer(int num);
	void SetLabel(const char* newLabel);
	void SetText(const std::string& newText);
	int GetAssociatedBuffer() { return assocBuffer; }
	GuiTextEditor& GetTextEditor() { return textEditor; }
	int GetTimerID() { return textEditorTimerID; }

	void OnMenuItem(unsigned int id, const GuiMenuItem::MenuItem& item) override;
	void OnButtonClickListener(GuiButton* btn) override;
	void OnTextEditorChangedListener(GuiTextEditor* textEditor) override;

	static void InitGLSLKeyword(TextEditor::LanguageDefinition& langDef);

private:
	std::string editorLabel;
	GuiMenuBar editorBar;
	GuiMenuItem fileMenuItem;
	GuiMenuItem editMenuItem;
	GuiMenuItem viewMenuItem;
	GuiButton compileBtn;
	GuiCheckbox autocompileChkbox;
	GuiTextEditor textEditor;

	int assocBuffer;
	int textEditorTimerID;

	std::unique_ptr<TextEditor::LanguageDefinition> glslLang;
	TimerFunction textEditorTimer;
};
