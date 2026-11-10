
#pragma once

namespace SeraphimEngine
{
	class Renderer
	{
		public:

			virtual ~Renderer() = default;
			virtual void DrawTriangle() = 0;
	

		private:
		
	};

} // namespace SeraphimEngine