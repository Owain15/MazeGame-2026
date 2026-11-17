
#pragma once

namespace SeraphimEngine::Events
{
	enum class EventType
	{
		None = 0,

		//Window Events
		WindowClose, WindowResize, WindowMinimized, WindowFocus,
		//Keyboard Events
		KeyPressed, KeyReleased,
		//Mouse Events
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};
}

