
#include "window.h"

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