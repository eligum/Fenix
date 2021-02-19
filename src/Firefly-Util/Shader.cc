#include "Shader.hh"
#include <iostream>

Shader& Shader::Use()
{
    glUseProgram(m_ID);
    return *this;
}

void Shader::Compile(const char *vert_source, const char *frag_source, const char *geom_source)
{
    unsigned int vertexID, fragmentID, geometryID;
    // Vertex shader
    vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &vert_source, NULL);
    glCompileShader(vertexID);
    checkCompileErrors(vertexID, "VERTEX");
    // Fragment shader
    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &frag_source, NULL);
    glCompileShader(fragmentID);
    checkCompileErrors(fragmentID, "FRAGMENT");
    // If geometry shader source is given
    if (geom_source != nullptr)
    {
        geometryID = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometryID, 1, &geom_source, NULL);
        glCompileShader(geometryID);
        checkCompileErrors(geometryID, "GEOMETRY");
    }
    // Shader Program
    m_ID = glCreateProgram();
    glAttachShader(m_ID, vertexID);
    glAttachShader(m_ID, fragmentID);
    if (geom_source != nullptr)
        glAttachShader(m_ID, geometryID);
    glLinkProgram(m_ID);
    checkCompileErrors(m_ID, "PROGRAM");
    // Delete the shaders as they're already linked into our program and no longer necessary
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);
    if (geom_source != nullptr)
        glDeleteShader(geometryID);
}


void Shader::SetFloat(const char *name, float value, bool useShader)
{
    if (useShader) Use();
    glUniform1f(glGetUniformLocation(m_ID, name), value);
}
void Shader::SetInteger(const char *name, GLint value, bool useShader)
{
    if (useShader) Use();
    glUniform1i(glGetUniformLocation(m_ID, name), value);
}
void Shader::SetVector2f(const char *name, float x, float y, bool useShader)
{
    if (useShader) Use();
    glUniform2f(glGetUniformLocation(m_ID, name), x, y);
}
void Shader::SetVector2f(const char *name, const glm::vec2 &value, bool useShader)
{
    if (useShader) Use();
    glUniform2f(glGetUniformLocation(m_ID, name), value.x, value.y);
}
void Shader::SetVector3f(const char *name, float x, float y, float z, bool useShader)
{
    if (useShader) Use();
    glUniform3f(glGetUniformLocation(m_ID, name), x, y, z);
}
void Shader::SetVector3f(const char *name, const glm::vec3 &value, bool useShader)
{
    if (useShader) Use();
    glUniform3f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z);
}
void Shader::SetVector4f(const char *name, float x, float y, float z, float w, bool useShader)
{
    if (useShader) Use();
    glUniform4f(glGetUniformLocation(m_ID, name), x, y, z, w);
}
void Shader::SetVector4f(const char *name, const glm::vec4 &value, bool useShader)
{
    if (useShader) Use();
    glUniform4f(glGetUniformLocation(m_ID, name), value.x, value.y, value.z, value.w);
}
void Shader::SetMatrix4(const char *name, const glm::mat4 &matrix, bool useShader)
{
    if (useShader) Use();
    glUniformMatrix4fv(glGetUniformLocation(m_ID, name), 1, GL_FALSE, glm::value_ptr(matrix));
}


void Shader::checkCompileErrors(unsigned int object, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(object, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER: Compile-time error: Type: " << type << "\n"
                      << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(m_ID, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER: Link-time error: Type: " << type << "\n"
                      << infoLog << std::endl;
        }
    }
}
