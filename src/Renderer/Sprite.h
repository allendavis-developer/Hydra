#pragma once
#include "Texture2D.h"
#include "Math/Vector2.h"

namespace Hydra {
	class Sprite
	{
	public:
		Sprite() = default;
		Sprite(Vector2<float> position, float rotation, Vector2<float> scale)
			: m_Position(position), m_RotationDegrees(rotation), m_Scale(scale) { }

		void LoadFromFile(const std::string& filepath);
		void Use() const;
	private:
		Vector2<float> m_Position;
		float m_RotationDegrees;
		Vector2<float> m_Scale;

		Texture2D m_Texture;	
	};
}