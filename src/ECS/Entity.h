#pragma once
#include <vector>
#include <typeindex>
#include <memory>
#include "Component.h"

namespace Hydra {
	class Entity
	{
	public:
		void AddComponent(std::shared_ptr<Component> component)
		{
			// Check if a component of the same type already exists
			std::type_index typeIdx = typeid(*component);
			for (std::shared_ptr<Component> comp : m_Components)
			{
				if (std::type_index(typeid(*comp)) == typeIdx)
				{
					// Component of the same type already exists, return without adding
					return;
				}
			}

			// If the component of this type doesn't exist, add it
			m_Components.emplace_back(component);
		}

		template<typename ComponentType, typename... Args>
		void AddComponentConstruct(Args&&... args)
		{
			// Creating the component
			std::shared_ptr<ComponentType> component = 
				std::make_shared<ComponentType>(std::forward<Args>(args)...);

			// Adding the component to the component list
			m_Components.emplace_back(component);
		}

		template<typename ComponentType>
		std::shared_ptr<ComponentType> GetComponent()
		{
			for (std::shared_ptr<Component> component : m_Components)
			{
				// Check if the component matches the type of the component we want
				if (typeid(*component) == typeid(ComponentType))
				{
					// Cast it to the relevant type
					std::shared_ptr<ComponentType> typedComponent = 
						std::dynamic_pointer_cast<ComponentType>(component);
					
					return typedComponent;
				}
			}

			// Returns nullptr if it wasn't found
			return nullptr;
		}

	private:
		std::vector<std::shared_ptr<Component>> m_Components;
	};
}