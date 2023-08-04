#include <iostream>
#include <glad/glad.h>

#include "Engine.h"
#include "Log.h"

namespace Hydra {
	// Static assignment
	Logger Engine::m_Logger("Hydra");

	// Constructor initializes some default values
	Engine::Engine()
		: m_IsRunning(false), m_Renderer()
	{
		
	}

	void Engine::Start()
	{
		// Initialize Logger
		m_Logger.Init();
		m_Logger.SetLevel(LogLevel::Trace);
		m_Logger.Trace("Started!");

		// Initializing Window
		m_Window.Init("HydraEngine", 1280, 720, &m_Logger);

		// Initialize GLAD
		int gladSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		if (!gladSuccess)
		{
			HYDRA_ERROR("Failed to initialize GLAD!");
			return;
		}

		HYDRA_INFO("Successfully initialized GLAD!");

		// Initialize Renderer
		m_Renderer.Init(1280, 720);

		// Initialize editor
		m_Editor.Init();

		m_IsRunning = true;
	}

	void Engine::Update()
	{
		// Code that runs every frame goes here
		m_Logger.Trace("Updating!");

		// Program Loop
		while (m_IsRunning)
		{
			// Render logic here
			m_Renderer.Draw();

			Window::PollEvents();
			m_Window.SwapBuffers();

			if (m_Window.HasUserQuit())
				m_IsRunning = false;
		}

	}

	void Engine::Stop()
	{
		// Cleanup code goes here
		m_Logger.Trace("Stopped!");
		m_Window.Shutdown();
	}
}