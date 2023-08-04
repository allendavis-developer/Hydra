#pragma once
#include <vector>
#include <memory>

#include "ECS/Entity.h"

namespace Hydra {
	class HydraEditor
	{
	public:
		HydraEditor() = default;
		~HydraEditor();
		// Disabling copying and assignment
		HydraEditor(const HydraEditor& other) = delete;
		HydraEditor& operator=(const HydraEditor& other) = delete;

		void Init();
		void AddEntityToWorld(std::shared_ptr<Entity>);
	private:
		std::vector <std::shared_ptr<Entity>> m_Entities;
	};
}