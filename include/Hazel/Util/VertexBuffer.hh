#ifndef VERTEX_BUFFER_HH
#define VERTEX_BUFFER_HH

#include <cstdint>

class VertexBuffer
{
public:
    VertexBuffer(const void* data, uint32_t size);
    ~VertexBuffer();
    void Bind() const;
    void Unbind() const;

private:
    uint32_t m_RendererID;
};

#endif
