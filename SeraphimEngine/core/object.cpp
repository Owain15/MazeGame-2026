
#include "object.h"

namespace SeraphimEngine
{

	Object::Object()
	{};

    Object::Object(Rect rect, Color color, float velocityX)
        : m_Rect(rect), m_Color(color), m_VelocityX(velocityX)
    {
    }

    void Object::Update(float deltaTime)
    {
        m_Rect.x += m_VelocityX * deltaTime;
    }

}

