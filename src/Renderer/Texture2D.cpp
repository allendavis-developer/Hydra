#include <glad/glad.h>
#include <stb_image.h>
#include <fstream>

#include "Texture2D.h"
#include "Core/Log.h"

namespace Hydra {

    Texture2D::~Texture2D()
    {
        if (m_TextureID != 0)
            glDeleteTextures(1, &m_TextureID);
    }

    void Texture2D::LoadFromFile(const std::string& filepath)
    {
        glGenTextures(1, &m_TextureID);
        stbi_set_flip_vertically_on_load(true);
        // Loading the image with stb
        unsigned char* data = stbi_load(filepath.c_str(), &m_Width, &m_Height, &m_ColorChannelsCount, 0);
        
        // Binding the texture so that all operations done after will be done on this texture
        Bind();

        // Set the texture wrapping/filtering options 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);


        // Finding whether the color channel of this texture is GL_RGB or GL_RGBA
        int glColorChannels;
        switch (m_ColorChannelsCount)
        {
        case 3:
            glColorChannels = GL_RGB;
            break;
        case 4:
            glColorChannels = GL_RGBA;
            break;
        default:
            HYDRA_ERROR("Unsupported amount of color channels ({0}) loaded by Texture2D!", 
                m_ColorChannelsCount);
            glColorChannels = GL_RGB;
            break;
        }

        if (data)
        {
            HYDRA_INFO("Successfully loaded texture file at {0}! with width {1} and height {2}", 
                filepath, m_Width, m_Height);
            // Passing the image data to OpenGL
            glTexImage2D(GL_TEXTURE_2D, 0, glColorChannels, m_Width, m_Height, 0, glColorChannels, 
                GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else 
        {
            // Data is null : Couldn't load the file (possibly a filepath problem)
            HYDRA_ERROR("Failed to load file at filepath!: {0}", filepath);
        }

        stbi_image_free(data);

    }

    void Texture2D::Bind() const
    {
        glActiveTexture(GL_TEXTURE0); 
        glBindTexture(GL_TEXTURE_2D, m_TextureID);
    }
}