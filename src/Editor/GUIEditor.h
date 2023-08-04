#pragma once

namespace Hydra {
	class GUIEditor
	{
	public:
		void Init(GLFWwindow* glfwWindow);
		void Shutdown();

		void ImGuiNewFrame();
		void Update();
		void Render();
	};
}