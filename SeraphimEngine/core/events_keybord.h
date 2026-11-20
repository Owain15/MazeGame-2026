
#pragma once

#include "events.h"

namespace SeraphimEngine::Events::Keyboard
{

    class KeyPressed : public Event
    {
        public:

            KeyPressed(unsigned int keycode)
            : m_Keycode(keycode)
            {}

            inline unsigned int GetKeycode() const { return m_Keycode; }

            static EventType GetStaticType() { return EventType::KeyPressed; }
            virtual EventType GetEventType() const override { return GetStaticType(); }
            virtual const char* GetName() const override { return "KeyboardKeyPressed"; }

        private:

            unsigned int m_Keycode;

    };

	class KeyReleased : public Event
	{
	public:
		KeyReleased(unsigned int keycode)
			: m_Keycode(keycode)
		{
		}
		inline unsigned int GetKeycode() const { return m_Keycode; }
		static EventType GetStaticType() { return EventType::KeyReleased; }
		virtual EventType GetEventType() const override { return GetStaticType(); }
		virtual const char* GetName() const override { return "KeyboardKeyReleased"; }
	private:
		unsigned int m_Keycode;
	};


}
       