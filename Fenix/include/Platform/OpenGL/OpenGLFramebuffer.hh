#pragma once

#include "Fenix/Renderer/Framebuffer.hh"

namespace fenix {

    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        ~OpenGLFramebuffer();

        void Invalidate();

        void Resize(uint32_t width, uint32_t height) override;

        void Bind() const override;
        void Unbind() const override;

        const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

        uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
    private:
        uint32_t m_RendererID = 0;
        uint32_t m_ColorAttachment = 0, m_DepthStencilAttachment = 0;
        FramebufferSpecification m_Specification;
    };

} // namespace fenix
