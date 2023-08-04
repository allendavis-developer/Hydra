#pragma once
#include "Renderer/Texture2D.h"
#include "Component.h"

namespace Hydra {
	class SpriteComponent2D : public Component
	{
	public:
		SpriteComponent2D(const std::string& filepath)
		{
			m_Texture.LoadFromFile(filepath);
		}

		const Texture2D& GetTexture() const { return m_Texture;  }

	private:
		Texture2D m_Texture;
	};
}