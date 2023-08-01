#include <iostream>
#include "Engine.h"

namespace Hydra {

	void Engine::Start()
	{
		// Initialization code goes here
		std::cout << "Hydra Engine Started!" << std::endl;
	}

	void Engine::Update()
	{
		// Code that runs every frame goes here
		std::cout << "Hydra Engine Update Started" << std::endl;
		while (true);

	}

	void Engine::Stop()
	{
		// Cleanup code goes here
		std::cout << "Hydra Engine Stopped" << std::endl;
	}
}