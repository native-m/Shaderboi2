#include "GlobalUniform.h"
#include "../Main.h"
#include "../Shaderboi.h"

GlobalUniform::GlobalUniform()
	: GuiWindow("Global Uniform")
{
	timerPause.SetText("| |");
	timerReset.SetText("Reset");
	timerEdit.SetLabel("iTime");
	deltaTimeEdit.SetLabel("iDeltaTime");
	deltaTimeEdit.SetFlags(ImGuiInputTextFlags_ReadOnly);

	// Set listener
	timerPause.AddListener(this);
	timerReset.AddListener(this);
	timerEdit.AddListener(this);

	SameLine();
	AddComponent(&timerPause);
	AddComponent(&timerReset);
	EndSameLine();
	AddComponent(&timerEdit);
	AddComponent(&deltaTimeEdit);

	SetSize(228, 300);
	SetPosition(700, 50);
}

void GlobalUniform::OnButtonClickListener(GuiButton* btn)
{
	if (btn == &timerReset)
		gInstance->SetElapsedTime(0.0);
	else if (btn == &timerPause)
	{
		if (!gInstance->IsPaused())
		{
			gInstance->SetPaused(true);
			timerPause.SetText(">");
		}
		else
		{
			gInstance->SetPaused(false);
			timerPause.SetText("| |");
		}
	}
}

void GlobalUniform::OnInputDoubleChanged(GuiInputDouble* input)
{
	if (input == &timerEdit)
		gInstance->SetElapsedTime(input->GetValue());
}

void GlobalUniform::Draw()
{
	// Seems inefficient tho..
	// Do you guys have another idea for this?
	if (!timerEdit.IsActive()) // This thing seems useless, timerEdit will stop updating if it is in active (editing) state
		timerEdit.SetValue(gInstance->GetElapsedTime());

	deltaTimeEdit.SetValue(gInstance->GetDeltaTime());

	GuiWindow::Draw();
}
