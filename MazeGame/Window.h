#pragma once

#include <Windows.h>	
#include <string>


namespace Engine
{
	class Window
	{
		// Properties
		public:

		protected:

			HWND m_hwnd = nullptr;
			HINSTANCE m_hInstance = nullptr;
			std::wstring m_className;


		// Methods
		public:

			Window(const std::wstring& title, int width, int height);
			~Window();

			// Prevent copying to avoid multiple objects managing the same window handle
			Window(const Window&) = delete;
			Window& operator=(const Window&) = delete;

			bool ProcessMessages(); // Call this in your main loop to keep the window alive
			HWND GetHandle() const { return m_hwnd; }

		protected:

			// The static router that the OS speaks to directly
			static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

			// The internal member function where you actually handle events
			LRESULT MemberWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);



	};
}