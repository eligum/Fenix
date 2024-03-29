#include "editor_layer.hh"
#include <fenix/util/instrumentor.hh>
#include <fenix/util/platform_utils.hh>

#include <imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <filesystem>

static constexpr float ASPECT_RATIO = 16.0f / 9.0f;

namespace fenix {

    EditorLayer::EditorLayer()
        : Layer("EditorLayer"), m_CameraController(ASPECT_RATIO, true)
    {}

    void EditorLayer::OnAttach()
    {
        FENIX_PROFILE_FUNCTION();

        m_Texture = Texture2D::Create("assets/textures/checkerboard.jpg");

        FramebufferSpecification framebufSpec;
        framebufSpec.Width  = 1280;
        framebufSpec.Height = 720;
        m_Framebuffer = Framebuffer::Create(framebufSpec);

        m_ActiveScene = CreateRef<Scene>();
#if 0
        m_SquareEntity = m_ActiveScene->CreateEntity("green_square");
        m_SquareEntity.AddComponent<SpriteRendererComponent>(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });

        auto red_square = m_ActiveScene->CreateEntity("red_square");
        red_square.AddComponent<SpriteRendererComponent>(glm::vec4{ 1.0f, 0.0f, 0.0f, 1.0f });

        m_CameraEntity = m_ActiveScene->CreateEntity("Camera Entity A");
        m_CameraEntity.AddComponent<CameraComponent>();

        m_SecondCamera = m_ActiveScene->CreateEntity("Camera Entity B");
        auto& cc = m_SecondCamera.AddComponent<CameraComponent>();
        cc.Primary = false;

        class CameraController : public ScriptableEntity
        {
        public:
            void OnCreate()
            {
            }

            void OnDestroy()
            {
            }

            void OnUpdate(Timestep ts)
            {
                auto& translation = GetComponent<TransformComponent>().Translation;
                constexpr float speed = 5.0f;

                if (Input::IsKeyPressed(Key::A))
                    translation.x -= speed * ts;
                if (Input::IsKeyPressed(Key::D))
                    translation.x += speed * ts;
                if (Input::IsKeyPressed(Key::W))
                    translation.y += speed * ts;
                if (Input::IsKeyPressed(Key::S))
                    translation.y -= speed * ts;
            }
        };

