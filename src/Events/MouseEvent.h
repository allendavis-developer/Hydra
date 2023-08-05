#pragma once
#include "Math/Vector2.h"
#include "Event.h"

namespace Hydra {

	enum MouseButtonActions
	{
		MouseButtonRelease = 0,
		MouseButtonPressed = 1,
	};

	enum MouseButtonTypes
	{
		MouseButtonLeft = 0,
		MouseButtonRight = 1,
		MouseButtonMiddle = 2,
	};

	class MouseButtonEvent : public Event
	{
	public:
		MouseButtonEvent(int button, int action, Vector2<float> pressedPosition)
			: m_Button((MouseButtonTypes)button), m_Action((MouseButtonActions)action), m_PressedPosition(pressedPosition)
		{
			
		}

		inline int GetButton() const { return m_Button; }
		inline int GetAction() const { return m_Action; }
		inline Vector2<float> GetPressedPosition() const { return m_PressedPosition; }
	private:
		MouseButtonTypes m_Button;
		MouseButtonActions m_Action;

		Vector2<float> m_PressedPosition;
	};
}