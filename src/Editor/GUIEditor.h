#pragma once
#include <map>

#include "Math/Vector2.h"
#include "ECS/Entity.h"
#include "ECS/TransformComponent.h"
#include "ECS/SpriteComponent.h"

namespace Hydra {
	
	class ComponentGUI
	{
	public:
		virtual void Display() const = 0;
		virtual void SetComponent(const std::shared_ptr<Component> component)
		{
			m_Component = component;
		}
	protected:
		std::shared_ptr<Component> m_Component;
	};

	class TransformComponentGUI : public ComponentGUI
	{
		void Display() const override;
		
	};

	class SpriteComponentGUI : public ComponentGUI
	{
		void Display() const override;
	};

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
		void DeselectAllEntities();
	private:
		Vector2<float> m_GameWindowSize;
		Vector2<float> m_GameWindowPosition;
			
		// Component GUI instances
		TransformComponentGUI m_TransformComponentGUI;
		SpriteComponentGUI m_SpriteComponentGUI;


		std::vector<ComponentGUI*> m_EnabledComponentGUIs;
		std::map<std::type_index, ComponentGUI*> m_ComponentsToTheirGUIS;
	};
}