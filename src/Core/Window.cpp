#include <iostream>
#include "Engine.h"
#include "Window.h"
#include "Core/Log.h"

#include "Events/EventManager.h"
#include "Events/MouseEvent.h"


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

		// Setting the user pointer to this instance of the Window class
		// so I can use it in lambdas through glfwGetWindowUserPointer
		glfwSetWindowUserPointer(m_GLFWWindow, this);

		// Setting callbacks
		glfwSetKeyCallback(m_GLFWWindow,
			[](GLFWwindow* window, int key, int scancode, 
				int action, int mods)
			{
				// Getting the window class associated with this window
				Window* hydraWindow = (Window*)glfwGetWindowUserPointer(window);
			});

		glfwSetMouseButtonCallback(m_GLFWWindow,
			[](GLFWwindow* window, int button, int action, int mods)
			{
				// Getting the window class associated with this window
				Window* hydraWindow = (Window*)glfwGetWindowUserPointer(window);

				// Getting cursor position
				double xpos, ypos;
				glfwGetCursorPos(window, &xpos, &ypos);

				// Calling the mouse button callback function on that Window
				EventManager::Get().Fire<MouseButtonEvent>(button, action, Vector2<float>((float)xpos, (float)ypos));
			});

		glfwSetCursorPosCallback(m_GLFWWindow, 
			[](GLFWwindow* window, double xpos, double ypos)
			{
				// Getting the window class associated with this window
				Window* hydraWindow = (Window*)glfwGetWindowUserPointer(window);

				EventManager::Get().Fire<MouseMotionEvent>(Vector2<float>((float)xpos, (float)ypos));
			});
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