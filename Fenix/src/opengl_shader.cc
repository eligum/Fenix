#include "platform/opengl/opengl_shader.hh"
#include "fenix/core/base.hh"

#include <array>
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace fenix {

    static uint32_t ShaderTypeFromString(const std::string& type)
    {
        if (type == "vertex")
            return GL_VERTEX_SHADER;
        if (type == "fragment" || type == "pixel")
            return GL_FRAGMENT_SHADER;
        if (type == "geometry")
            return GL_GEOMETRY_SHADER;

        FENIX_CORE_ASSERT(false, "Unknown shader type!");
        return 0;
    }

    OpenGLShader::OpenGLShader(const std::string& filepath)
    {
        std::string source = ReadFile(filepath);
        auto shaderSources = PreProcess(source);
        Compile(shaderSources);

        // Extract name from filepath
        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind('.');
        auto count = (lastDot == std::string::npos) ? filepath.size() - lastSlash : lastDot - lastSlash;
        m_Name = filepath.substr(lastSlash, count);
    }

    OpenGLShader::OpenGLShader(const std::string& vert_filepath, const std::string& frag_filepath)
    {
        std::string vertSrc = ReadFile(vert_filepath);
        std::string fragSrc = ReadFile(frag_filepath);

        std::unordered_map<uint32_t, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertSrc;
        sources[GL_FRAGMENT_SHADER] = fragSrc;
        Compile(sources);
        m_Name = "Loaded from 2 files";
    }

    OpenGLShader::OpenGLShader(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc)
        : m_Name(name)
    {
        std::unordered_map<uint32_t, std::string> sources;
        sources[GL_VERTEX_SHADER] = vertexSrc;
        sources[GL_FRAGMENT_SHADER] = fragmentSrc;
        Compile(sources);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_RendererID);
    }

    std::string OpenGLShader::ReadFile(const std::string& filepath)
    {
        std::string result;
        std::ifstream in(filepath, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII (Resource Acquisition Is Initialization)
        if (in)
        {
            in.seekg(0, std::ios::end);
            auto size = in.tellg();
            if (size != std::streampos(-1))
            {
                result.resize(size);
                in.seekg(0, std::ios::beg);
                in.read(&result[0], size);
                // in.close();
            }
            else
            {
                FENIX_CORE_ERROR("Could not read from file '{0}'", filepath);
            }
        }
        else
        {
            FENIX_CORE_ERROR("Could not open file '{0}'", filepath);
        }

        return result;
    }

    std::unordered_map<uint32_t, std::string> OpenGLShader::PreProcess(const std::string& source)
    {
        std::unordered_map<uint32_t, std::string> shaderSources;

        const char* typeToken = "#type";
        std::size_t typeTokenLength = strlen(typeToken);
        std::size_t pos = source.find(typeToken, 0); //Start of shader type declaration line
        while (pos != std::string::npos)
        {
            std::size_t eol = source.find_first_of("\r\n", pos); //End of shader type declaration line
            FENIX_CORE_ASSERT(eol != std::string::npos, "Syntax error");
            std::size_t begin = pos + typeTokenLength + 1; //Start of shader type name (after "#type " keyword)
            std::string type = source.substr(begin, eol - begin);
            FENIX_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

            std::size_t nextLinePos = source.find_first_not_of("\r\n", eol); //Start of shader code after shader type declaration line
            FENIX_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
            pos = source.find(typeToken, nextLinePos); //Start of next shader type declaration line

            shaderSources[ShaderTypeFromString(type)] = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
        }

        return shaderSources;
    }

    void OpenGLShader::Compile(const std::unordered_map<uint32_t, std::string>& shaderSources)
    {
        uint32_t program = glCreateProgram();
        FENIX_CORE_ASSERT(shaderSources.size() <= 2, "We only support 2 shaders for now");
        std::array<uint32_t, 2> shaderIDs;
        int shaderIDIndex = 0;
        for (auto& [type, source] : shaderSources)
        {
            uint32_t shader = glCreateShader(type);

            const char* sourceCStr = source.c_str();
            glShaderSource(shader, 1, &sourceCStr, nullptr);
            glCompileShader(shader);

            int isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                int logMaxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logMaxLength);

                std::vector<char> infoLog(logMaxLength);
                glGetShaderInfoLog(shader, logMaxLength, &logMaxLength, &infoLog[0]);

                glDeleteShader(shader);

                FENIX_CORE_ERROR("{0}", infoLog.data());
                FENIX_CORE_ASSERT(false, "Shader compilation failure!");
                break;
            }

            glAttachShader(program, shader);
            shaderIDs[shaderIDIndex++] = shader;
        }

        m_RendererID = program;

        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        int isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
        if (isLinked == GL_FALSE)
        {
            int logMaxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logMaxLength);

            // The logMaxLength includes the NULL character
            std::vector<char> infoLog(logMaxLength);
            glGetProgramInfoLog(program, logMaxLength, &logMaxLength, &infoLog[0]);

            // We don't need the program nor the shaders anymore.
            glDeleteProgram(program);
            for (auto id : shaderIDs)
                glDeleteShader(id);

            FENIX_CORE_ERROR("{0}", infoLog.data());
            FENIX_CORE_ASSERT(false, "Shader link failure!");
            return;
        }

        for (auto id : shaderIDs)
        {
            glDetachShader(program, id);
            glDeleteShader(id);
        }
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_RendererID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::SetInt(const std::string& name, int value)
    {
        UploadUniformInt(name, value);
    }

    void OpenGLShader::SetIntArray(const std::string& name, int* values, uint32_t count)
    {
        UploadUniformIntArray(name, values, count);
    }

    void OpenGLShader::SetFloat(const std::string& name, float value)
    {
        UploadUniformFloat(name, value);
    }

    void OpenGLShader::SetFloat2(const std::string& name, const glm::vec2& value)
    {
        UploadUniformFloat2(name, value);
    }

    void OpenGLShader::SetFloat3(const std::string& name, const glm::vec3& value)
    {
        UploadUniformFloat3(name, value);
    }

    void OpenGLShader::SetFloat4(const std::string& name, const glm::vec4& value)
    {
        UploadUniformFloat4(name, value);
    }

    void OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
    {
        UploadUniformMat4(name, value);
    }

    void OpenGLShader::UploadUniformInt(const std::string& name, int value)
    {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1i(location, value);
    }

    void OpenGLShader::UploadUniformIntArray(const std::string& name, int* values, uint32_t count)
    {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1iv(location, count, values);
    }

    void OpenGLShader::UploadUniformFloat(const std::string& name, float value)
    {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform1f(location, value);
    }

    void OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2& value)
    {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform2f(location, value.x, value.y);
    }

    void OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3& value)
    {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform3f(location, value.x, value.y, value.z);
    }

    void OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4& value)
    {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::UploadUniformMat3(const std::string& name, const glm::mat3& matrix)
    {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

    void OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
    {
        int location = glGetUniformLocation(m_RendererID, name.c_str());
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
    }

} // namespace fenix
