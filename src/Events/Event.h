#pragma once
#include <functional>
#include <vector>

namespace Hydra {
	class Event
	{
	public:
		inline bool IsHandled() const { return m_IsHandled; }
	private:
		bool m_IsHandled = false;
	};

	using EventFunction = std::function<void(Event&)>;
	using EventFunctionVector = std::vector<EventFunction>;
}