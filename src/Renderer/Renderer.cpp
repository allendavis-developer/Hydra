#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Renderer.h"

namespace Hydra {
    bool Renderer::s_GLADInitialized = false;

    void Renderer::Init(Logger* logger)
    {
        if (!s_GLADInitialized)
        {
            // Initialize GLAD here
            int gladSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            if (!gladSuccess)
            {
                logger->Error("Failed to initialize GLAD!");
                return;
            }

            logger->Info("Successfully initialized GLAD!");
        }
    }

    void Renderer::Draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.7f, 0.7f, 1.0f);
    }
}