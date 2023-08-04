#pragma once   
#include <vector>

#include "Core/Logger.h"
#include "Shaders/Shader.h"
#include "Texture2D.h"
#include "ECS/Entity.h"

namespace Hydra {

    class SpriteRenderer
    {
    public:
        SpriteRenderer();
         
        void Init(unsigned int windowWidth, unsigned int windowHeight);
        void InitQuadVAO();
        void InitQuadShader();
        void Draw();
        static void SubmitEntity(const std::shared_ptr<Entity> entity);
    private:
        unsigned int m_QuadVAO;
        Shader m_QuadShader;

        static std::vector<std::shared_ptr<Entity>> m_Entities;

        void DrawEntity(const std::shared_ptr<Entity> entity);
    };
}