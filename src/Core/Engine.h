#pragma once

#include "Window.h"

namespace Hydra {
	// Houses the main Engine components such as the Engine window and the Engine Renderer
	class Engine
	{
	public:
		Engine();

		void Start();
		void Update();
		void Stop();
	private:
		bool m_IsRunning;

		Window m_Window;
	};
}