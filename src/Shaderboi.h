#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Buffer.h"

struct SDL_UserEvent;

class Shaderboi
{
public:
	typedef struct
	{
		std::string name;
		Buffer* buffer;
	} BufferDesc;

	enum Event
	{
		SB_COMPILESHADER
	};

public:
	Shaderboi();
	~Shaderboi();

	void SetMainShaderStr(const std::string& str);
	void SetElapsedTime(double elapsed);
	void SetPaused(bool shouldPause);
	void ProcessEvent(SDL_UserEvent* event);
	bool CompileMainShader();
	void AddBuffer();
	void UpdateTime();
	void RenderBuffer();

	std::string& GetMainShader() { return mainShader; }
	Buffer* GetMainBuffer() { return mainBuffer.get(); }
	Buffer* GetBuffer(int i) { return buffers[i]; }
	std::vector<Buffer*> GetAllBuffer() { return buffers; }
	const double& GetElapsedTime() const { return elapsedTime; }
	const double& GetDeltaTime() const { return deltaTime; }
	bool IsPaused() { return pause; }

	static Shaderboi* CreateInstance();

private:
	std::unique_ptr<Buffer> mainBuffer;
	std::vector<Buffer*> buffers;
	std::string mainShader;
	Buffer::ShaderMessages mainShaderMsg;

	bool pause;
	uint64_t time;
	double deltaTime;
	double elapsedTime;
};
