#include "Hazel/Renderer/RenderCommand.hh"

#include "Platform/OpenGL/OpenGLRendererAPI.hh"

namespace Hazel {

    RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}
