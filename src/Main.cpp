#define SDL_MAIN_HANDLED

#include <SDL.h>
#include "imgui.h"
#include "misc/freetype/imgui_freetype.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "Main.h"
#include "Shaderboi.h"
#include "GUI/MainGui.h"
#include <cstdio>
#include <iostream>

Shaderboi* gInstance = nullptr;
MainGui* gMainGUI = nullptr;
ImFont* gMainFont = nullptr;
ImFont* gEditorFont = nullptr;

int main(int argc, const char* argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS) != 0)
	{
		std::printf("Error: %s\n", SDL_GetError());
		return -1;
	}

	// Set GL & GLSL Version
	const char* glslVersion = "#version 150";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// Setup buffer
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	// Create window and smash GL context
	SDL_WindowFlags winFlags = (SDL_WindowFlags)((SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI));
	SDL_Window* window = SDL_CreateWindow("Shaderboi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, winFlags);
	SDL_GLContext glctx = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, glctx);
	SDL_GL_SetSwapInterval(1); // Enable vsync

	bool err = gladLoadGL() == 0;

	if (err)
	{
		std::fprintf(stderr, "Failed to initialize OpenGL loader!\n");
		return 1;
	}

	gInstance = Shaderboi::CreateInstance();
#ifdef _DEBUG
	assert(gInstance != nullptr);
#endif

	gMainGUI = new MainGui();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.IniFilename = nullptr;

	unsigned int fontBuilderFlags = ImGuiFreeType::NoAutoHint;

	gMainFont = io.Fonts->AddFontFromFileTTF("res/Roboto-Regular.ttf", 15);
	gEditorFont = io.Fonts->AddFontFromFileTTF("res/RobotoMono-Regular.ttf", 16);
	ImGuiFreeType::BuildFontAtlas(io.Fonts, fontBuilderFlags);

	ImGui::StyleColorsDark();
	style.WindowBorderSize = 0.0f;
	style.WindowRounding = 4.0f;

	ImGui_ImplSDL2_InitForOpenGL(window, glctx);
	ImGui_ImplOpenGL3_Init(glslVersion);

	static char buf[1024];

	bool done = false;
	while (!done)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:
				done = true;
				break;
			case SDL_USEREVENT:
				gInstance->ProcessEvent(&event.user);
				break;
			}

			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED && event.window.windowID == SDL_GetWindowID(window))
			{
				int w, h;
				SDL_GetWindowSize(window, &w, &h);
				//testbuffer.SetFramebufferSize(w, h);
			}

			else if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
				done = true;

			ImGui_ImplSDL2_ProcessEvent(&event);
		}

		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplSDL2_NewFrame(window);
		ImGui::NewFrame();

		ImGui::PushFont(gMainFont);

		gMainGUI->Draw();

		ImGui::PopFont();

		ImGui::Render();
		glViewport(0, 0, 1280, 720);
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if(!gInstance->IsPaused())
		{
			gInstance->UpdateTime();
			gInstance->RenderBuffer();
		}

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		SDL_GL_SwapWindow(window);
	}

	delete gMainGUI;
	delete gInstance;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	SDL_GL_DeleteContext(glctx);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
