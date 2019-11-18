#include "Shaderboi.h"
#include "GUI/CodeEditor.h"
#include "SDL.h"
#include <iostream>

const char* defaultShader =
"void mainImage(in vec2 fragCoord, out vec4 fragColor)\r\n"
"{\r\n"
"	vec2 uv = fragCoord / iResolution.xy;\r\n"
"	fragColor = vec4(uv.x, uv.y, 0.0, 1.0);\r\n"
"}\r\n";

Shaderboi::Shaderboi()
	: mainBuffer(new Buffer()), time(0), deltaTime(0.0), elapsedTime(0.0), pause(false)
{
	SetMainShaderStr(defaultShader);
	CompileMainShader();
}

Shaderboi::~Shaderboi()
{
	for (auto b : buffers)
		delete b;
}

void Shaderboi::SetMainShaderStr(const std::string& str)
{
	mainShader = str;
}

bool Shaderboi::CompileMainShader()
{
	bool ret = mainBuffer->CompileShader(mainShader.c_str(), mainShader.length(), mainShaderMsg);

	if (ret && pause)
		RenderBuffer();

	return ret;
}

void Shaderboi::SetElapsedTime(double elapsed)
{
	elapsedTime = elapsed;
	if (pause)
		RenderBuffer();
}

void Shaderboi::SetPaused(bool shouldPause)
{
	pause = shouldPause;
	time = 0;
	deltaTime = 0.0;
}

void Shaderboi::ProcessEvent(SDL_UserEvent* event)
{
	switch (event->code)
	{
	case Event::SB_COMPILESHADER:
		CodeEditor* editor = reinterpret_cast<CodeEditor*>(event->data1);
		GuiButton* compileBtn = reinterpret_cast<GuiButton*>(event->data2);

		if (editor->GetAssociatedBuffer() == 0)
		{
			SetMainShaderStr(editor->GetTextEditor().GetText());
			CompileMainShader();

			compileBtn->SetText("Compile");
			compileBtn->SetEnable(true);
		}
		else
		{
			// TODO: Compile shader for other buffers
		}

		break;
	}
}

void Shaderboi::AddBuffer()
{
	buffers.push_back(new Buffer());
}

void Shaderboi::UpdateTime()
{
	uint64_t frequency = SDL_GetPerformanceFrequency();
	uint64_t currentTime = SDL_GetPerformanceCounter();
	deltaTime = time > 0 ? (double)(currentTime - time) / frequency : 1.0 / 60.0;
	time = currentTime;
	elapsedTime += deltaTime;

	if (elapsedTime > 8388607.0)
		elapsedTime = 0.0;
}

void Shaderboi::RenderBuffer()
{
	mainBuffer->Draw((float)elapsedTime, (float)deltaTime);
}

Shaderboi* Shaderboi::CreateInstance()
{
	return new Shaderboi();
}
