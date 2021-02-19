#include "ResourceManager.hh"

#include <iostream>
#include <sstream>
#include <fstream>

// Instantiate static variables
std::unordered_map<std::string, Shader> ResourceManager::ShaderTable;


Shader ResourceManager::LoadShader(std::string name, const char *vert_file,const char *frag_file, const char *geom_file)
{
    ShaderTable[name] = loadShaderFromFile(vert_file, frag_file, geom_file);
    return ShaderTable[name];
}

Shader ResourceManager::GetShader(std::string name)
{
    return ShaderTable.at(name);
}

void ResourceManager::Clear()
{
    for (auto it : ShaderTable)
        glDeleteProgram(it.second.m_ID);
}

Shader ResourceManager::loadShaderFromFile(const char* vert_file, const char* frag_file, const char* geom_file)
{
    std::string vert_code;
    std::string frag_code;
    std::string geom_code;
    try
    {
        // Open files in read mode
        std::ifstream v_file(vert_file);
        std::ifstream f_file(frag_file);
        std::stringstream v_stream, f_stream;
        // Read file's buffer contents into streams
        v_stream << v_file.rdbuf();
        f_stream << f_file.rdbuf();
        // Close files
        v_file.close();
        f_file.close();
        // Convert stream into string
        vert_code = v_stream.str();
        frag_code = f_stream.str();
        // Do the same if geom_file is not null.
        if (geom_file != nullptr)
        {
            std::ifstream g_file(geom_file);
            std::stringstream g_stream;
            g_stream << g_file.rdbuf();
            g_file.close();
            geom_code = g_stream.str();
        }
    }
    catch (std::exception e)
    {
        std::cerr << "ERROR::SHADER: Failed to read shader files." << std::endl;
    }
    const char* v_code = vert_code.c_str();
    const char* f_code = frag_code.c_str();
    const char* g_code = geom_code.c_str();
    // Construct shader object.
    Shader shader;
    shader.Compile(v_code, f_code, (geom_file != nullptr) ? g_code : nullptr);
    return shader;
}
