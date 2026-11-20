
#pragma once

#include "renderer_structs.h" // Rect & Color

namespace SeraphimEngine
{
	class Object
	{
		public :

			Object();
			Object(Rect rect, Color color, float velocityX);
		
			void Update(float deltaTime);

			Rect GetRect() const { return m_Rect;  }
			Color GetColor() const { return m_Color; }

			void SetPosition(float x, float y) { m_Rect.x = x; m_Rect.y = y; }

		protected:

			Rect m_Rect;
			Color m_Color;
			float m_VelocityX;

	};
}

