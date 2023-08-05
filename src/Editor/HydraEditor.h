#pragma once
#include <vector>
#include <memory>
#include <GLFW/glfw3.h>

#include "ECS/Entity.h"
#include "GUIEditor.h"
#include "Events/Event.h"

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
		void Shutdown();

		inline GUIEditor& GetGUIEditor() { return m_GUIEditor;  }

		// Event callbacks
		void OnMouseButtonEvent(Event& event);

		void CheckEntitiesSelected(Vector2<float> mousePosition);

		bool IsMousePositionInsideEntity(Vector2<float> mousePosition, Vector2<float> entityPosition, 
			Vector2<float> entityScale);

	private:
		std::vector <std::shared_ptr<Entity>> m_Entities;

		GUIEditor m_GUIEditor;
	};
}