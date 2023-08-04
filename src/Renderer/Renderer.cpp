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
    Shader SpriteRenderer::m_QuadShader;
    std::vector<const Sprite*> SpriteRenderer::m_Sprites;

    SpriteRenderer::SpriteRenderer()
        : m_QuadVAO(0)
    {

    }

    void SpriteRenderer::Init(unsigned int windowWidth, unsigned int windowHeight)
    {
        InitQuadVAO();
        InitQuadShader();

        // Creating the view matrix
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, 0.0f));
        m_QuadShader.SetMat4("uView", view);

        // Creating the projection matrix
        glm::mat4 projection = glm::ortho(0.0f, (float)windowWidth, (float)windowHeight, 0.0f, -1.0f, 1.0f);
        m_QuadShader.SetMat4("uProjection", projection);

    }

    void SpriteRenderer::InitQuadShader()
    {
        m_QuadShader.Load(ShaderTypes::QuadShader);
    }

    // Runs every frame
    void SpriteRenderer::Draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        // Preparing for rendering quads by binding the Quad VAO and using the Quad Shader
        m_QuadShader.Use();
        glBindVertexArray(m_QuadVAO);
           
        // Rendering all the sprites
        for (const Sprite* sprite : m_Sprites)
        {
            DrawSprite(sprite);
        }
    }

    void SpriteRenderer::SubmitSprite(const Sprite* sprite)
    {
        m_Sprites.emplace_back(sprite);
    }

    void SpriteRenderer::DrawSprite(const Sprite* sprite)
    {
        sprite->Use();
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    // Initializes the quad VAO -> with the VBO and the EBO
    void SpriteRenderer::InitQuadVAO()
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