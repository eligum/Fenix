#include "scene_hierarchy_panel.hh"

#include <fenix/scene/components.hh>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <imgui_internal.h>

namespace fenix {

    SceneHierarchyPanel::SceneHierarchyPanel(const Ref<Scene>& context)
    {
        SetContext(context);
    }

    void SceneHierarchyPanel::SetContext(const Ref<Scene>& context)
    {
        m_Context = context;
    }

    void SceneHierarchyPanel::OnImGuiRender()
    {
        ImGui::Begin("Scene Hierarchy");
        m_Context->m_Registry.each([=](auto entity_id) {
            Entity entity{ entity_id, m_Context.get() };
            DrawEntityNode(entity);
        });
        if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
        {
            m_SelectionContext = Entity{};
        }
        ImGui::End();

        ImGui::Begin("Properties");
        if (m_SelectionContext)
        {
            DrawComponents(m_SelectionContext);
        }
        ImGui::End();
    }

    void SceneHierarchyPanel::DrawEntityNode(Entity entity)
    {
        auto& tag = entity.GetComponent<TagComponent>().Tag;

        ImGuiTreeNodeFlags flags =
            ((m_SelectionContext == entity) ? ImGuiTreeNodeFlags_Selected : 0)
            | ImGuiTreeNodeFlags_OpenOnArrow
            | ImGuiTreeNodeFlags_OpenOnDoubleClick;

        bool opened = ImGui::TreeNodeEx(reinterpret_cast<void*>((uint64_t)(uint32_t)entity), flags, "%s", tag.c_str());
        if (ImGui::IsItemClicked())
        {
            m_SelectionContext = entity;
        }

        if (opened)
        {
            ImGui::TreePop();
        }
    }

    static void DrawVec3Control(const std::string& label, glm::vec3& values, float reset_value = 0.0f, float column_width = 100.0f)
    {
        ImGui::PushID(label.c_str());

        // *NOTE: Tried using the newer Table API but failed at it :(
        // TODO: Refactor this at some point.
        // ImGui::BeginTable("##Table", 2);
        ImGui::Columns(2);
        ImGui::SetColumnWidth(0, column_width);

        // ImGui::TableSetupColumn("##nolabel", 0, column_width);
        // ImGui::TableNextColumn();
        ImGui::Text("%s", label.c_str());
        ImGui::NextColumn();

        ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

        float line_height = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        ImVec2 button_size = { line_height + 3.0f, line_height };

        // ImGui::TableNextColumn();

        // X button
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
        if (ImGui::Button("X", button_size))
            values.x = reset_value;
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        // Y button
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::SameLine();
        if (ImGui::Button("Y", button_size))
            values.y = reset_value;
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        // Z button
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        ImGui::SameLine();
        if (ImGui::Button("Z", button_size))
            values.z = reset_value;
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();

        // ImGui::EndTable();
        ImGui::Columns(1);
        ImGui::PopID();
    }

    void SceneHierarchyPanel::DrawComponents(Entity entity)
    {
        if (entity.HasComponent<TagComponent>())
        {
            auto& tag = entity.GetComponent<TagComponent>().Tag;

            std::array<char, 256> buff;
            std::fill(buff.begin(), buff.end(), '\0');
            std::copy(tag.cbegin(), tag.cend(), buff.begin());

            if (ImGui::InputText("Tag", buff.data(), buff.size()))
            {
                tag = std::string(buff.data());
            }
        }

        if (entity.HasComponent<TransformComponent>())
        {
            if (ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(TransformComponent).hash_code()), ImGuiTreeNodeFlags_DefaultOpen, "Transform"))
            {
                auto& tc = entity.GetComponent<TransformComponent>();
                DrawVec3Control("Translation", tc.Translation);
                glm::vec3 rotation = glm::degrees(tc.Rotation);
                DrawVec3Control("Rotation", rotation);
                tc.Rotation = glm::radians(rotation);
                DrawVec3Control("Scale", tc.Scale, 1.0f);

                ImGui::TreePop();
            }
        }

        if (entity.HasComponent<CameraComponent>())
        {
            if (ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(CameraComponent).hash_code()), ImGuiTreeNodeFlags_DefaultOpen, "Camera"))
            {
                auto& camera_comp = entity.GetComponent<CameraComponent>();
                auto& camera = camera_comp.Camera;

                ImGui::Checkbox("Primary", &camera_comp.Primary);

                std::array<const char*, 2> items = { "Perspective", "Orthographic" };
                const char* current_item = items[static_cast<std::size_t>(camera.GetProjectionType())];
                if (ImGui::BeginCombo("Projection", current_item))
                {
                    for (std::size_t i = 0; i < items.size(); i++)
                    {
                        bool is_selected = (current_item == items[i]);
                        if (ImGui::Selectable(items[i], is_selected))
                        {
                            current_item = items[i];
                            camera.SetProjectionType(static_cast<SceneCamera::ProjectionType>(i));
                        }

                        // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }

                switch (camera.GetProjectionType())
                {
                    case SceneCamera::ProjectionType::Perspective:
                    {
                        float fov = glm::degrees(camera.GetPerspectiveVerticalFOV());
                        if (ImGui::DragFloat("FOV", &fov))
                            camera.SetPerspectiveVerticalFOV(glm::radians(fov));

                        float z_near = camera.GetPerspectiveNearClip();
                        if (ImGui::DragFloat("Z-near", &z_near))
                            camera.SetPerspectiveNearClip(z_near);

                        float z_far = camera.GetPerspectiveFarClip();
                        if (ImGui::DragFloat("Z-far", &z_far))
                            camera.SetPerspectiveFarClip(z_far);
                    } break;
                    case SceneCamera::ProjectionType::Orthographic:
                    {
                        float ortho_size = camera.GetOrthographicSize();
                        if (ImGui::DragFloat("Size", &ortho_size))
                            camera.SetOrthographicSize(ortho_size);

                        float z_near = camera.GetOrthographicNearClip();
                        if (ImGui::DragFloat("Z-near", &z_near))
                            camera.SetOrthographicNearClip(z_near);

                        float z_far = camera.GetOrthographicFarClip();
                        if (ImGui::DragFloat("Z-far", &z_far))
                            camera.SetOrthographicFarClip(z_far);

                        ImGui::Checkbox("Fixed Aspect Ratio", &camera_comp.FixedAspectRatio);
                    } break;
                }

                ImGui::TreePop();
            }
        }

        if (entity.HasComponent<SpriteRendererComponent>())
        {
            if (ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(SpriteRendererComponent).hash_code()), ImGuiTreeNodeFlags_DefaultOpen, "Sprite Renderer"))
            {
                auto& src = entity.GetComponent<SpriteRendererComponent>();
                ImGui::ColorEdit4("Color", glm::value_ptr(src.Color));

                ImGui::TreePop();
            }
        }
    }

} // namespace fenix
