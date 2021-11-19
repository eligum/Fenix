#include "Fenix/Renderer/RenderCommand.hh"

#include "Platform/OpenGL/OpenGLRendererAPI.hh"

namespace fenix {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
