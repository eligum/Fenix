#pragma once

#include "Fenix/Renderer/Framebuffer.hh"

namespace Fenix {

    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        ~OpenGLFramebuffer();

        void Resize();

        void Bind() const override;
        void Unbind() const override;

        const FramebufferSpecification& GetSpecification() const override { return m_Specification; }

        uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
    private:
        uint32_t m_RendererID;
        uint32_t m_ColorAttachment, m_DepthStencilAttachment;
        FramebufferSpecification m_Specification;
    };

} // namespace Fenix
