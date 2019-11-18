#include "Buffer.h"
#include "imgui.h"
#include <iostream>

// vertex data
const float Buffer::verts[] = {
	-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
	 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
	 1.0f,-1.0f, 0.0f, 1.0f, 0.0f,
	-1.0f,-1.0f, 0.0f, 0.0f, 0.0f
};

const unsigned int Buffer::index[] = {
	0, 2, 3,
	1, 2, 0
};

const char* Buffer::vertexShader =
"#version 150\n"
"in vec3 in_pos;"
"in vec2 in_uv;"
"uniform vec2 maxRes;"
"out vec2 sb_gl_frgcoord;"
"void main() {"
"\tgl_Position = vec4(in_pos, 1.0);"
"\tsb_gl_frgcoord = in_uv;"
"}";

const char* Buffer::fragmentShaderTest =
"#version 150\n"
"in vec4 iResolution;"
"out vec4 color;"
"void main() {"
"\tvec3 col = vec3(sin(length(uv) * 100.));"
"\tcolor = vec4(col, 1.0);"
"}";

const char* shaderHeader =
"#version 150\n"
"uniform vec4 iResolution;"
"uniform float iTime;"
"uniform float iDeltaTime;"
"in vec2 sb_gl_frgcoord;"
"out vec4 sb_gl_frgcolor;"
"void mainImage(in vec2 fragCoord, out vec4 fragColor);"
"void main() {"
"\tvec4 color;"
"\tmainImage(sb_gl_frgcoord * iResolution.xy, color);"
"\tsb_gl_frgcolor = color;"
"}";

Buffer::Buffer()
	: vs(0), fs(0), program(0)
{
	Initialize();
}

Buffer::~Buffer()
{
	// Delete framebuffer data
	glDeleteFramebuffers(1, &fbo);
	glDeleteTextures(1, &fboTex);
	glDeleteRenderbuffers(1, &rboTex);

	// Delete vertex resources
	glDeleteBuffers(1, &idx);
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);

	// Delete shaders
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteProgram(program);
}

bool Buffer::CompileShader(const char* shader, int length, Buffer::ShaderMessages& msg)
{
	int nv, nf, np;
	GLint vertexStatus;
	GLint fragmentStatus;
	GLint infoLen;
	GLchar* str;
	std::string strShader = std::string(shaderHeader) + shader + '\0';

	nv = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(nv, 1, (const GLchar**)&Buffer::vertexShader, nullptr);
	glCompileShader(nv);
	glGetShaderiv(nv, GL_COMPILE_STATUS, &vertexStatus);

	if(!vertexStatus)
	{
		char msg[256];
		glGetShaderInfoLog(nv, 256, &infoLen, msg);
		std::cout << msg << std::endl;
		assert(vertexStatus != GL_FALSE);
	}

	char* s = new char[strShader.length()];
	memset(s, 0, strShader.length());
	memcpy(s, strShader.c_str(), strShader.length());
	nf = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(nf, 1, &s, nullptr);
	glCompileShader(nf);
	glGetShaderiv(nf, GL_COMPILE_STATUS, &fragmentStatus);
	delete[] s;

	// vibe check
	if (!fragmentStatus)
	{
		glGetShaderiv(nf, GL_INFO_LOG_LENGTH, &infoLen);
		str = new GLchar[infoLen];
		glGetShaderInfoLog(nf, infoLen, &infoLen, str);
		msg.messages = str;
		msg.status = 2;
		std::cout << str << std::endl;
		glDeleteShader(nv);
		delete[] str;
		return false;
	}

	np = glCreateProgram();
	glAttachShader(np, nv);
	glAttachShader(np, nf);
	glBindAttribLocation(np, 0, "in_pos");
	glBindAttribLocation(np, 1, "in_uv");
	glLinkProgram(np);

	if (!np)
	{
		msg.messages = "Cannot create program";
		msg.status = 2;
		std::cout << "Cannot create program" << std::endl;
		glDeleteShader(nv);
		glDeleteShader(nf);
		return false;
	}

	if (vs)
		glDeleteShader(vs);

	if (fs)
		glDeleteShader(fs);

	if (program)
		glDeleteShader(program);

	program = np;
	vs = nv;
	fs = nf;

	glUseProgram(program);
	resolution = glGetUniformLocation(program, "iResolution");
	time = glGetUniformLocation(program, "iTime");
	delta = glGetUniformLocation(program, "iDeltaTime");
	glUseProgram(0);

	return true;
}

void Buffer::SetFramebufferSize(int w, int h)
{
	if (w != fbWidth || h != fbHeight)
	{
		fbWidth = w;
		fbHeight = h;

		glBindTexture(GL_TEXTURE_2D, fboTex);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fbWidth, fbHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindRenderbuffer(GL_RENDERBUFFER, rboTex);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, fbWidth, fbHeight);
		glBindRenderbuffer(GL_RENDERBUFFER, 0);
	}
}

void Buffer::Draw(float elapsedTime, float deltaTime)
{
	GLint depthTest = glIsEnabled(GL_DEPTH_TEST);
	GLint lastViewport[4];
	glGetIntegerv(GL_VIEWPORT, lastViewport);

	glViewport(0, 0, fbWidth, fbHeight);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	glUseProgram(program);

	glUniform4f(resolution, (float)fbWidth, (float)fbHeight, 0.f, 0.0f);
	glUniform1f(time, elapsedTime);
	glUniform1f(delta, deltaTime);

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
	glUseProgram(0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	if (!depthTest) glDisable(GL_DEPTH_TEST);
	glViewport(lastViewport[0], lastViewport[1], lastViewport[2], lastViewport[3]);
}

void Buffer::Initialize()
{
	// Create framebuffer
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	glGenTextures(1, &fboTex);
	glBindTexture(GL_TEXTURE_2D, fboTex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, fbWidth, fbHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, fboTex, 0);

	glGenRenderbuffers(1, &rboTex);
	glBindRenderbuffer(GL_RENDERBUFFER, rboTex);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, fbWidth, fbHeight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboTex);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Create an vertex array
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create vertex buffer object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Upload buffer data
	glBufferData(GL_ARRAY_BUFFER, sizeof(Buffer::verts), (void*)Buffer::verts, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glGenBuffers(1, &idx);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Buffer::index), (void*)Buffer::index, GL_STATIC_DRAW);

	glBindVertexArray(0);
}
