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
        SpriteRenderer();
        
        void Init(unsigned int windowWidth, unsigned int windowHeight);
        void Shutdown();
        void InitQuadVAO();
        void InitQuadShader();
        void Draw();


        void SetWindowSize(Vector2<unsigned int> windowSize) 
            { m_WindowSize = windowSize; }

        // To be used by Engine
        void CreateFramebuffer();
        void BindFramebuffer();
        void UnbindFramebuffer();
        
        // Statics
        static void SubmitEntity(const std::shared_ptr<Entity> entity);
        static unsigned int GetRenderedTexture() { return m_RenderedTexture; }
    private:
        unsigned int m_QuadVAO;
        unsigned int m_FBO; // Frame buffer object
        static unsigned int m_RenderedTexture; // Rendered texture ID
        static unsigned int m_RBO; // Render buffer object

        Vector2<unsigned int> m_WindowSize;

        Shader m_QuadShader;

        static std::vector<std::shared_ptr<Entity>> m_Entities;

        void DrawEntity(const std::shared_ptr<Entity> entity);

    };
}