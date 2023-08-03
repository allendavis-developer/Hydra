#include <glad/glad.h>
#include <fstream>
#include <sstream>

#include "Shader.h"
#include "Core/Log.h"

namespace Hydra {

    
    void Shader::Load(ShaderTypes type)
    {
        const char* vertexSource;
        const char* fragmentSource;

        // Finding the revelant source from m_Sources which is ShaderSources
        switch (type)
        {
        case ShaderTypes::QuadShader:
            vertexSource = m_Sources.QuadVertexSource;
            fragmentSource = m_Sources.QuadFragmentSource;
            break;
        default:
            HYDRA_ERROR("Invalid shader type passed into Shader::LoadFromFile()!");
            vertexSource = "";
            fragmentSource = "";
            break;
        }

        unsigned int vertexShader = Compile(GL_VERTEX_SHADER, vertexSource);
        unsigned int fragmentShader = Compile(GL_FRAGMENT_SHADER, fragmentSource);

        // Creating our shader program
        m_ProgramID = glCreateProgram();
        Link(vertexShader, fragmentShader);
        
    }

    unsigned int Shader::Compile(unsigned int glType, const char* source)
    {
        // Compilation
        unsigned int shader = glCreateShader(glType);
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);
        
        // Error logging
        int success;
        char infoLog[512];
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

        std::string stringType;

        switch (glType)
        {
        case GL_VERTEX_SHADER:
            stringType = "Vertex";
            break;
        case GL_FRAGMENT_SHADER:
            stringType = "Fragment";
            break;
        }

        if (!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infoLog);
            HYDRA_ERROR("{0} Shader compilation failed: {1}", stringType, infoLog);
            return 0;
        }

        HYDRA_INFO("Successfully compiled {0} shader!", stringType);

        return shader;
    }

    void Shader::Link(unsigned int vertexShader, unsigned int fragmentShader)
    {
        // Attaching and linking
        glAttachShader(m_ProgramID, vertexShader);
        glAttachShader(m_ProgramID, fragmentShader);
        glLinkProgram(m_ProgramID);

        // Error logging
        int success;
        char infoLog[512];
        glGetProgramiv(m_ProgramID, GL_LINK_STATUS, &success);
        if (!success) 
        {
            glGetProgramInfoLog(m_ProgramID, 512, NULL, infoLog);
            HYDRA_ERROR("Failed to link shader program!: {0}", infoLog);
        }

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);


        HYDRA_INFO("Successfully linked shader program!");
    }


    void Shader::Use() const
    {
        glUseProgram(m_ProgramID);
    }

    void Shader::SetMat4(const char* uniformName, const glm::mat4& matrix) const
    {
        Use();
        unsigned int uniformLocation = glGetUniformLocation(m_ProgramID, uniformName);
        glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    Shader::~Shader()
    {
        if (m_ProgramID != 0)
        {
            glDeleteProgram(m_ProgramID);
        }
    }

    
}