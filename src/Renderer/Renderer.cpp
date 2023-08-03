#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer.h"
#include "Core/Log.h"

namespace Hydra {
    bool Renderer::s_GLADInitialized = false;

    void Renderer::Init()
    {
        if (!s_GLADInitialized)
        {
            // Initialize GLAD here
            int gladSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
            if (!gladSuccess)
            {
                HYDRA_ERROR("Failed to initialize GLAD!");
                return;
            }

            HYDRA_INFO("Successfully initialized GLAD!");
        }
           
        InitQuadVAO();
        InitQuadShader();
    }

    void Renderer::InitQuadShader()
    {
        // Get the current working directory

        m_QuadShader.Load(ShaderTypes::QuadShader);
    }

    void Renderer::Draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.7f, 0.7f, 1.0f);

        m_QuadShader.Use();
        glBindVertexArray(m_QuadVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    // Initializes the quad VAO -> with the VBO and the EBO
    void Renderer::InitQuadVAO()
    {
        HYDRA_TRACE("Initializing quad VAO");
        // Copied from learnopengl.com
        // Set up vertex data (and buffer(s)) and configure vertex attributes
        float vertices[] = {
            // Positions          // Colors           // Texture coords
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,    // top right
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,    // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // Bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // Top left 
        };

        unsigned int indices[] = {
            0, 1, 3, // First triangle
            1, 2, 3  // Second triangle
        };

        // Generating VBO and EBO
        unsigned int VBO, EBO;
        glGenVertexArrays(1, &m_QuadVAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(m_QuadVAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Texture coords attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
    }
}