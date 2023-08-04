#pragma once
#include "Math/Vector2.h"

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
	private:
		Vector2<float> m_GameWindowSize;
		Vector2<float> m_GameWindowPosition;
	};
}