
#include "window.h"
#include "renderer.h"

//#include "logging.h"
//#include "core/events_dispatcher.h"
//#include "core/events_window.h"

namespace SeraphimEngine::Windows
{
	class Application
	{
		public:
			
			Application();
			~Application();
		
			void Run();
		
		private:
			
			SeraphimEngine::Windows::Window m_Window;
			
			SeraphimEngine::Windows::Renderer m_Renderer;
			SeraphimEngine::Camera2D m_Camera;

			bool m_Running;
	};
}