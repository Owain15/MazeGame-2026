
#pragma once

#include "events.h"

namespace SeraphimEngine::Events
{
    class EventDispatcher
    {
        public:

            EventDispatcher(Event& event) : m_Event(event) {}

            // Route an event to a specific target function if the types match
            template<typename T, typename F>
            bool Dispatch(const F& func)
            {
                if (m_Event.GetEventType() == T::GetStaticType())
                {
                    // Safely cast up to the concrete type and execute callback
                    m_Event.Handled |= func(static_cast<T&>(m_Event));
                    return true;
                }

                return false;
            }

        private:

            Event& m_Event;
    };
}


