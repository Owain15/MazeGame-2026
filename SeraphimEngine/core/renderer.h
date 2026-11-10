
#pragma once

namespace SeraphimEngine
{

	struct Color { float r, g, b, a; };
	struct Rect { float x, y, width, height; };

	class Renderer
	{
		public:

			virtual ~Renderer() = default;
			
			virtual void BeginFrame(Color clearColor) = 0;
			virtual void DrawRect(Rect rect, Color color) = 0;
			virtual void EndFrame() = 0;
	

		private:
		
	};

} // namespace SeraphimEngine