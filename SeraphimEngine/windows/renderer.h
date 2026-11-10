
#pragma once

#include "core/renderer.h"
#include "Windows.h"
#include <memory>

#include <fstream>
#include <iterator>
#include <stdexcept>
#include <string>

namespace SeraphimEngine::Windows 
{

	class Renderer final : public  SeraphimEngine::Renderer
	{
		public:

			explicit Renderer(HWND windowHandle);

			~Renderer() override;

			void BeginFrame(Color clearColor) override;
			void DrawRect(Rect rect, Color color) override;
			void EndFrame() override;

			
		private:
		
			struct GraphicsState; // EGL/GLES
			std::unique_ptr<GraphicsState> m_State;

	};

} // namespace SeraphimEngine
