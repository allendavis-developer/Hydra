#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"
#include "Core/Log.h"
#include "Texture2D.h"
#include "Math/Vector2.h"

namespace Hydra {
    Shader Renderer::m_QuadShader;

    Renderer::Renderer()
        : m_QuadVAO(0), 
        m_TestSprite(Vector2<float>(640.0f, 360.0f), 0.0f, Vector2<float>(300.0f, 300.0f))
    {

    }

    void Renderer::Init()
    {
        InitQuadVAO();
        InitQuadShader();

        m_TestSprite.LoadFromFile("res/NinjaAdventure/Actor/Characters/BlueNinja/Faceset.png");
    }

    void Renderer::InitQuadShader()
    {
        m_QuadShader.Load(ShaderTypes::QuadShader);
           
        // Creating the view matrix
        glm::mat4 view = glm::mat4(1.0f);
        m_QuadShader.SetMat4("uView", view);

        // Creating the projection matrix
        glm::mat4 projection = glm::ortho(0.0f, 1280.0f, 720.0f, 0.0f, -1.0f, 1.0f);
        m_QuadShader.SetMat4("uProjection", projection);

    }

    void Renderer::Draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.7f, 0.7f, 1.0f);

        m_QuadShader.Use();
        glBindVertexArray(m_QuadVAO);
        m_TestSprite.Use();
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
            -0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   0.0f, 1.0f,    // top left
             0.5f,  0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f,    // top right
             0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f,    // bottom right
            -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f     // bottom left
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