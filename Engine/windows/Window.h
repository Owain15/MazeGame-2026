
#include <Windows.h>

namespace Engine::Windows
{
	class Window
	{
		public:
			
			Window(const wchar_t* title, int width, int height);
			~Window();
		
			bool ProcessMessages();
	
			HWND GetHandle() const;
		
		private:
	
			HWND m_Handle;
	};
}