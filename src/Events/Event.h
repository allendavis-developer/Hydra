#pragma once
#include <functional>
#include <vector>

#define BIND_EVENT_FN(Function) std::bind(&Function, this, std::placeholders::_1)

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