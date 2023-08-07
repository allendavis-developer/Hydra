#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <GLFW/glfw3.h>

#include "GUIEditor.h"
#include "Renderer/Renderer.h"

#include "Core/Log.h"


namespace Hydra {

	void TransformComponentGUI::Display() const 
	{
		auto transformComponent = std::dynamic_pointer_cast<TransformComponent2D>(m_Component);
		Vector2<float> position = transformComponent->GetPosition();
		Vector2<float> scale = transformComponent->GetScale();
		float rotation = transformComponent->GetRotation();

		ImGui::Text("TransformComponent!");

		// ImGui code to display the position, scale, and rotation
		ImGui::Text("Position: (%.2f, %.2f)", position.X, position.Y);
		ImGui::Text("Scale: (%.2f, %.2f)", scale.X, scale.Y);
		ImGui::Text("Rotation: %.2f", rotation);

	}

	void SpriteComponentGUI::Display() const 
	{
		ImGui::Text("SpriteComponent!");
	}

	// Initializes imgui
	void GUIEditor::Init(GLFWwindow* glfwWindow)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}


		// initialize ImGui's glfw/opengl implementation 
		ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
		ImGui_ImplOpenGL3_Init("#version 330");

		m_ComponentsToTheirGUIS[typeid(TransformComponent2D)] = &m_TransformComponentGUI;
		m_ComponentsToTheirGUIS[typeid(SpriteComponent2D)] = &m_SpriteComponentGUI;


	}

	// Cleans up imgui
	void GUIEditor::Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void GUIEditor::ImGuiNewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void GUIEditor::Update()
	{
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

		// Main Viewport Window!
		ImGui::Begin("My Scene");

		m_GameWindowSize.X = ImGui::GetContentRegionAvail().x;
		m_GameWindowSize.Y = ImGui::GetContentRegionAvail().y;
		ImGui::Button("Play!");

		ImVec2 pos = ImGui::GetCursorScreenPos();

		m_GameWindowPosition = Vector2<float>(pos.x, pos.y);

		// Adding our created texture to ImGui
		ImGui::GetWindowDrawList()->AddImage(
			(void*)SpriteRenderer::GetEditorInstance().GetRenderedTexture(),
			ImVec2(pos.x, pos.y),
			ImVec2(pos.x + 1280, pos.y + 720),
			ImVec2(0, 1),
			ImVec2(1, 0)
		);

		ImGui::End();

		// Properties window
		ImGui::Begin("Properties");

		for (ComponentGUI* componentGUI : m_EnabledComponentGUIs)
		{
			componentGUI->Display();
		}

		ImGui::End();
		
		// Console window
		ImGui::Begin("Console Output!");
		ImGui::End();

		// Entity list window
		ImGui::Begin("Entity list");
		ImGui::End();

	}

	void GUIEditor::Render()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		ImGuiIO& io = ImGui::GetIO(); (void)io;

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backupCurrentContext);
		}

	}


	void GUIEditor::SelectEntity(std::shared_ptr<Entity> entity)
	{
		HYDRA_INFO("Entity Selected!");
		const ComponentList& componentList = entity->GetComponents();
		for (std::shared_ptr<Component> component : componentList)
		{
			// Finds the type of the component
			std::type_index componentType = typeid(*component.get());
			// Finds the relevant GUI type -> for example TransformComponentGUI for TransformComponent2D
			// It uses a map to get this
			ComponentGUI* relevantComponentGUI = m_ComponentsToTheirGUIS[componentType];

			// Adds that to the enabled list
			m_EnabledComponentGUIs.emplace_back(relevantComponentGUI);

			// Gives a pointer to it to the component so it can display the values
			relevantComponentGUI->SetComponent(component);
		}
	}

	void GUIEditor::DeselectAllEntities()
	{
		m_EnabledComponentGUIs.clear();
	}
}