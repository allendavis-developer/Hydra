#pragma once   
#include "Core/Logger.h"

namespace Hydra {

    class Renderer
    {
    public:
        Renderer() = default;

        void Init(Logger* logger);
        void InitQuadVAO();
        void Draw();
    private:
        Logger* m_Logger;
        unsigned int m_QuadVAO;
        static bool s_GLADInitialized;
    };

}