#include "fenix/renderer/render_command.hh"
#include "platform/opengl/opengl_renderer_API.hh"

namespace fenix {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
