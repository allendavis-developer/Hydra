#include "Engine.h"

int main()
{
	auto engine = new Hydra::Engine;
	engine->Start();
	engine->Update();
	engine->Stop();

	delete engine;
}