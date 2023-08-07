#pragma once
#include <typeindex>
#include <map>

#include "Event.h"


namespace Hydra {
	class EventManager
	{
	public:
		static EventManager& Get()
		{
			static EventManager instance;
			return instance;
		}

		template<typename EventType>
		void Connect(EventFunction function)
		{
			std::type_index eventTypeIndex = typeid(EventType);
			m_ConnectionList[eventTypeIndex].emplace_back(function);
		}

		// Fires the function
		// Use it as EventManager::Get().Fire<EventType>(.....);
		template<typename EventType, typename... Args>
		void Fire(Args&&... args)
		{
			std::type_index eventType = typeid(EventType);
			// If the relevant event exists in the connection list
			if (m_ConnectionList.find(eventType) != m_ConnectionList.end())
			{
				for (EventFunction func : m_ConnectionList[eventType])
				{
					// Call event
					EventType eventInstance(std::forward<Args>(args)...);
					if (!eventInstance.IsHandled())
					{
						func(eventInstance);
					}
				}
			}

		}
	private:
		std::map<std::type_index, EventFunctionVector> m_ConnectionList;
	};
}

#define CONNECT_EVENT_FN(EventType, Function) EventManager::Get().Connect<EventType>(BIND_EVENT_FN(Function))
