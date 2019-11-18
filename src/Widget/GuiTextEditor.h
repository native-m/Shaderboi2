#pragma once
#include "GuiComponent.h"
#include "TextEditor.h"
#include <string>

class GuiTextEditor : public GuiComponent
{
public:
	struct Listener
	{
		virtual void OnTextEditorChangedListener(GuiTextEditor* textEditor) { }
	};

public:
	GuiTextEditor(const TextEditor::LanguageDefinition& languageDef = TextEditor::LanguageDefinition());

	// Setter
	void SetLanguageDefinition(const TextEditor::LanguageDefinition& languageDef) { editor.SetLanguageDefinition(languageDef); }
	void SetText(const std::string& text) { editor.SetText(text); }
	void SetReadOnly(bool readOnly) { editor.SetReadOnly(readOnly); }
	void AddListener(Listener* listener) { this->listener = listener; }

	// Getter
	std::string GetText() { return editor.GetText(); }

	void Draw() override;

private:
	TextEditor editor;
	Listener* listener;
};
