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
            Entity entity {entity_id, m_Context.get()};
            DrawEntityNode(entity);
        });

        if (ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::IsWindowHovered())
            m_SelectionContext = Entity{};

        // Right-click on blank space
        if (ImGui::BeginPopupContextWindow(0, ImGuiMouseButton_Right, false))
        {
            if (ImGui::MenuItem("Create Empty Entity"))
                m_Context->CreateEntity("empty entity");

            ImGui::EndPopup();
        }

        ImGui::End();

        // TODO: Export to its own class
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
            | ImGuiTreeNodeFlags_OpenOnDoubleClick
            | ImGuiTreeNodeFlags_SpanAvailWidth;

        bool opened = ImGui::TreeNodeEx(reinterpret_cast<void*>((uint64_t)(uint32_t)entity), flags, "%s", tag.c_str());
        if (ImGui::IsItemClicked())
        {
            m_SelectionContext = entity;
        }

        bool entity_deleted = false;
        if (ImGui::BeginPopupContextItem())
        {
            if (ImGui::MenuItem("Delete Entity"))
                entity_deleted = true;

            ImGui::EndPopup();
        }

        if (opened)
        {
            ImGui::TreePop();
        }

        if (entity_deleted)
        {
            m_Context->DestroyEntity(entity);
            if (m_SelectionContext == entity)
                m_SelectionContext = {};
        }
    }

    static void DrawVec3Control(const std::string& label, glm::vec3& values, float reset_value = 0.0f, float column_width = 100.0f)
    {
        ImGuiIO& io = ImGui::GetIO();
        auto bold_font = io.Fonts->Fonts[0];

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
        ImGui::PushFont(bold_font);
        if (ImGui::Button("X", button_size))
            values.x = reset_value;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        // Y button
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
        ImGui::SameLine();
        ImGui::PushFont(bold_font);
        if (ImGui::Button("Y", button_size))
            values.y = reset_value;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        // Z button
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.2f, 0.35f, 0.9f, 1.0f });
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.1f, 0.25f, 0.8f, 1.0f });
        ImGui::SameLine();
        ImGui::PushFont(bold_font);
        if (ImGui::Button("Z", button_size))
            values.z = reset_value;
        ImGui::PopFont();
        ImGui::PopStyleColor(3);

        ImGui::SameLine();
        ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
        ImGui::PopItemWidth();

        ImGui::PopStyleVar();

        // ImGui::EndTable();
        ImGui::Columns(1);
        ImGui::PopID();
    }

    template <typename T, typename UIFunction>
    static void DrawComponent(const std::string& name, Entity entity, UIFunction ui_function)
    {
        constexpr ImGuiTreeNodeFlags treenode_flags = ImGuiTreeNodeFlags_DefaultOpen
                                                    | ImGuiTreeNodeFlags_Framed
                                                    | ImGuiTreeNodeFlags_SpanAvailWidth
                                                    | ImGuiTreeNodeFlags_FramePadding
                                                    | ImGuiTreeNodeFlags_AllowItemOverlap;
        if (entity.HasComponent<T>())
        {
            auto& component = entity.GetComponent<T>();

            ImVec2 content_region_available = ImGui::GetContentRegionAvail();
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2{ 4, 4 });
            float line_height = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
            ImGui::Separator();
            bool open = ImGui::TreeNodeEx(reinterpret_cast<void*>(typeid(T).hash_code()), treenode_flags, "%s", name.c_str());
            ImGui::PopStyleVar();

            ImGui::SameLine(content_region_available.x - 0.5f * line_height);
            if (ImGui::Button("+", ImVec2{ line_height, line_height }))
            {
                ImGui::OpenPopup("ComponentSettings");
            }

            bool component_removed = false;
            if (ImGui::BeginPopup("ComponentSettings"))
            {
                if (ImGui::MenuItem("Remove component"))
                    component_removed = true;

                ImGui::EndPopup();
            }

            if (open)
            {
                ui_function(component);
                ImGui::TreePop();
            }

            if (component_removed)
                entity.RemoveComponent<T>();
        }
    }

    void SceneHierarchyPanel::DrawComponents(Entity entity)
    {
        if (entity.HasComponent<TagComponent>())
        {
            auto& tag = entity.GetComponent<TagComponent>().Tag;

            std::array<char, 256> buff;
            std::fill(buff.begin(), buff.end(), '\0');
            std::copy(tag.cbegin(), tag.cend(), buff.begin());

            if (ImGui::InputText("##Tag", buff.data(), buff.size()))
            {
                tag = std::string(buff.data());
            }
        }

        // Add component button
        ImGui::SameLine();
        ImGui::PushItemWidth(-1);

        if (ImGui::Button("Add Component"))
            ImGui::OpenPopup("AddComponent");

        if (ImGui::BeginPopup("AddComponent"))
        {
            if (ImGui::MenuItem("Camera"))
            {
                m_SelectionContext.AddComponent<CameraComponent>();
                ImGui::CloseCurrentPopup();
            }
            else if (ImGui::MenuItem("Color Picker"))
            {
                m_SelectionContext.AddComponent<SpriteRendererComponent>();
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        ImGui::PopItemWidth();

        DrawComponent<TransformComponent>("Transform", entity, [](auto& component) {
            DrawVec3Control("Translation", component.Translation);
            glm::vec3 rotation = glm::degrees(component.Rotation);
            DrawVec3Control("Rotation", rotation);
            component.Rotation = glm::radians(rotation);
            DrawVec3Control("Scale", component.Scale, 1.0f);
        });

        DrawComponent<CameraComponent>("Camera", entity, [](auto& component) {
            auto& camera = component.Camera;

            ImGui::Checkbox("Primary", &component.Primary);

            std::array<const char*, 2> items = { "Perspective", "Orthographic" };
            const char* current_item = items[static_cast<std::size_t>(camera.GetProjectionType())];

            if (ImGui::BeginCombo("Projection", current_item))
            {
                for (std::size_t i = 0; i < items.size(); ++i)
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

                    ImGui::Checkbox("Fixed Aspect Ratio", &component.FixedAspectRatio);
                } break;
            }
        });

        DrawComponent<SpriteRendererComponent>("Sprite Renderer", entity, [](auto& component) {
            ImGui::ColorEdit4("Color", glm::value_ptr(component.Color));
        });
    }

} // namespace fenix
