#pragma once
#include "Component.h"
#include "Math/Vector2.h"

namespace Hydra {
	class TransformComponent2D : public Component
	{
	public:
		TransformComponent2D(const Vector2<float>& position, float rotation, 
				const Vector2<float>& scale)
			: m_Position(position), m_Rotation(rotation), m_Scale(scale)
		{

		}
		
		// Getters
		Vector2<float> GetPosition() const { return m_Position; }
		Vector2<float> GetScale() const { return m_Scale; }
		float GetRotation() const { return m_Rotation; }

		// Setters
		void SetPosition(const Vector2<float>& position) { m_Position = position; }
		void SetScale(const Vector2<float> scale) { m_Scale = scale; }
		void SetRotation(float rotation) { m_Rotation = rotation; }

	private:
		Vector2<float> m_Position;
		float m_Rotation;
		Vector2<float> m_Scale;
	};
}