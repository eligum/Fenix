#include "Hazel/Renderer/Shader.hh"
#include "Hazel/Renderer/Renderer.hh"

#include "Platform/OpenGL/OpenGLShader.hh"

namespace Hazel {

    Shader* Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return new OpenGLShader(name, vertexSrc, fragmentSrc);
        }

        HZ_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    Shader* Shader::Create(const std::string& filepath)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return new OpenGLShader(filepath);
        }

        HZ_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
}
