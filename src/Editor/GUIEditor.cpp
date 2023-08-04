#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <GLFW/glfw3.h>
#include "GUIEditor.h"
#include "Renderer/Renderer.h"
#include "Core/Log.h"

namespace Hydra {
	// Initializes imgui
	void GUIEditor::Init(GLFWwindow* glfwWindow)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}


		// initialize ImGui's glfw/opengl implementation 
		ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
		ImGui_ImplOpenGL3_Init("#version 330");
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
		ImGui::Begin("My Scene");

		m_GameWindowSize.X = ImGui::GetContentRegionAvail().x;
		m_GameWindowSize.Y = ImGui::GetContentRegionAvail().y;

		ImVec2 pos = ImGui::GetCursorScreenPos();

		// Adding our created texture to ImGui
		ImGui::GetWindowDrawList()->AddImage(
			(void*)SpriteRenderer::GetRenderedTexture(),
			ImVec2(pos.x, pos.y),
			ImVec2(pos.x + 1280, pos.y + 720),
			ImVec2(0, 1),
			ImVec2(1, 0)
		);


		// Here we can render into the ImGui window
		// ImGui Buttons, Drop Downs, etc. and later our framebuffer

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
}