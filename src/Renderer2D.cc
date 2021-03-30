#include "Fenix/Renderer/Renderer2D.hh"

#include "Fenix/Renderer/Shader.hh"
#include "Fenix/Renderer/VertexArray.hh"
#include "Fenix/Renderer/RenderCommand.hh"

#include <glm/gtc/type_ptr.hpp>

namespace Fenix {

    struct QuadVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        // TODO: texid
    };

    struct Renderer2DData
    {
        const uint32_t MaxQuads = 4096;
        const uint32_t MaxVertices = MaxQuads * 4;
        const uint32_t MaxIndices = MaxQuads * 6;
        Ref<VertexArray> QuadVA;
        Ref<VertexBuffer> QuadVB;
        Ref<Shader> TextureShader;
        Ref<Texture2D> WhiteTexture;

        uint32_t QuadIndexCount = 0;
        QuadVertex* QuadVertexBufferBase = nullptr;
        QuadVertex* QuadVertexBufferPtr = nullptr;
    };

    static Renderer2DData s_Data;

    void Renderer2D::Init()
    {
        s_Data.QuadVA = VertexArray::Create();

        s_Data.QuadVB = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
        s_Data.QuadVB->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" },
            { ShaderDataType::Float2, "a_TexCoord" }
        });
        s_Data.QuadVA->AddVertexBuffer(s_Data.QuadVB);

        s_Data.QuadVertexBufferBase = new QuadVertex[s_Data.MaxVertices];

        uint32_t* quadIndices = new uint32_t[s_Data.MaxIndices];
        uint32_t offset = 0;
        for (uint32_t i = 0; i < s_Data.MaxIndices; i += 6)
        {
            quadIndices[i + 0] = offset + 0;
            quadIndices[i + 1] = offset + 1;
            quadIndices[i + 2] = offset + 2;

            quadIndices[i + 3] = offset + 2;
            quadIndices[i + 4] = offset + 3;
            quadIndices[i + 5] = offset + 0;

            offset += 4;
        }

        Ref<IndexBuffer> quadIB = IndexBuffer::Create(quadIndices, s_Data.MaxIndices);
        s_Data.QuadVA->SetIndexBuffer(quadIB);
        delete[] quadIndices;

        s_Data.WhiteTexture = Texture2D::Create(1, 1);
        uint32_t WhiteTextureData = 0xffffffff;
        s_Data.WhiteTexture->SetData(&WhiteTextureData, sizeof(uint32_t));

        s_Data.TextureShader = Shader::Create("examples/assets/shaders/texture_and_color.glsl");
        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetInt("u_Texture", 0);
    }

    void Renderer2D::Shuttdown()
    {
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetMat4("u_ProjView", camera.GetProjViewMatrix());

        s_Data.QuadIndexCount = 0;
        s_Data.QuadVertexBufferPtr = s_Data.QuadVertexBufferBase;
    }

    void Renderer2D::EndScene()
    {
        uint32_t dataSize = (uint8_t*)s_Data.QuadVertexBufferPtr - (uint8_t*)s_Data.QuadVertexBufferBase;
        s_Data.QuadVB->SetData(s_Data.QuadVertexBufferBase, dataSize);

        Flush();
    }

    void Renderer2D::Flush()
    {
        RenderCommand::DrawIndexed(s_Data.QuadVA, s_Data.QuadIndexCount);
    }

    //////////////////////////////////////////////////////////////////////////////////////
    // Specifying color //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        s_Data.QuadVertexBufferPtr->Position = position;
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 0.0f };
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y, position.z };
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 0.0f };
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = { position.x + size.x, position.y + size.y, position.z };
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 1.0f, 1.0f };
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadVertexBufferPtr->Position = { position.x, position.y + size.y, position.z };
        s_Data.QuadVertexBufferPtr->Color = color;
        s_Data.QuadVertexBufferPtr->TexCoord = { 0.0f, 1.0f };
        s_Data.QuadVertexBufferPtr++;

        s_Data.QuadIndexCount += 6;

        /*
        s_Data.TextureShader->SetFloat4("u_Color", color);
        s_Data.TextureShader->SetFloat("u_TilingFactor", 1.0f);

        s_Data.WhiteTexture->Bind(0);

        glm::mat4 transform(1.0f);
        transform = glm::translate(glm::mat4(1.0f), position);
        transform = glm::scale(transform, glm::vec3(size.x, size.y, 1.0f));
        s_Data.TextureShader->SetMat4("u_Transform", transform);

        s_Data.QuadVA->Bind();
        RenderCommand::DrawIndexed(s_Data.QuadVA); // TEMP: Immediate mode render
        */
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, rotation, size, color);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color)
    {
        s_Data.TextureShader->SetFloat4("u_Color", color);
        s_Data.TextureShader->SetFloat("u_TilingFactor", 1.0f);

        s_Data.WhiteTexture->Bind(0);

        glm::mat4 transform(1.0f);
        transform = glm::translate(glm::mat4(1.0f), position);
        transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(size.x, size.y, 1.0f));
        s_Data.TextureShader->SetMat4("u_Transform", transform);

        s_Data.QuadVA->Bind();
        RenderCommand::DrawIndexed(s_Data.QuadVA); // TEMP: Immediate mode render
    }

    //////////////////////////////////////////////////////////////////////////////////////
    // Specifying a texture //////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, texture, tiling_factor);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor)
    {
        s_Data.TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
        s_Data.TextureShader->SetFloat("u_TilingFactor", tiling_factor);

        texture->Bind(0);

        glm::mat4 transform(1.0f);
        transform = glm::translate(glm::mat4(1.0f), position);
        transform = glm::scale(transform, glm::vec3(size.x, size.y, 1.0f));
        s_Data.TextureShader->SetMat4("u_Transform", transform);

        s_Data.QuadVA->Bind();
        RenderCommand::DrawIndexed(s_Data.QuadVA); // TEMP: Immediate mode render
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, rotation, size, texture, tiling_factor);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor)
    {
        s_Data.TextureShader->SetFloat4("u_Color", glm::vec4(1.0f));
        s_Data.TextureShader->SetFloat("u_TilingFactor", tiling_factor);

        texture->Bind(0);

        glm::mat4 transform(1.0f);
        transform = glm::translate(glm::mat4(1.0f), position);
        transform = glm::rotate(transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
        transform = glm::scale(transform, glm::vec3(size.x, size.y, 1.0f));
        s_Data.TextureShader->SetMat4("u_Transform", transform);

        s_Data.QuadVA->Bind();
        RenderCommand::DrawIndexed(s_Data.QuadVA); // TEMP: Immediate mode render
    }

} // namespace Fenix
