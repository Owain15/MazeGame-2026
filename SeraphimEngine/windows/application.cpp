
#include "application.h"	


#include "logging.h"
#include "core/events_dispatcher.h"
#include "core/events_window.h"
#include "core/events_keybord.h"

#include <thread>
#include <chrono>

namespace SeraphimEngine::Windows
{
	Application::Application(SeraphimEngine::Object& player, SeraphimEngine::Object& testObject)
		: m_Window(L"MazeGame", 1280, 720), 
		m_Renderer(m_Window.GetHandle()),
		m_Camera(SeraphimEngine::Camera2D()),
		m_Running(true),
		m_Paused(false),
		m_Minimized(false),
		m_Player(player),
		m_Object(testObject)
	{
		Logging::Init();
		Seraphim_Log_CORE_INFO("Logging Initialized Subsystem Successfully.");

		m_Window.SetEventCallback([this](SeraphimEngine::Events::Event& event)
			{	OnEvent(event);});

	}

	Application::~Application()
	{}

	void Application::Run()
	{
		using Clock = std::chrono::steady_clock;
		auto previousFrame = Clock::now();
		constexpr auto targetFrameTime = std::chrono::duration<double>(1.0 / 60.0);

		while (m_Running)
		{
			// cache time for start of game loop cycle 
			const auto frameStart = Clock::now();
			const float deltaTime = std::chrono::duration<float>(frameStart - previousFrame).count();
			previousFrame = frameStart; // Advance even while paused/minimized.

			if (!m_Window.ProcessMessages() || !m_Running)
			{ break; }


			if (!m_Paused && !m_Minimized)
			{
				UpdateGameState(deltaTime);

				Render();
			}

			//calculte fame time, delay next cylecel if needed
			const auto workTime = Clock::now() - frameStart;
			if (workTime < targetFrameTime)
				std::this_thread::sleep_for(targetFrameTime - workTime);
		}
	}

	void Application::OnEvent(SeraphimEngine::Events::Event& event)
	{
		SeraphimEngine::Events::EventDispatcher dispatcher(event);

		dispatcher.Dispatch<SeraphimEngine::Events::Window::Resize>(
			[this](SeraphimEngine::Events::Window::Resize& resize)
			{

				if (m_Minimized)
				{
					m_Minimized = false;
					Seraphim_Log_CORE_INFO("Window restored - game loop updating {}", (m_Paused) ? "still paused" : "resumed");
				}
				
				Seraphim_Log_CORE_INFO(
					"Window resized to {}x{}",
					resize.GetWidth(),
					resize.GetHeight());
				return false;
			});

		dispatcher.Dispatch<SeraphimEngine::Events::Window::Close>(
			[this](SeraphimEngine::Events::Window::Close& close)
			{
				Seraphim_Log_CORE_INFO(close.GetName());
				m_Running = false;
				return true;
			});

		dispatcher.Dispatch<SeraphimEngine::Events::Window::Minimized>(
			[this](auto& minimized)
			{
				Seraphim_Log_CORE_INFO("{} - pausing game loop update.", minimized.GetName());
				m_Minimized = true;
				return true;
			});

		dispatcher.Dispatch<SeraphimEngine::Events::Keyboard::KeyPressed>(
			[this](SeraphimEngine::Events::Keyboard::KeyPressed& keyPressed)
			{
				Seraphim_Log_CORE_INFO(
					"{} - keycode: {}",
					keyPressed.GetName(),
					keyPressed.GetKeycode());

				switch (keyPressed.GetKeycode())
				{
					// Up arrow
					case 38: 
					{ m_Inputs.Up    = true; break; }
					// Down arrow
					case 40: 
					{ m_Inputs.Down  = true; break; }
					// Left arrow
					case 37: 
					{ m_Inputs.Left  = true; break; }
					// Right arrow
					case 39: 
					{ m_Inputs.Right = true; break; }

				}

				return false;
			});

		dispatcher.Dispatch<SeraphimEngine::Events::Keyboard::KeyReleased>(
			[this](SeraphimEngine::Events::Keyboard::KeyReleased& keyReleased)
			{
				Seraphim_Log_CORE_INFO(
					"{} - keycode: {}",
					keyReleased.GetName(),
					keyReleased.GetKeycode());


				switch (keyReleased.GetKeycode())
				{
					// Up arrow
					case 38:
					{ m_Inputs.Up    = false; break; }
					// Down arrow
					case 40:
					{ m_Inputs.Down  = false; break; }
					// Left arrow
					case 37:
					{ m_Inputs.Left  = false; break; }
					// Right arrow
					case 39:
					{ m_Inputs.Right = false; break; }
				}
				
				return false;
			});

	}

	void Application::UpdateGameState(const float deltaTime)
	{
		m_Player.Update(deltaTime);
		m_Object.Update(deltaTime);

		//// //// temerary movement logic for player object
		if (m_Inputs.Up)
		{
			const auto playerRect = m_Player.GetRect();
			m_Player.SetPosition(playerRect.x, playerRect.y - 100.0f * deltaTime);
		}
		if (m_Inputs.Down)
		{
			const auto playerRect = m_Player.GetRect();
			m_Player.SetPosition(playerRect.x, playerRect.y + 100.0f * deltaTime);
		}
		if (m_Inputs.Left)
		{
			const auto playerRect = m_Player.GetRect();
			m_Player.SetPosition(playerRect.x - 100.0f * deltaTime, playerRect.y);
		}
		if (m_Inputs.Right)
		{
			const auto playerRect = m_Player.GetRect();
			m_Player.SetPosition(playerRect.x + 100.0f * deltaTime, playerRect.y);
		}

		//// ////
	}

	void Application::Render()
	{
		m_Renderer.BeginFrame({ 0.1f, 0.1f, 0.1f, 1.0f }, m_Camera);
		//m_Renderer.DrawRect({ 100.0f, 100.0f, 200.0f, 150.0f }, { 1.0f, 0.0f, 0.0f, 1.0f });
		//m_Renderer.DrawRect({ 400.0f, 200.0f, 50.0f, 50.0f }, { 0.0f, 1.0f, 1.0f, 1.0f });
		m_Renderer.DrawObject(m_Object);
		m_Renderer.DrawObject(m_Player);
		m_Renderer.EndFrame();
	}

}