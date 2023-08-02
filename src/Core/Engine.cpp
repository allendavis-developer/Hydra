#include <iostream>
#include "Engine.h"

namespace Hydra {
	// Static assignment
	Logger Engine::m_Logger("Engine");

	// Constructor initializes some default values
	Engine::Engine()
		: m_Window("Hydra Engine", 1280, 720), m_IsRunning(false)
	{

	}

	void Engine::Start()
	{
		// Initialize Engine Components
		m_Window.Init();

		m_Logger.Init();
		Engine::GetLogger().SetLevel(LogLevel::Trace);
		m_Logger.Info("Hydra Engine Started");

		m_IsRunning = true;


	}

	void Engine::Update()
	{
		// Code that runs every frame goes here
		m_Logger.Info("Hydra Engine Update Started!");

		// Program Loop
		while (m_IsRunning)
		{
			Window::PollEvents();

			m_Window.SwapBuffers();

			if (m_Window.HasUserQuit())
				m_IsRunning = false;
		}

	}

	void Engine::Stop()
	{
		// Cleanup code goes here
		m_Logger.Info("Hydra Engine Stopped");
	}
}