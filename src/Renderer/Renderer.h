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
    private:
        unsigned int m_QuadVAO;
        Shader m_QuadShader;
        Sprite m_TestSprite;
    };
}