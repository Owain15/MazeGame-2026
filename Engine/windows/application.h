
#include "window.h"

namespace Engine::Windows
{
	class Application
	{
		public:
			
			Application();
			~Application();
		
			void Run();
		
		private:
			
			Engine::Windows::Window m_Window;
			
			bool m_Running;
	};
}