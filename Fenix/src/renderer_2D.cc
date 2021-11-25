#include "fenix/renderer/renderer_2D.hh"
#include "fenix/renderer/shader.hh"
#include "fenix/renderer/vertex_array.hh"
#include "fenix/renderer/render_command.hh"

#include <array>
#include <glm/gtc/type_ptr.hpp>

namespace fenix {

    struct QuadVertex
    {
        glm::vec3 Position;
        glm::vec4 Color;
        glm::vec2 TexCoord;
        float TexIndex;
        float TilingFactor;
    };

    struct Renderer2DData
    {
        static constexpr uint32_t MaxQuads = 16000;
        static constexpr uint32_t MaxVertices = MaxQuads * 4;
        static constexpr uint32_t MaxIndices = MaxQuads * 6;
        static constexpr uint32_t MaxTextureSlots = 32; // TODO: RenderCaps (Renderer Capabilities)

        Ref<VertexArray> QuadVA;
        Ref<VertexBuffer> QuadVB;
        Ref<Shader> TextureShader;
        Ref<Texture2D> WhiteTexture;

        uint32_t QuadIndexCount = 0;
        QuadVertex* QuadVBBase = nullptr;
        QuadVertex* QuadVBPtr = nullptr;

        std::array<Ref<Texture2D>, MaxTextureSlots> TextureSlots;
        uint32_t TextureSlotIndex = 1; // 0 = white texture

        glm::vec4 QuadVertexPositions[4]; // Quad of size 1.0 centered at the origin with W component = 1.0

        Renderer2D::Statistics Stats;
    };

    static Renderer2DData s_Data;

