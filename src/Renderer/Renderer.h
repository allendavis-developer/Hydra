#pragma once   
#include <vector>

#include "Core/Logger.h"
#include "Shaders/Shader.h"
#include "Texture2D.h"
#include "ECS/Entity.h"
#include "Math/Vector2.h"

namespace Hydra {

    // TODO: Make this a singleton
    class SpriteRenderer
    {
    public:

        inline static SpriteRenderer& Get()
        {
            static SpriteRenderer instance;
            return instance;
        }
        
        void Init(unsigned int windowWidth, unsigned int windowHeight);
        void Shutdown();
        void InitQuadVAO();
        void InitQuadShader();
        void Draw();

        // To be used by Engine
        void CreateFramebuffer();
        void BindFramebuffer();
        void UnbindFramebuffer();
        
        // Statics
        void SubmitEntity(const std::shared_ptr<Entity> entity);
        unsigned int GetRenderedTexture() { return m_RenderedTexture; }
    private:
        SpriteRenderer();

        unsigned int m_QuadVAO;
        unsigned int m_FBO; // Frame buffer object
        unsigned int m_RenderedTexture; // Rendered texture ID
        unsigned int m_RBO; // Render buffer object

        Vector2<unsigned int> m_WindowSize;

        Shader m_QuadShader;

        std::vector<std::shared_ptr<Entity>> m_Entities;

        void DrawEntity(const std::shared_ptr<Entity> entity);

    };
}