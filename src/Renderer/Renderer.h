#pragma once   
#include <vector>

#include "Core/Logger.h"
#include "Shaders/Shader.h"
#include "Texture2D.h"
#include "Sprite.h"

namespace Hydra {

    class SpriteRenderer
    {
    public:
        SpriteRenderer();
         
        void Init(unsigned int windowWidth, unsigned int windowHeight);
        void InitQuadVAO();
        void InitQuadShader();
        void Draw();
        static void SubmitSprite(const Sprite* sprite);

        static const Shader& GetQuadShader() { return m_QuadShader; }
    private:
        unsigned int m_QuadVAO;
        static Shader m_QuadShader;

        static std::vector<const Sprite*> m_Sprites;

        void DrawSprite(const Sprite* sprite);
    };
}