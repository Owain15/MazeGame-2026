
#pragma once

namespace SeraphimEngine
{

	struct Camera2D
	{
		float x = 0.0f;
		float y = 0.0f;
		float zoom = 1.0f;
	};

	struct Color { float r, g, b, a; };
	struct Rect { float x, y, width, height; };

	class Renderer
	{
		public:

			virtual ~Renderer() = default;
			
			virtual void BeginFrame(Color clearColor, const Camera2D& camera) = 0;
			virtual void DrawRect(Rect rect, Color color) = 0;
			virtual void EndFrame() = 0;
	
		protected:

			SeraphimEngine::Camera2D m_Camera;

		private:
		
	};

} // namespace SeraphimEngine