#include "fenix/renderer/shader.hh"
#include "fenix/renderer/renderer.hh"
#include "platform/opengl/opengl_shader.hh"

namespace fenix {

    //////////////////////////////////////////////////////////////////////////////////////
    // Shader ////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    Ref<Shader> Shader::Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    FENIX_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(name, vertexSrc, fragmentSrc);
        }

        FENIX_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& vert_filepath, const std::string& frag_filepath)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    FENIX_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(vert_filepath, frag_filepath);
        }

        FENIX_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    Ref<Shader> Shader::Create(const std::string& filepath)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:    FENIX_CORE_ASSERT(false, "RendererAPI::None currently not supported!"); return nullptr;
            case RendererAPI::API::OpenGL:  return CreateRef<OpenGLShader>(filepath);
        }

        FENIX_CORE_ASSERT(false, "Unknow RendererAPI!");
        return nullptr;
    }

    //////////////////////////////////////////////////////////////////////////////////////
    // ShaderLibrary /////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    void ShaderLibrary::Add(const std::string& name, const Ref<Shader>& shader)
    {
        FENIX_CORE_ASSERT(!Exists(name), "Shader already exists!");
        m_Shaders[name] = shader;
    }

    void ShaderLibrary::Add(const Ref<Shader>& shader)
    {
        auto& name = shader->GetName();
        Add(name, shader);
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath)
    {
        auto shader = Shader::Create(filepath);
        Add(name, shader);
        return shader;
    }

    Ref<Shader> ShaderLibrary::GetShader(const std::string& name)
    {
        FENIX_CORE_ASSERT(Exists(name), "Shader not found!");
        return m_Shaders[name];
    }

    bool ShaderLibrary::Exists(const std::string& name) const
    {
        return m_Shaders.find(name) != m_Shaders.end();
    }
}
