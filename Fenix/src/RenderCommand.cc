#include "Fenix/Renderer/RenderCommand.hh"

#include "Platform/OpenGL/OpenGLRendererAPI.hh"

namespace Fenix {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
