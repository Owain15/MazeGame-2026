
#include "window.h"
#include "renderer.h"

#include "core/object.h"

//#include "logging.h"
//#include "core/events_dispatcher.h"
//#include "core/events_window.h"

namespace SeraphimEngine::Windows
{
	class Application
	{
		public:
			
			Application( SeraphimEngine::Object& player, SeraphimEngine::Object& testObject);
			~Application();
		
			void Run();

		private:

			void OnEvent(SeraphimEngine::Events::Event& event);

			void UpdateGameState(const float deltaTime);
			void Render();
		
		private:
			
			SeraphimEngine::Windows::Window m_Window;
			
			SeraphimEngine::Windows::Renderer m_Renderer;
			SeraphimEngine::Camera2D m_Camera;

			bool m_Running;
			bool m_Paused;
			bool m_Minimized;

			SeraphimEngine::Object& m_Player;
			SeraphimEngine::Object& m_Object;

			struct Inputs
			{
				bool Up = false;
				bool Down = false;
				bool Left = false;
				bool Right = false;

			} m_Inputs;
	};
}