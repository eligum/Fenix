#include <tuple>
#include "glm/glm.hpp"

std::tuple<glm::vec3, glm::vec3>
GetBoxCoords(float* model_vertices, std::size_t count, std::size_t offset_count)
{
    float max_x, min_x, max_y, min_y, max_z, min_z;
    max_x = min_x = model_vertices[0];
    max_y = min_y = model_vertices[1];
    max_z = min_z = model_vertices[2];
    for (std::size_t i = 0; i < count; i += offset_count)
    {
        // Check maximum
        if (model_vertices[i] > max_x) max_x = model_vertices[i];
        if (model_vertices[i + 1] > max_y) max_y = model_vertices[i + 1];
        if (model_vertices[i + 2] > max_z) max_z = model_vertices[i + 2];
        // Check minimum
        if (model_vertices[i] < min_x) min_x = model_vertices[i];
        if (model_vertices[i + 1] < min_y) min_y = model_vertices[i + 1];
        if (model_vertices[i + 2] < min_z) min_z = model_vertices[i + 2];
    }

    return {
        glm::vec3((max_x + min_x) / 2, min_y, (max_z + min_z) / 2),
        glm::vec3((max_x + min_x) / 2, (max_y + min_y) / 2, (max_z + min_z) / 2)
    };
}
