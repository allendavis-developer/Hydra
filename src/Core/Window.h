#pragma once
#include <GLFW/glfw3.h>

namespace Hydra {

	struct WindowData
	{
		const char* Title;
		unsigned int Width;
		unsigned int Height;
	};


	class Window
	{
	public:
		Window();
		Window(const char* title, unsigned int width, unsigned int height);

		void Init();
		void Shutdown();
		void SwapBuffers();

		// Getters and setters
		bool HasUserQuit() { return glfwWindowShouldClose(m_GLFWWindow); }
		WindowData GetWindowData() { return m_Data; }

		// Polls events for all active windows.
		// This is static because GLFW doesn't need a window instance to poll events. It polls events for all Windows
		static void PollEvents();
	private:
		GLFWwindow* m_GLFWWindow;

		WindowData m_Data;

		// ------------ STATICS -----------
		// This is static because all instances of the Window class will use one instance of GLFW
		// As a result, we add this variable to make sure GLFW is only initialized once
		static bool s_IsGLFWInitialized;

		// Just to terminate GLFW after all window instances have been closed
		static unsigned int s_WindowInstancesCount;
	};
}