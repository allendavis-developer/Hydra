#pragma once
#include "Math/Vector2.h"
#include "ECS/Entity.h"

namespace Hydra {
	class GUIEditor
	{
	public:
		void Init(GLFWwindow* glfwWindow);
		void Shutdown();

		void ImGuiNewFrame();
		void Update();
		void Render();
		Vector2<float> GetGameWindowSize() { return m_GameWindowSize; }
		Vector2<float> GetGameWindowPosition() { return m_GameWindowPosition; }

		// GUI Engine Functions
		void SelectEntity(std::shared_ptr<Entity> entity);
	private:
		Vector2<float> m_GameWindowSize;
		Vector2<float> m_GameWindowPosition;
	};
}