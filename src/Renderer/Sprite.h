#pragma once
#include "Texture2D.h"

namespace Hydra {
	class Sprite
	{
	public:
		Sprite() = default;

		void LoadFromFile(const std::string& filepath);
		void BindTexture() const;
	private:
		Texture2D m_Texture;	
	};
}