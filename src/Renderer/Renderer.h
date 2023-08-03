#pragma once   
#include "Core/Logger.h"
#include "Shaders/Shader.h"

namespace Hydra {

    class Renderer
    {
    public:
        Renderer() = default;

        void Init();
        void InitQuadVAO();
        void InitQuadShader();
        void Draw();
    private:
        unsigned int m_QuadVAO;
        Shader m_QuadShader;

        static bool s_GLADInitialized;
    };

}