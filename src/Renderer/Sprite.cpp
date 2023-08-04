#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sprite.h"
#include "Renderer.h"

namespace Hydra {
	void Sprite::LoadFromFile(const std::string& filepath)
	{
		m_Texture.LoadFromFile(filepath);
	}

	void Sprite::Use() const
	{
		const Shader& quadShader = SpriteRenderer::GetQuadShader();
		quadShader.Use();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(m_Position.X, m_Position.Y, 0.0f));
		model = glm::rotate(model, glm::radians(m_RotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::scale(model, glm::vec3(m_Scale.X, m_Scale.Y, 0.0f));

		quadShader.SetMat4("uModel", model);
		m_Texture.Bind();
	}
}