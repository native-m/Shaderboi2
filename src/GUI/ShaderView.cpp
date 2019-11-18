#include "ShaderView.h"
#include "../Main.h"
#include "../Shaderboi.h"

ShaderView::ShaderView()
	: GuiWindow("Shader View"), bufView(640, 360)
{
	Buffer* buf = gInstance->GetMainBuffer();

	tabs.SetID("TabGroup");

	bufView.SetBuffer(buf);

	mainBufferTab.SetTitle("Main Buffer");
	mainBufferTab.AddComponent(&bufView);

	tabs.AddTab(&mainBufferTab);

	AddComponent(&tabs);

	//SetResizable(false);
	SetSize(640 + 16 + 4, 360 + 16 + 4 + 46);
	SetPosition(300, 50);
}
