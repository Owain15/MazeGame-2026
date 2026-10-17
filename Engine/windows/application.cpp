
#include "application.h"

namespace Engine::Windows
{
	Application::Application()
		: m_Window(L"MazeGame", 1280, 720), m_Running(true)
	{
	}

	Application::~Application()
	{}

	void Application::Run()
	{
		while (m_Running)
		{
			if (!m_Window.ProcessMessages())
			{
				m_Running = false;
			}
			// Your game engine / application logic goes here
			// (e.g., m_Window.GetHandle() can be passed to DirectX or Vulkan)
			Sleep(16); // Simple cap to ~60fps for testing
		}
	}
}