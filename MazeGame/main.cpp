
//#include "Engine/EnteryPoint.h"
#include "Window.h"


int main()
{

    // Create the window instance cleanly
    Engine::Window gameWindow(L"MazeGame", 1280, 720);

    bool running = true;
    
    while (running) {
    
        // Process OS window messages
        if (!gameWindow.ProcessMessages()) {
            running = false;
        }

        // Your game engine / application logic goes here
        // (e.g., gameWindow.GetHandle() can be passed to DirectX or Vulkan)

        Sleep(16); // Simple cap to ~60fps for testing
    }

    return 0;

}

