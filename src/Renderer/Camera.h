#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Math/Vector2.h"

namespace Hydra {
	class Camera2D
	{
	public:
		Camera2D()
			: m_ViewMatrix(glm::mat4(1.0f)), m_ProjectionMatrix(glm::mat4(1.0f))
		{

		}

		inline Vector2<float> GetPosition() const { return m_Position; }
		inline Vector2<float> GetSize() const { return m_Size; }

		void SetPosition(const Vector2<float>& position)
		{
			m_Position = position;
			UpdateViewMatrix();
		}

		void AddToPosition(const Vector2<float>& addition)
		{
			m_Position += addition;
			UpdateViewMatrix();
		}

		void SetSize(const Vector2<float>& size)
		{
			m_Size = size;
			UpdateProjectionMatrix();
		}

		
		void SetScale(float scalar)
		{
			m_Size = m_Size * scalar;
			UpdateProjectionMatrix();
		}


		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
	private:

		inline void UpdateProjectionMatrix()
		{
			m_ProjectionMatrix = glm::ortho(0.0f, m_Size.X, m_Size.Y, 0.0f, -1.0f, 1.0f);
		}

		inline void UpdateViewMatrix()
		{
			m_ViewMatrix = glm::translate(m_ViewMatrix, glm::vec3(-m_Position.X, -m_Position.Y, 0.0f));
		}

		Vector2<float> m_Position;
		Vector2<float> m_Size;

		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ProjectionMatrix;
	};
}