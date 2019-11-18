#pragma once
#include "glad/glad.h"
#include <string>

class Buffer
{
public:
	struct ShaderMessages
	{
		// Compile status
		// 0: No error
		// 1: Warning
		// 2: Error
		// 3: Warning + Error
		int status;

		// Warning/Error messages
		std::string messages;
	};

public:
	Buffer();
	~Buffer();

	bool CompileShader(const char* shader, int length, Buffer::ShaderMessages& msg);
	void SetFramebufferSize(int w, int h);
	unsigned int GetFramebufferTexture() { return fboTex; };

	void Draw(float elapsedTime, float deltaTime);

private:
	void Initialize();

private:
	unsigned int fboTex, fbo, rboTex, rbo;
	unsigned int vao, vbo, idx;
	unsigned int vs, fs, program;
	int fbWidth = 128, fbHeight = 128;

	// uniforms
	unsigned int resolution;
	unsigned int time;
	unsigned int delta;

	static const float verts[];
	static const unsigned int index[];
	static const char* vertexShader;
	static const char* fragmentShaderTest;
};
