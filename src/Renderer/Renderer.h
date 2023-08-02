#pragma once   
#include "Core/Logger.h"

namespace Hydra {

    class Renderer
    {
    public:
        Renderer() = default;

        void Init(Logger* logger);
        void Draw();
    private:
        static bool s_GLADInitialized;
        Logger* m_Logger;
    };

}