
#include "window.h"

namespace SeraphimEngine::Windows
{

	LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		Window* window = nullptr;

		if (message == WM_NCCREATE)
		{
			auto* createInfo = reinterpret_cast<CREATESTRUCT*>(lParam);
			window = static_cast<Window*>(createInfo->lpCreateParams);

			SetWindowLongPtr(hwnd, GWLP_USERDATA,
				reinterpret_cast<LONG_PTR>(window));
			window->m_Handle = hwnd;
		}
		else
		{
			window = reinterpret_cast<Window*>(
				GetWindowLongPtr(hwnd, GWLP_USERDATA));
		}

		if (window && message == WM_SIZE && window->m_EventCallback)
		{
			const unsigned int width = LOWORD(lParam);
			const unsigned int height = HIWORD(lParam);

			SeraphimEngine::Events::Window::ResizeEvent event(width, height);
			window->m_EventCallback(event);
		}

		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	Window::Window(const wchar_t* title, int width, int height)
	{
		WNDCLASS wc = {};
		wc.lpfnWndProc = &Window::WindowProc;
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
			this
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

	void Window::SetEventCallback(EventCallback callback)
	{
		m_EventCallback = callback;
	}

	SeraphimEngine::Events::Window::ResizeEvent Window::GetResizeEvent() const
	{
		RECT rect;
		GetClientRect(m_Handle, &rect);
		int width = rect.right - rect.left;
		int height = rect.bottom - rect.top;
		return SeraphimEngine::Events::Window::ResizeEvent(width, height);
	}

}