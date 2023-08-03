#pragma once

#include "Logger.h"
#include "Window.h"
#include "Renderer/Renderer.h"


namespace Hydra {
	// Houses the main Engine components such as the Engine window and the Engine Renderer
	class Engine
	{
	public:
		Engine();

		void Start();
		void Update();
		void Stop();

		static Logger& GetLogger() { return m_Logger; }

	private:
		bool m_IsRunning;

		// Engine components
		static Logger m_Logger;
		Window m_Window;
		Renderer m_Renderer;

	};
}