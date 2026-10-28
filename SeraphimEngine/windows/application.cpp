
#include "application.h"	


#include "logging.h"
#include "core/events_dispatcher.h"
#include "core/events_window.h"

namespace SeraphimEngine::Windows
{
	Application::Application()
		: m_Window(L"MazeGame", 1280, 720), m_Running(true)
	{
		Logging::Init();
		Seraphim_Log_CORE_INFO("Logging Initialized Subsystem Successfully.");

		m_Window.SetEventCallback([](SeraphimEngine::Events::Event& event)
			{
				SeraphimEngine::Events::EventDispatcher dispatcher(event);

				dispatcher.Dispatch<SeraphimEngine::Events::Window::ResizeEvent>(
					[](SeraphimEngine::Events::Window::ResizeEvent& resize)
					{
						Seraphim_Log_CORE_INFO(
							"Window resized to {}x{}",
							resize.GetWidth(),
							resize.GetHeight());
						return false;
					});
			});


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