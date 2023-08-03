#pragma once        
#include <string>

namespace Hydra {
    class Texture2D
    {
    public:
        Texture2D() = default;
        ~Texture2D();
        // Disabling copying and assignment
        Texture2D(const Texture2D& other) = delete;
        Texture2D& operator==(const Texture2D& other) = delete;

        void LoadFromFile(const std::string& filepath);
        void Bind() const;
    private:
        unsigned int m_TextureID;
        int m_Width;
        int m_Height;
        int m_ColorChannelsCount;
    };
}