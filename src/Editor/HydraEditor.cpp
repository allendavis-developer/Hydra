#include "HydraEditor.h"
#include "Renderer/Renderer.h"
#include "Core/Log.h"

#include "ECS/TransformComponent.h"
#include "ECS/SpriteComponent.h"

#include "Events/EventManager.h"
#include "Events/MouseEvent.h"
#include "Events/EditorEvent.h"

namespace Hydra {
	void HydraEditor::Init(GLFWwindow* glfwWindow)
	{
		m_GUIEditor.Init(glfwWindow);

		auto entity = std::make_shared<Entity>();
		entity->AddComponentConstruct<TransformComponent2D>(
			Vector2<float>(500.0f, 360.0f), 0.0f, Vector2<float>(200.0f, 200.0f));
		entity->AddComponentConstruct<SpriteComponent2D>
			("res/NinjaAdventure/Actor/Characters/BlueNinja/SeparateAnim/Special2.png");

		auto entity2 = std::make_shared<Entity>();
		entity2->AddComponentConstruct<TransformComponent2D>(
			Vector2<float>(100.0f, 100.0f), 0.0f, Vector2<float>(200.0f, 200.0f));
		entity2->AddComponentConstruct<SpriteComponent2D>
			("res/NinjaAdventure/Actor/Monsters/Cyclope/Faceset.png");

		SpriteRenderer::GetEditorInstance().SubmitEntity(entity);
		SpriteRenderer::GetEditorInstance().SubmitEntity(entity2);

		AddEntityToWorld(entity);
		AddEntityToWorld(entity2);

		// Event callbacks
		
		CONNECT_EVENT_FN(MouseButtonEvent, HydraEditor::OnMouseButtonEvent);
		CONNECT_EVENT_FN(MouseMotionEvent, HydraEditor::OnMouseMotionEvent);
	}

	void HydraEditor::AddEntityToWorld(std::shared_ptr<Entity> entity)
	{
		m_Entities.emplace_back(entity);
	}



	void HydraEditor::Shutdown()
	{
		m_GUIEditor.Shutdown();
	}


	void HydraEditor::OnMouseButtonEvent(Event& event)
	{
		// Static casting
		auto mouseEvent = *(MouseButtonEvent*)(&event);

		Vector2<float> gameWindowMousePosition = 
				mouseEvent.GetPressedPosition() - m_GUIEditor.GetGameWindowPosition();

		if (mouseEvent.GetButton() == MouseButtonLeft)
		{
			switch (mouseEvent.GetAction())
			{
			case MouseButtonPressed:
				CheckEntitiesSelected(gameWindowMousePosition);
				m_IsCameraPanning = true;
				HYDRA_INFO("Camera pan start");
				break;
			case MouseButtonRelease:
				m_IsCameraPanning = false;
				HYDRA_INFO("Camera pan stop");
				break;
			}
		}
	}

	void HydraEditor::OnMouseMotionEvent(Event& event)
	{
		MouseMotionEvent& mouseEvent = *(MouseMotionEvent*)(&event);

		Vector2<float> mousePos = mouseEvent.GetPosition();

		if (m_IsCameraPanning)
		{
		}
	}


	// TODO: This could be made more efficient by not looping through every single entiy
	void HydraEditor::CheckEntitiesSelected(Vector2<float> mousePosition)
	{
		m_GUIEditor.DeselectAllEntities();

		for (auto entity : m_Entities)
		{
			auto transform = entity->GetComponent<TransformComponent2D>();
			if (transform == nullptr)
				continue;

			Vector2<float> entityPosition = transform->GetPosition();
			Vector2<float> entityScale = transform->GetScale();

			bool isMouseInsideEntity = IsMousePositionInsideEntity(mousePosition, entityPosition, entityScale);
			if (isMouseInsideEntity)
			{
				m_GUIEditor.SelectEntity(entity);
				return;
			}
		}

	}

	// This could be made more efficient
	bool HydraEditor::IsMousePositionInsideEntity(Vector2<float> mousePosition, Vector2<float> entityPosition, 
			Vector2<float> entityScale)
	{
		// Calculate the half dimensions of the entity (half width and half height)
		float halfWidth = entityScale.X * 0.5f;
		float halfHeight = entityScale.Y * 0.5f;

		// Calculate the left, right, top, and bottom bounds of the entity
		float left = entityPosition.X - halfWidth;
		float right = entityPosition.X + halfWidth;
		float top = entityPosition.Y + halfHeight;
		float bottom = entityPosition.Y - halfHeight;

		// Check if the mouse position is inside the entity's bounds
		if (mousePosition.X >= left && mousePosition.X <= right && mousePosition.Y >= bottom && mousePosition.Y <= top)
		{
			return true;
		}
		return false;
	}


}