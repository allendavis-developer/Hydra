#include <iostream>
#include "Engine.h"
#include "Window.h"

namespace Hydra {
	// Static assignment
	bool Window::s_IsGLFWInitialized = false;
	unsigned int Window::s_WindowInstancesCount = false;

	// Initializing member variables to defaults
	Window::Window()
		: m_GLFWWindow(nullptr), m_Logger(nullptr)
	{
		m_Data.Title = "Hydra Engine";
		m_Data.Width = 800;
		m_Data.Height = 600;
	}


	void Window::Init(const char* title, unsigned int width, unsigned int height, Logger* logger)
	{
		m_Data.Title = title;
		m_Data.Width = width;
		m_Data.Height = height;
		m_Logger = logger;

		if (!s_IsGLFWInitialized)
		{
			// Initialize GLFW 
			int glfwSuccess = glfwInit();
			if (!glfwSuccess)
				m_Logger->Error("Failed to initialize GLFW!");
		}

		// Initialize Window 
		m_GLFWWindow = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title, NULL, NULL);
		if (!m_GLFWWindow)
		{
			// Failed to initialize GLFW Window
			m_Logger->Error("Failed to create GLFW window!");
		}

		// Create the OpenGL context
		glfwMakeContextCurrent(m_GLFWWindow);

		m_Logger->Info("Successfully created window!");

		s_WindowInstancesCount += 1;
	}


	void Window::Shutdown()
	{
		// Close window 
		glfwDestroyWindow(m_GLFWWindow);

		s_WindowInstancesCount -= 1;

		if (s_WindowInstancesCount <= 0)
		{
			// Terminate GLFW as it is not needed anymore
			glfwTerminate();
		}
	}
	void Window::PollEvents()
	{
		glfwPollEvents();
	}

	void Window::SwapBuffers()
	{
		glfwSwapBuffers(m_GLFWWindow);
	}
}