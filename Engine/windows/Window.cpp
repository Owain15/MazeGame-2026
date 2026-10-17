
#include "window.h"

namespace Engine::Windows
{
	Window::Window(const wchar_t* title, int width, int height)
	{
		WNDCLASS wc = {};
		wc.lpfnWndProc = DefWindowProc;
		wc.hInstance = GetModuleHandle(nullptr);
		wc.lpszClassName = L"EngineWindowClass";
		RegisterClass(&wc);
		m_Handle = CreateWindowEx(
			0,
			L"EngineWindowClass",
			title,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT, width, height,
			nullptr,
			nullptr,
			GetModuleHandle(nullptr),
			nullptr
		);

		ShowWindow(m_Handle, SW_SHOW);
	}

	Window::~Window()
	{
		if (m_Handle)
		{
			DestroyWindow(m_Handle);
			m_Handle = nullptr;
		}
	}

	bool Window::ProcessMessages()
	{
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				return false;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		return true;
	}

	HWND Window::GetHandle() const
	{
		return m_Handle;
	}

}