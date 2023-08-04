#pragma once   
#include "Core/Logger.h"
#include "Shaders/Shader.h"
#include "Texture2D.h"
#include "Sprite.h"

namespace Hydra {

    class Renderer
    {
    public:
        Renderer();

        void Init();
        void InitQuadVAO();
        void InitQuadShader();
        void Draw();
        void DrawSprite(const Sprite& sprite);

        static const Shader& GetQuadShader() { return m_QuadShader; }
    private:
        unsigned int m_QuadVAO;
        static Shader m_QuadShader;

        Sprite m_TestSprite;
        Sprite m_TestSprite2;
    };
}