        m_CameraEntity.AddComponent<NativeScriptComponent>().Bind<CameraController>();
#endif
        m_SceneHierarchyPanel.SetContext(m_ActiveScene);

    }

    void EditorLayer::OnDetach()
    {
        FENIX_PROFILE_FUNCTION();
    }

    void EditorLayer::OnUpdate(Timestep ts)
    {
        FENIX_PROFILE_FUNCTION();

        // Resize
        FramebufferSpecification spec = m_Framebuffer->GetSpecification();
        if (m_ViewportSize.x > 0.0f && m_ViewportSize.y > 0.0f // Zero sized framebuffer is invalid
            && (spec.Width != m_ViewportSize.x || spec.Height != m_ViewportSize.y))
        {
            m_Framebuffer->Resize(static_cast<uint32_t>(m_ViewportSize.x), static_cast<uint32_t>(m_ViewportSize.y));
            m_CameraController.OnResize(m_ViewportSize.x, m_ViewportSize.y);
            m_ActiveScene->OnViewportResize(static_cast<uint32_t>(m_ViewportSize.x), static_cast<uint32_t>(m_ViewportSize.y));
        }

        // Update
        if (m_ViewportFocused)
            m_CameraController.OnUpdate(ts);
        m_FPS = 1.0f / ts;

        // Render
        Renderer2D::ResetStats();

        m_Framebuffer->Bind();
        RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        RenderCommand::Clear();

        // Update scene
        m_ActiveScene->OnUpdate(ts);

        // Renderer2D::BeginScene(m_CameraController.GetCamera());
        // Stress test
        // for (float y = -5.0f; y <= 5.0f; y += 0.5f)
        // {
        //     for (float x = -5.0f; x <= 5.0f; x += 0.5f)
        //     {
        //         glm::vec4 color = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 1.0f };
        //         Renderer2D::DrawRotatedQuad({ x, y, 0.1f }, glm::radians(10.0f), { 0.45f, 0.45f }, color);
        //     }
        // }
        // Renderer2D::EndScene();

        m_Framebuffer->Unbind();
    }

    void EditorLayer::OnImGuiRender()
    {
        FENIX_PROFILE_FUNCTION();

        static bool dockspaceOpen                 = true;
        static bool opt_fullscreen                = true;
        static bool opt_padding                   = false;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceOpen, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // DockSpace
        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();
        float min_win_size = style.WindowMinSize.x;
        style.WindowMinSize.x = 385.0f;
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        style.WindowMinSize.x = min_win_size;

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                // ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                ImGui::MenuItem("Padding", NULL, &opt_padding);
                ImGui::Separator();

                if (ImGui::MenuItem("New", "Ctrl+N"))
                    NewScene();

                if (ImGui::MenuItem("Open...", "Ctrl+O"))
                    OpenScene();

                if (ImGui::MenuItem("Save As...", "Ctrl+Shift+S"))
                    SaveSceneAs();

                // if (ImGui::MenuItem("Save", "Ctrl+S"))
                // {
                //     std::filesystem::create_directories("assets/scenes");
                //     std::string file_path = FileDialog::SaveFile("Fenix Scene (*.fenix)\0*.fenix\0");
                // }

                ImGui::Separator();
                if (ImGui::MenuItem("Exit")) {
                    Application::GetApp().Close();
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        // Scene Hierarchy panel
        m_SceneHierarchyPanel.OnImGuiRender();

        ImGui::Begin("2D Renderer Stats");

        auto stats = Renderer2D::GetStats();
        ImGui::Text("Draw calls: %d", stats.DrawCalls);
        ImGui::Text("Quads: %d", stats.QuadCount);
        ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
        ImGui::Text("Indices: %d", stats.GetTotalIndexCount());
        ImGui::Text("FPS: %d", m_FPS);

        ImGui::End();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Viewport");

        m_ViewportFocused = ImGui::IsWindowFocused();
        m_ViewportHovered = ImGui::IsWindowHovered();
        Application::GetApp().GetImGuiLayer()->BlockEvents(!m_ViewportFocused || !m_ViewportHovered);

        ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
        m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

        uint32_t textureID = m_Framebuffer->GetColorAttachmentRendererID();
        ImGui::Image(reinterpret_cast<void*>(textureID), { m_ViewportSize.x, m_ViewportSize.y }, ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::End(); // End dockspace
    }

    void EditorLayer::OnEvent(Event& e)
    {
        // FENIX_WARN("Recived event {0}", e.GetName());
        m_CameraController.OnEvent(e);

        EventDispatcher dispatcher {e};
        dispatcher.Dispatch<KeyPressedEvent>(FENIX_BIND_EVENT_FN(EditorLayer::OnKeyPressed));
    }

    bool EditorLayer::OnKeyPressed(KeyPressedEvent& e)
    {
        // Shortcuts
        if (e.GetRepeatCount() > 0)
            return false;

        bool control = Input::IsKeyPressed(key::LeftControl) || Input::IsKeyPressed(key::RightControl);
        bool shift = Input::IsKeyPressed(key::LeftShift) || Input::IsKeyPressed(key::RightShift);
        switch (e.GetKeyCode())
        {
            case key::N: {
                if (control)
                    NewScene();
                break;
            }
            case key::O: {
                if (control)
                    OpenScene();
                break;
            }
            case key::S: {
                if (control && shift)
                    SaveSceneAs();
                break;
            }
        }

        return true;
    }

    void EditorLayer::NewScene()
    {
        m_ActiveScene = CreateRef<Scene>();
        m_ActiveScene->OnViewportResize(static_cast<uint32_t>(m_ViewportSize.x), static_cast<uint32_t>(m_ViewportSize.y));
        m_SceneHierarchyPanel.SetContext(m_ActiveScene);
    }

    void EditorLayer::OpenScene()
    {
        std::string file_path = FileDialog::OpenFile("Fenix Scene (*.fenix)\0*.fenix\0");
        if (!file_path.empty())
        {
            m_ActiveScene = CreateRef<Scene>();
            m_ActiveScene->OnViewportResize(static_cast<uint32_t>(m_ViewportSize.x), static_cast<uint32_t>(m_ViewportSize.y));
            m_SceneHierarchyPanel.SetContext(m_ActiveScene);

            SceneSerializer serializer {m_ActiveScene};
            serializer.Deserialize(file_path);
        }
    }

    void EditorLayer::SaveSceneAs()
    {
        std::string file_path = FileDialog::SaveFile("Fenix Scene (*.fenix)\0*.fenix\0");
        if (!file_path.empty())
        {
            SceneSerializer serializer {m_ActiveScene};
            serializer.Serialize(file_path);
        }
    }

} // namespace fenix
