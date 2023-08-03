#pragma once
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Hydra
{
    struct ShaderSources
    {
        const char* QuadVertexSource = R"(
            #version 330 core
            layout (location = 0) in vec3 aPos;
            layout (location = 1) in vec3 aColor;
            layout (location = 2) in vec2 aTextureCoord;
            
            out vec3 color;
            out vec2 textureCoord;

            uniform mat4 uModel;
            uniform mat4 uView;
            uniform mat4 uProjection;

            void main()
            {
	            gl_Position = uProjection * uView * uModel * vec4(aPos.xyz, 1.0f);
                // Outputs
                color = aColor;
                textureCoord = aTextureCoord;
            }
        )";

        const char* QuadFragmentSource = R"(
            #version 330 core
            out vec4 fragColor;
            
            in vec3 color;
            in vec2 textureCoord;

            uniform sampler2D textureSampler;
        

            void main()
            {
	            fragColor = texture(textureSampler, textureCoord);
            }
        )";
    };

    enum class ShaderTypes
    {
        QuadShader = 0,
    };

    class Shader
    {
    public:
        Shader() = default;
        ~Shader();
        
        // Disabling copying and assignment
        Shader(const Shader& other) = delete;
        Shader& operator==(const Shader& other) = delete;

        void Load(ShaderTypes type);
        void Use() const;

        // Setting uniforms
        void SetMat4(const char* uniformName, const glm::mat4& matrix) const;
    private:
        unsigned int m_ProgramID;

        unsigned int Compile(unsigned int glType, const char* source);
        void Link(unsigned int vertexShader, unsigned int fragmentShader);

        ShaderSources m_Sources;
    };
} 
