#pragma once

#include "fenix/renderer/vertex_array.hh"

namespace fenix {

    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        void Bind() const override;
        void Unbind() const override;

        void AddVertexBuffer(const Ref<VertexBuffer>& vertex_buffer) override;
        void SetIndexBuffer(const Ref<IndexBuffer>& index_buffer)  override;

        const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
        const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }
    private:
        uint32_t m_RendererID;
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
    };

} // namespace fenix
