#include "Sprite.h"

namespace Hydra {
	void Sprite::LoadFromFile(const std::string& filepath)
	{
		m_Texture.LoadFromFile(filepath);
	}

	void Sprite::BindTexture() const
	{
		m_Texture.Bind();
	}
}