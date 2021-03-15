#include "Platform/OpenGL/OpenGLTexture.hh"

#include <glad/glad.h>
#include <stb_image.h>

namespace Hazel {

    OpenGLTexture2D::OpenGLTexture2D(const std::string& filepath)
        : m_Path(filepath)
    {
        int width, height, channels;
        stbi_uc* data = stbi_load(filepath.c_str(), &width, &height, &channels, STBI_default);
        HZ_CORE_ASSERT(data, "Failed to load image");
        m_Width = static_cast<uint32_t>(width);
        m_Height = static_cast<uint32_t>(height);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
        glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

        glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_RendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_RendererID);
    }

} // namespace Hazel
