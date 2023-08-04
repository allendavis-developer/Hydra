#include "HydraEditor.h"
#include "Renderer/Renderer.h"
#include "Core/Log.h"

#include "ECS/TransformComponent.h"
#include "ECS/SpriteComponent.h"

namespace Hydra {
	void HydraEditor::Init()
	{
		auto entity = std::make_shared<Entity>();
		entity->AddComponentConstruct<TransformComponent2D>(
			Vector2<float>(500.0f, 360.0f), 0.0f, Vector2<float>(200.0f, 200.0f));
		entity->AddComponentConstruct<SpriteComponent2D>
			("res/NinjaAdventure/Actor/Characters/BlueNinja/SeparateAnim/Special2.png");

		auto entity2 = std::make_shared<Entity>();
		entity2->AddComponentConstruct<TransformComponent2D>(
			Vector2<float>(800.0f, 560.0f), 0.0f, Vector2<float>(300.0f, 300.0f));
		entity2->AddComponentConstruct<SpriteComponent2D>
			("res/NinjaAdventure/Actor/Monsters/Cyclope/Faceset.png");

		SpriteRenderer::SubmitEntity(entity);
		SpriteRenderer::SubmitEntity(entity2);

		AddEntityToWorld(entity);
		AddEntityToWorld(entity2);

	}

	void HydraEditor::AddEntityToWorld(std::shared_ptr<Entity> entity)
	{
		m_Entities.emplace_back(entity);
	}

	HydraEditor::~HydraEditor()
	{
	}
}