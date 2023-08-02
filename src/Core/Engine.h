#pragma once

#include "Window.h"
#include "Logger.h"

namespace Hydra {
	// Houses the main Engine components such as the Engine window and the Engine Renderer
	class Engine
	{
	public:
		Engine();

		void Start();
		void Update();
		void Stop();

		static Logger& GetLogger() { return m_Logger;  }
	private:
		bool m_IsRunning;

		// Engine components
		Window m_Window;
		static Logger m_Logger;

	};
}