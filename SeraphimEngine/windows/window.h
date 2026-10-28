
#pragma once

#include <Windows.h>
#include <functional>
#include "core/events.h"
#include "core/events_window.h"

namespace SeraphimEngine::Windows
{
	class Window
	{
		public:
			
			Window(const wchar_t* title, int width, int height);
			~Window();
		
			bool ProcessMessages();
	
			HWND GetHandle() const;
		
			using EventCallback = std::function<void(SeraphimEngine::Events::Event&)>;
			
			void SetEventCallback(EventCallback callback);

			SeraphimEngine::Events::Window::ResizeEvent GetResizeEvent() const;

		private:

			static LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

			HWND m_Handle = nullptr;
			EventCallback m_EventCallback;
	};
}