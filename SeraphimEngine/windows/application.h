
#include "window.h"

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
			
			bool m_Running;
	};
}