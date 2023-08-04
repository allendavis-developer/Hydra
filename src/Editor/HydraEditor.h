#pragma once
#include <vector>
#include "Renderer/Sprite.h"

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
	private:
		std::vector<Sprite*> m_Sprites;
	};
}