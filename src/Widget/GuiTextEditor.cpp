#include "GuiTextEditor.h"
#include "../Main.h"

GuiTextEditor::GuiTextEditor(const TextEditor::LanguageDefinition& languageDef)
	: listener(nullptr)
{
	static TextEditor::Palette p = TextEditor::GetDarkPalette();

	p[(int)TextEditor::PaletteIndex::Background] = 0;
	p[(int)TextEditor::PaletteIndex::Identifier] = 0xffc0c0c0;

	editor.SetHandleMouseInputs(true);
	editor.SetHandleKeyboardInputs(true);
	editor.SetLanguageDefinition(languageDef);
	editor.SetReadOnly(false);
	editor.SetPalette(p);
}

void GuiTextEditor::Draw()
{
	ImGui::PushFont(gEditorFont);

	editor.Render("Editor");

	if (editor.IsTextChanged() && listener)
		listener->OnTextEditorChangedListener(this);

	ImGui::PopFont();
}