    void Renderer2D::Init()
    {
        s_Data.QuadVA = VertexArray::Create();
        s_Data.QuadVBBase = new QuadVertex[s_Data.MaxVertices];

        s_Data.QuadVB = VertexBuffer::Create(s_Data.MaxVertices * sizeof(QuadVertex));
        s_Data.QuadVB->SetLayout({
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" },
            { ShaderDataType::Float2, "a_TexCoord" },
            { ShaderDataType::Float, "a_TexIndex" },
            { ShaderDataType::Float, "a_TilingFactor" }
        });
        s_Data.QuadVA->AddVertexBuffer(s_Data.QuadVB);

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

        s_Data.TextureSlots[0] = s_Data.WhiteTexture;

        int32_t samplers[s_Data.MaxTextureSlots];
        for (uint32_t i = 0; i < s_Data.MaxTextureSlots; ++i)
            samplers[i] = i;

        s_Data.TextureShader = Shader::Create("assets/shaders/texture_and_color.glsl");
        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetIntArray("u_Textures", samplers, s_Data.MaxTextureSlots);

        s_Data.QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
        s_Data.QuadVertexPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };
    }

    void Renderer2D::Shuttdown()
    {
        delete[] s_Data.QuadVBBase;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& camera)
    {
        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetMat4("u_ProjView", camera.GetProjViewMatrix());

        StartBatch();
    }

    void Renderer2D::BeginScene(const Camera& camera, const glm::mat4& transform)
    {
        glm::mat4 projView = camera.GetProjection() * glm::inverse(transform);

        s_Data.TextureShader->Bind();
        s_Data.TextureShader->SetMat4("u_ProjView", projView);

        StartBatch();
    }


    void Renderer2D::EndScene()
    {
        Flush();
    }

    void Renderer2D::Flush()
    {
        if (s_Data.QuadIndexCount == 0)
            return; // Nothing to draw

        uint32_t dataSize = reinterpret_cast<uint8_t*>(s_Data.QuadVBPtr) - reinterpret_cast<uint8_t*>(s_Data.QuadVBBase); // Size in bytes
        s_Data.QuadVB->SetData(s_Data.QuadVBBase, dataSize);

        // Bind textures
        for (uint32_t i = 0; i < s_Data.TextureSlotIndex; ++i)
            s_Data.TextureSlots[i]->Bind(i);

        RenderCommand::DrawIndexed(s_Data.QuadVA, s_Data.QuadIndexCount);
        ++s_Data.Stats.DrawCalls;
    }

    void Renderer2D::StartBatch()
    {
        s_Data.QuadIndexCount = 0;
        s_Data.QuadVBPtr = s_Data.QuadVBBase;
        s_Data.TextureSlotIndex = 1;
    }

    void Renderer2D::NextBatch()
    {
        Flush();
        StartBatch();
    }

    //////////////////////////////////////////////////////////////////////////////////////
    // Specifying color //////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
    {
        constexpr std::size_t quadVertexCount = 4;
        constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
        constexpr float textureIndex = 0.0f;
        constexpr float tilingFactor = 1.0f;

        if (s_Data.QuadIndexCount >= s_Data.MaxIndices)
            NextBatch();

        for (std::size_t i = 0; i < quadVertexCount; ++i)
        {
            s_Data.QuadVBPtr->Position     = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVBPtr->Color        = color;
            s_Data.QuadVBPtr->TexCoord     = textureCoords[i];
            s_Data.QuadVBPtr->TexIndex     = textureIndex;
            s_Data.QuadVBPtr->TilingFactor = tilingFactor;
            ++s_Data.QuadVBPtr;
        }

        s_Data.QuadIndexCount += 6;

        ++s_Data.Stats.QuadCount;
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
    {
        glm::mat4 transform(1.0f);
        transform = glm::translate(transform, position);
        transform = glm::scale(transform, { size.x, size.y, 1.0f });
        DrawQuad(transform, color);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const glm::vec4& color)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, rotation, size, color);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const glm::vec4& color)
    {
        glm::mat4 transform(1.0f);
        transform = glm::translate(transform, position);
        transform = glm::rotate(transform, rotation, { 0.0f, 0.0f, 1.0f });
        transform = glm::scale(transform, { size.x, size.y, 1.0f });
        DrawQuad(transform, color);
    }

    //////////////////////////////////////////////////////////////////////////////////////
    // Specifying a texture //////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color)
    {
        constexpr std::size_t quadVertexCount = 4;
        constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

        if (s_Data.QuadIndexCount >= s_Data.MaxIndices)
            NextBatch();

        float textureIndex = 0.0f;
        // We start at 1 because slot 0 is reserved for the white texture.
        for (uint32_t i = 1; i < s_Data.TextureSlotIndex; ++i)
        {
            if (*s_Data.TextureSlots[i].get() == *texture.get())
            {
                textureIndex = static_cast<float>(i);
                break;
            }
        }
        if (textureIndex == 0.0f)
        {
            if (s_Data.TextureSlotIndex >= s_Data.MaxTextureSlots)
                NextBatch();
            textureIndex = static_cast<float>(s_Data.TextureSlotIndex);
            s_Data.TextureSlots[s_Data.TextureSlotIndex] = texture;
            ++s_Data.TextureSlotIndex;
        }

        for (std::size_t i = 0; i < quadVertexCount; ++i)
        {
            s_Data.QuadVBPtr->Position     = transform * s_Data.QuadVertexPositions[i];
            s_Data.QuadVBPtr->Color        = tint_color;
            s_Data.QuadVBPtr->TexCoord     = textureCoords[i];
            s_Data.QuadVBPtr->TexIndex     = textureIndex;
            s_Data.QuadVBPtr->TilingFactor = tiling_factor;
            ++s_Data.QuadVBPtr;
        }

        s_Data.QuadIndexCount += 6;

        ++s_Data.Stats.QuadCount;
    }

    void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color)
    {
        DrawQuad({ position.x, position.y, 0.0f }, size, texture, tiling_factor, tint_color);
    }

    void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color)
    {
        glm::mat4 transform(1.0f);
        transform = glm::translate(glm::mat4(1.0f), position);
        transform = glm::scale(transform, glm::vec3(size.x, size.y, 1.0f));
        DrawQuad(transform, texture, tiling_factor, tint_color);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec2& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color)
    {
        DrawRotatedQuad({ position.x, position.y, 0.0f }, rotation, size, texture, tiling_factor, tint_color);
    }

    void Renderer2D::DrawRotatedQuad(const glm::vec3& position, float rotation, const glm::vec2& size, const Ref<Texture2D>& texture, float tiling_factor, const glm::vec4& tint_color)
    {
        glm::mat4 transform(1.0f);
        transform = glm::translate(glm::mat4(1.0f), position);
        transform = glm::rotate(transform, rotation, { 0.0f, 0.0f, 1.0f });
        transform = glm::scale(transform, glm::vec3(size.x, size.y, 1.0f));
        DrawQuad(transform, texture, tiling_factor, tint_color);
    }

    void Renderer2D::ResetStats()
    {
        s_Data.Stats.QuadCount = 0;
        s_Data.Stats.DrawCalls = 0;
    }

    Renderer2D::Statistics Renderer2D::GetStats()
    {
        return s_Data.Stats;
    }

} // namespace fenix
