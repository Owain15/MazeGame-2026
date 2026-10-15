
#include "Window.h"

namespace Engine
{

    Window::Window(const std::wstring& title, int width, int height)
        : m_className(L"MyEngineWindowClass_" + title) { // Unique class name per instance

        m_hInstance = GetModuleHandle(nullptr);

        // 1. Register the window class
        WNDCLASS wc = {};
        wc.lpfnWndProc = Window::WindowProc; // Points to our static router
        wc.hInstance = m_hInstance;
        wc.lpszClassName = m_className.c_str();
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);

        RegisterClass(&wc);

        // 2. Create the window, passing 'this' as the very last parameter
        m_hwnd = CreateWindowEx(
            0, m_className.c_str(), title.c_str(),
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, width, height,
            nullptr, nullptr, m_hInstance, this // <--- 'this' pointer passed here
        );

        if (m_hwnd) {
            ShowWindow(m_hwnd, SW_SHOW);
        }
    }



    Window::~Window() {
        if (m_hwnd) {
            DestroyWindow(m_hwnd);
        }
        UnregisterClass(m_className.c_str(), m_hInstance);
    }



    // The core trick: routing the static OS message to our specific C++ instance
    LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        Window* pWindow = nullptr;

        if (uMsg == WM_NCCREATE) {
            // Extract the 'this' pointer we passed into CreateWindowEx
            CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
            pWindow = reinterpret_cast<Window*>(pCreate->lpCreateParams);
            // Store it inside the internal Windows user data slot
            SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
        }
        else {
            // Retrieve the stored C++ instance pointer for all subsequent messages
            pWindow = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        }

        if (pWindow) {
            return pWindow->MemberWindowProc(hwnd, uMsg, wParam, lParam);
        }

        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }



    // Clean member function where you can now use class variables and state safely
    LRESULT Window::MemberWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }



    bool Window::ProcessMessages() {
        MSG msg = {};
        // PeekMessage handles things without blocking your application's frame update
        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                return false; // Time to close the app
            }
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        return true;
    }


}