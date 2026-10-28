
#pragma once

#include "events_types.h"
#include <string>
//#include <functional>
//#include <vector>

namespace SeraphimEngine::Events
{
    class Event     
    {
        public:
        
            virtual ~Event() = default;

            bool Handled = false; // Allows systems to block events from bubbling down

            virtual EventType GetEventType() const = 0;
            virtual const char* GetName() const = 0;
            virtual std::string ToString() const { return GetName(); }
    };
}









