#include <iostream>
#include "Engine.h"

namespace Hydra {
	
	// Constructor initializes some default values
	Engine::Engine()
		: m_Window("Hydra Engine", 1280, 720), m_IsRunning(false)
	{

	}

	void Engine::Start()
	{
		// Initialization code goes here
		std::cout << "Hydra Engine Started!" << std::endl;

		// Initialize Window
		m_Window.Init();

		m_IsRunning = true;
		
	}

	void Engine::Update()
	{
		// Code that runs every frame goes here
		std::cout << "Hydra Engine Update Started" << std::endl;

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
		std::cout << "Hydra Engine Stopped" << std::endl;
	}
}