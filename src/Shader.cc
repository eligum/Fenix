#include "Hazel/Renderer/Shader.hh"
#include "Hazel/Renderer/Renderer.hh"

#include "Platform/OpenGL/OpenGLShader.hh"

namespace Hazel {

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        HZ_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& vert_filepath, const std::string& frag_filepath)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(vert_filepath, frag_filepath);
        }

        HZ_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& filepath)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    HZ_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLShader>(filepath);
        }

        HZ_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }
}
