#pragma once
#include <vector>
#include <memory>

#include <GLFW/glfw3.h>
#include "ECS/Entity.h"
#include "GUIEditor.h"

namespace Hydra {
	class HydraEditor
	{
	public:
		HydraEditor() = default;
		// Disabling copying and assignment
		HydraEditor(const HydraEditor& other) = delete;
		HydraEditor& operator=(const HydraEditor& other) = delete;

		void Init(GLFWwindow* glfwWindow);
		void AddEntityToWorld(std::shared_ptr<Entity>);

		inline GUIEditor& GetGUIEditor() { return m_GUIEditor;  }
	private:
		std::vector <std::shared_ptr<Entity>> m_Entities;

		GUIEditor m_GUIEditor;
	};
}