#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer.h"
#include "Core/Log.h"
#include "Texture2D.h"
#include "Math/Vector2.h"

#include "ECS/SpriteComponent.h"
#include "ECS/TransformComponent.h"

#include "Events/EditorEvent.h"
#include "Events/EventManager.h"

namespace Hydra {
    
    SpriteRenderer::SpriteRenderer()
        : m_QuadVAO(0), m_FBO(0), m_RBO(0), m_RenderedTexture(0), m_QuadShader()
    {

    }

    void SpriteRenderer::Init(unsigned int windowWidth, unsigned int windowHeight)
    {
        InitQuadVAO();
        InitQuadShader();

        m_WindowSize.X = windowWidth;
        m_WindowSize.Y = windowHeight;

        // Creating the view matrix
        //m_Camera.AddToPosition(Vector2<float>(320.0f, 0.0f));
        m_QuadShader.SetMat4("uView", m_Camera.GetViewMatrix());

        // Creating the projection matrix
        m_Camera.SetSize(Vector2<float>(windowWidth, windowHeight));
        m_QuadShader.SetMat4("uProjection", m_Camera.GetProjectionMatrix());

        // Preparing for rendering quads by binding the Quad VAO and using the Quad Shader
        m_QuadShader.Use();
        glBindVertexArray(m_QuadVAO);

        // Blending
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        CONNECT_EVENT_FN(EditorCameraAddOffsetEvent, SpriteRenderer::OnEditorCameraAddOffset);

    }

    // Callbacks
    void SpriteRenderer::OnEditorCameraAddOffset(Event& event)
    {
        // Casting it to the right event type
        EditorCameraAddOffsetEvent& offsetEvent = *(EditorCameraAddOffsetEvent*)(&event);

        Vector2<float> offset = offsetEvent.GetOffset();
        offset.Normalize();
        HYDRA_TRACE("Offset: ({0}, {1})", offset.X, offset.Y);

        m_Camera.AddToPosition(Vector2<float>(offset.X, offset.Y) * 0.1);
        UpdateMatrixes();
    }

    void SpriteRenderer::Shutdown()
    {
        // and cleanup, when we're done 
        glDeleteFramebuffers(1, &m_FBO);
        glDeleteTextures(1, &m_RenderedTexture);
        glDeleteRenderbuffers(1, &m_RBO);
    }

    void SpriteRenderer::InitQuadShader()
    {
        m_QuadShader.Load(ShaderTypes::QuadShader);
    }

    // Runs every frame
    void SpriteRenderer::Draw()
    {
        glClear(GL_COLOR_BUFFER_BIT);
        for (std::shared_ptr<Entity> entity : m_Entities)
        {
            DrawEntity(entity);
        }
    }


    void SpriteRenderer::SubmitEntity(const std::shared_ptr<Entity> entity)
    {
        m_Entities.emplace_back(entity);
    }


    void SpriteRenderer::DrawEntity(const std::shared_ptr<Entity> entity)
    {
        auto transform = entity->GetComponent<TransformComponent2D>();
        auto sprite = entity->GetComponent<SpriteComponent2D>();

        if (transform && sprite)
        {
            m_QuadShader.Use();

            // Getting the position data
            Vector2<float> position = transform->GetPosition();
            Vector2<float> scale = transform->GetScale();
            float rotation = transform->GetRotation();

            // Getting the sprite texture
            const Texture2D& texture = sprite->GetTexture();

            // Setting up the model matrix for the sprite
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(position.X, position.Y, 0.0f));
            model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, glm::vec3(scale.X, scale.Y, 0.0f));
            
            m_QuadShader.SetMat4("uModel", model);

            texture.Bind();

            // Actual draw call
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        }
    }

    void SpriteRenderer::UpdateMatrixes()
    {
        m_QuadShader.SetMat4("uView", m_Camera.GetViewMatrix());
        m_QuadShader.SetMat4("uProjection", m_Camera.GetProjectionMatrix());
    }

    void SpriteRenderer::CreateFramebuffer()
    {
        unsigned int width = m_WindowSize.X;
        unsigned int height = m_WindowSize.Y;

        glGenFramebuffers(1, &m_FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);

        glGenTextures(1, &m_RenderedTexture);
        glBindTexture(GL_TEXTURE_2D, m_RenderedTexture);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height,
                0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, 
                GL_TEXTURE_2D, m_RenderedTexture, 0);

        glGenRenderbuffers(1, &m_RBO);
        glBindRenderbuffer(GL_RENDERBUFFER, m_RBO);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RBO);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
            HYDRA_ERROR("Framebuffer is not complete!");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

    }

    void SpriteRenderer::BindFramebuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_FBO);
    }

    void SpriteRenderer::UnbindFramebuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
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