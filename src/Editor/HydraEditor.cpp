#include "HydraEditor.h"
#include "Renderer/Renderer.h"

namespace Hydra {
	void HydraEditor::Init()
	{
		Sprite* sprite = new Sprite(Vector2<float>(300.0f, 200.0f), 
				0.0f, Vector2<float>(200.0f, 200.0f));
		sprite->LoadFromFile("res/NinjaAdventure/Actor/Characters/BlueSamurai/SeparateAnim/Special1.png");
		m_Sprites.emplace_back(sprite);
		SpriteRenderer::SubmitSprite(sprite);
	}

	HydraEditor::~HydraEditor()
	{
		// Deletes all the sprites
		for (Sprite* sprite : m_Sprites)
		{
			delete sprite;
		}
	}
}