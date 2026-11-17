
#pragma once

#include "renderer_structs.h"
#include "object.h"

namespace SeraphimEngine
{

	class Renderer
	{
		public:

			virtual ~Renderer() = default;
			
			virtual void BeginFrame(Color clearColor, const Camera2D& camera) = 0;
			virtual void EndFrame() = 0;
			
			virtual void DrawRect(Rect rect, Color color) = 0;
			void DrawObject(const SeraphimEngine::Object& object)
			{ DrawRect(object.GetRect(),object.GetColor()); };
		
	protected:

			SeraphimEngine::Camera2D m_Camera;

		private:
		
	};

} // namespace SeraphimEngine