
#pragma once

#include "renderer.h"

#include <EGL/egl.h>
#include <EGL/eglext.h>	
#include <EGL/eglext_angle.h>
#include <GLES3/gl3.h>

namespace SeraphimEngine::Windows
{
	std::string LoadTextFile(const char* path)
	{
		std::ifstream file(path, std::ios::binary);
		if (!file)
			throw std::runtime_error(std::string("Could not open file: ") + path);

		return std::string(
			std::istreambuf_iterator<char>(file),
			std::istreambuf_iterator<char>());
	}

	struct Renderer::GraphicsState
	{
		EGLDisplay display = EGL_NO_DISPLAY;
		EGLSurface surface = EGL_NO_SURFACE;
		EGLContext context = EGL_NO_CONTEXT;
		EGLConfig   config = EGL_NO_CONFIG_KHR;
		// Add ANGLE/GLES state variables here
		HWND window = nullptr;
		GLuint program = 0;
		GLuint vao = 0;
		GLuint vbo = 0;
	};

	Renderer::Renderer(HWND windowHandle)
		: m_State(std::make_unique<GraphicsState>())	
	{
		// Include EGL/egl.h and EGL/eglext_angle.h in renderer.cpp.

		const EGLAttrib displayAttributes[] = {
			EGL_PLATFORM_ANGLE_TYPE_ANGLE,
			EGL_PLATFORM_ANGLE_TYPE_D3D11_ANGLE,
			EGL_NONE
		};

		m_State->display = eglGetPlatformDisplay(
			EGL_PLATFORM_ANGLE_ANGLE, EGL_DEFAULT_DISPLAY, displayAttributes);

		eglInitialize(m_State->display, nullptr, nullptr);
		eglBindAPI(EGL_OPENGL_ES_API);

		const EGLint configAttributes[] = {
			EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
			EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
			EGL_RED_SIZE, 8,
			EGL_GREEN_SIZE, 8,
			EGL_BLUE_SIZE, 8,
			EGL_NONE
		};

		EGLint configCount = 0;

		if (eglChooseConfig(m_State->display, configAttributes,
			&m_State->config, 1, &configCount) != EGL_TRUE ||
			configCount == 0)
		{
			// Report the EGL error and stop initialization.
		}

		// Choose an EGLConfig with EGL_WINDOW_BIT and EGL_OPENGL_ES3_BIT.
		m_State->surface = eglCreateWindowSurface(
			m_State->display, m_State->config, windowHandle, nullptr);

		const EGLint contextAttributes[] = {
			EGL_CONTEXT_CLIENT_VERSION, 3,
			EGL_NONE
		};

		m_State->context = eglCreateContext(
			m_State->display, m_State->config, EGL_NO_CONTEXT, contextAttributes);

		// Create an ES 3 context, then:
		eglMakeCurrent(m_State->display, m_State->surface, m_State->surface, m_State->context);

		const std::string vertexSource = LoadTextFile("shaders/triangle.vert");
		const std::string fragmentSource = LoadTextFile("shaders/triangle.frag");

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		const char* vertexText = vertexSource.c_str();
		glShaderSource(vertexShader, 1, &vertexText, nullptr);
		glCompileShader(vertexShader);

		// Do the same for fragmentSource with GL_FRAGMENT_SHADER,
		// then link both compiled shaders into m_State->program.

		GLint compiled = GL_FALSE;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);

		if (compiled != GL_TRUE)
		{
			GLint logLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);

			std::string infoLog(logLength > 0 ? logLength : 1, '\0');
			GLsizei written = 0;
			glGetShaderInfoLog(vertexShader, static_cast<GLsizei>(infoLog.size()),
				&written, infoLog.data());
			infoLog.resize(written);

			OutputDebugStringA("Vertex shader compilation failed:\n");
			OutputDebugStringA(infoLog.c_str());
			OutputDebugStringA("\n");
		}
		else
		{
			OutputDebugStringA("Vertex shader compiled successfully.\n");
		}

		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		const char* fragmentText = fragmentSource.c_str();
		glShaderSource(fragmentShader, 1, &fragmentText, nullptr);
		glCompileShader(fragmentShader);

		GLint fragmentCompiled = GL_FALSE;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fragmentCompiled);

		if (fragmentCompiled != GL_TRUE)
		{
			GLint logLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);

			std::string infoLog(logLength > 0 ? logLength : 1, '\0');
			GLsizei written = 0;
			glGetShaderInfoLog(fragmentShader, static_cast<GLsizei>(infoLog.size()),
				&written, infoLog.data());
			infoLog.resize(written);

			OutputDebugStringA("Fragment shader compilation failed:\n");
			OutputDebugStringA(infoLog.c_str());
			OutputDebugStringA("\n");
		}
		else
		{
			OutputDebugStringA("Fragment shader compiled successfully.\n");
		}

		if (compiled == GL_TRUE && fragmentCompiled == GL_TRUE)
		{
			m_State->program = glCreateProgram();
			glAttachShader(m_State->program, vertexShader);
			glAttachShader(m_State->program, fragmentShader);
			glLinkProgram(m_State->program);

			GLint linked = GL_FALSE;
			glGetProgramiv(m_State->program, GL_LINK_STATUS, &linked);

			if (linked == GL_TRUE)
			{
				OutputDebugStringA("Shader program linked successfully.\n");
				const GLfloat vertices[] = {
				-0.6f, -0.6f,
				0.6f, -0.6f,
				 0.0f,  0.6f
				};

				glGenVertexArrays(1, &m_State->vao);
				glGenBuffers(1, &m_State->vbo);

				glBindVertexArray(m_State->vao);
				glBindBuffer(GL_ARRAY_BUFFER, m_State->vbo);
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
				glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
					2 * sizeof(GLfloat), nullptr);
				glEnableVertexAttribArray(0);

				glBindBuffer(GL_ARRAY_BUFFER, 0);
				glBindVertexArray(0);
			}
			else
			{
				GLint logLength = 0;
				glGetProgramiv(m_State->program, GL_INFO_LOG_LENGTH, &logLength);

				std::string infoLog(logLength > 0 ? logLength : 1, '\0');
				GLsizei written = 0;
				glGetProgramInfoLog(m_State->program,
					static_cast<GLsizei>(infoLog.size()), &written, infoLog.data());
				infoLog.resize(written);

				OutputDebugStringA("Shader program link failed:\n");
				OutputDebugStringA(infoLog.c_str());
				OutputDebugStringA("\n");
			}
		}
	}

	Renderer::~Renderer()
	{
		// Clean up EGL context and resources
		if (m_State->context != EGL_NO_CONTEXT)
		{
			eglDestroyContext(m_State->display, m_State->context);
		}
		if (m_State->surface != EGL_NO_SURFACE)
		{
			eglDestroySurface(m_State->display, m_State->surface);
		}
		if (m_State->display != EGL_NO_DISPLAY)
		{
			eglTerminate(m_State->display);
		}
	}

	void Renderer::DrawTriangle()
	{
		EGLint width = 0;
		EGLint height = 0;

		eglQuerySurface(m_State->display, m_State->surface, EGL_WIDTH, &width);
		eglQuerySurface(m_State->display, m_State->surface, EGL_HEIGHT, &height);

		glViewport(0, 0, width, height);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		

		glUseProgram(m_State->program);
		glBindVertexArray(m_State->vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
		
		
		
		eglSwapBuffers(m_State->display, m_State->surface);
	
	}

}