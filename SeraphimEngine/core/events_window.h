
#pragma once

#include "events.h"

namespace SeraphimEngine::Events::Window
{
    class ResizeEvent : public Event
    {
        public:

            ResizeEvent(unsigned int width, unsigned int height)
            : m_Width(width), m_Height(height)
            {
            }

            inline unsigned int GetWidth() const { return m_Width; }
            inline unsigned int GetHeight() const { return m_Height; }

            static EventType GetStaticType() { return EventType::WindowResize; }
            virtual EventType GetEventType() const override { return GetStaticType(); }
            virtual const char* GetName() const override { return "WindowResize"; }

            std::string ToString() const override
            {
                return "WindowResizeEvent: " + std::to_string(m_Width) + ", " + std::to_string(m_Height);
            }

        private:

            unsigned int m_Width, m_Height;

    };

}