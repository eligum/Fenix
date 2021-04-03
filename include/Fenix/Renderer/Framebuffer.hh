#pragma once

#include "Fenix/Core/Base.hh"

namespace Fenix {

    struct FramebufferSpecification
    {
        uint32_t Width, Height;
        uint32_t Samples = 1;
    };

    class Framebuffer
    {
    public:
        virtual ~Framebuffer() = default;

        virtual const FramebufferSpecification& GetSpecification() const = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual uint32_t GetColorAttachmentRendererID() const = 0;

        static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
    };

} // namespace Fenix
