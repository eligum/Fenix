#ifndef RESOURCE_MANAGER_HH
#define RESOURCE_MANAGER_HH

#include <unordered_map>
#include "Shader.hh"

/**
 * A static singleton that host several functions to load Textures and Shaders.
 *
 * Each loaded texture and/or shader is also stored for future reference by string handles.
 * All functions and resources are static and no constructor is defined.
 */
class ResourceManager
{
public:
    static std::unordered_map<std::string, Shader> ShaderTable;

public:
    ResourceManager() = delete;

    /**
     * Loads and generates a shader program from file.
     */
    static Shader LoadShader(std::string name,
                             const char* vert_file,
                             const char* frag_file,
                             const char* geom_file = nullptr);

    /**
     * Retrive a stored shader.
     */
    static Shader GetShader(std::string name);

    /**
     * Properly de-allocates all loaded resources.
     */
    static void Clear();

private:
    // Loads and generates a shader from file
    static Shader loadShaderFromFile(const char* vert_file,
                                     const char* frag_file,
                                     const char* geom_file);
};

#endif
