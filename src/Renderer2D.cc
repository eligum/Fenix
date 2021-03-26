#include "Fenix/Renderer/Renderer2D.hh"

#include "Fenix/Renderer/Shader.hh"
#include "Fenix/Renderer/VertexArray.hh"
#include "Fenix/Renderer/RenderCommand.hh"

#include <glm/gtc/type_ptr.hpp>

namespace Fenix {

    struct Renderer2DStorage
    {
        Ref<VertexArray> QuadVA;
        Ref<Shader> TextureShader;
        Ref<Texture2D> WhiteTexture;
    };

    static Renderer2DStorage* s_Data;

    void Renderer2D::Init()
    {
        s_Data = new Renderer2DStorage();

        s_Data->QuadVA = VertexArray::Create();

        float squareVertices[4 * 5] = {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };
        Ref<VertexBuffer> squareVB;
        squareVB = VertexBuffer::Create(squareVertices, sizeof(squareVertices));
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Pos" },
            { ShaderDataType::Float2, "a_TexCoord" },
        };
        squareVB->SetLayout(layout);
        s_Data->QuadVA->AddVertexBuffer(squareVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        Ref<IndexBuffer> squareIB;
        squareIB = IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
        s_Data->QuadVA->SetIndexBuffer(squareIB);

        s_Data->WhiteTexture = Texture2D::Create(1, 1);
        uint32_t WhiteTextureData = 0xffffffff;
        s_Data->WhiteTexture->SetData(&WhiteTextureData, sizeof(uint32_t));

        s_Data->TextureShader = Shader::Create("examples/assets/shaders/texture_and_color.glsl");
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Shuttdown()
    {
        delete s_Data;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetMat4("u_ProjView", camera.GetProjViewMatrix());
    }

    void Renderer2D::EndScene()
    {
    }

    //////////////////////////////////////////////////////////////////////////////////////
    // Specifying color //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    void Renderer2D::DrawQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, rotation, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color)
    {
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetFloat4("u_Color", color);

        s_Data->WhiteTexture->Bind(0);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform = glm::scale(transform, glm::vec3(size.x, size.y, 1.0f));
        transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        s_Data->TextureShader->SetMat4("u_Transform", transform);

        s_Data->QuadVA->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVA); // TEMP: Immediate mode render
    }

    //////////////////////////////////////////////////////////////////////////////////////
    // Specifying a texture //////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    void Renderer2D::DrawQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture)
    {
        DrawQuad({ position.x, position.y, 0.0f }, rotation, size, texture);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture)
    {
        s_Data->TextureShader->Bind();
        s_Data->TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));

        texture->Bind(0);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        transform = glm::scale(transform, glm::vec3(size.x, size.y, 1.0f));
        transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        s_Data->TextureShader->SetMat4("u_Transform", transform);

        s_Data->QuadVA->Bind();
        RenderCommand::DrawIndexed(s_Data->QuadVA); // TEMP: Immediate mode render
    }

} // namespace Fenix
