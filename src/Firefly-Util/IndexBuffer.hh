#ifndef INDEX_BUFFER_HH
#define INDEX_BUFFER_HH

#include <cstdint>

class IndexBuffer
{
public:
    IndexBuffer(const uint32_t* data, uint32_t count);
    ~IndexBuffer();

    // Binds this buffer as the current ELEMENT_ARRAY_BUFFER
    void Bind() const;

    // Unbinds this buffer
    void Unbind() const;

    // Returns the element count of the buffer
    uint32_t GetCount() const { return m_Count; }

private:
    uint32_t m_RendererID;
    uint32_t m_Count;
};

#endif
