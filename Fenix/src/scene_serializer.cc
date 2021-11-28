#include "fenix/scene/scene_serializer.hh"
#include "fenix/scene/entity.hh"
#include "fenix/scene/components.hh"

#include <yaml-cpp/yaml.h>
#include <fstream>

namespace YAML {

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

}

namespace fenix {

    YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
        return out;
    }

    YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
    {
        out << YAML::Flow;
        out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
        return out;
    }

    SceneSerializer::SceneSerializer(const Ref<Scene>& scene)
        : m_Scene(scene) {}

    static void SerializeEntity(YAML::Emitter& out, Entity entity)
    {
        out << YAML::BeginMap;
        out << YAML::Key << "Entity" << YAML::Key << "10923874"; // TODO: Entity ID goes here.

        if (entity.HasComponent<TagComponent>())
        {
            out << YAML::Key << "TagComponent";
            out << YAML::BeginMap;

            const auto& tag = entity.GetComponent<TagComponent>().Tag;
            out << YAML::Key << "Tag" << YAML::Value << tag;

            out << YAML::EndMap;
        }

        if (entity.HasComponent<TransformComponent>())
        {
            out << YAML::Key << "TransformComponent";
            out << YAML::BeginMap; // TransformComponent

            const auto& tc = entity.GetComponent<TransformComponent>();
            out << YAML::Key << "Translation" << YAML::Value << tc.Translation;
            out << YAML::Key << "Rotation" << YAML::Value << tc.Rotation;
            out << YAML::Key << "Scale" << YAML::Value << tc.Scale;

            out << YAML::EndMap; // TransformComponent
        }

        if (entity.HasComponent<CameraComponent>())
        {
            out << YAML::Key << "CameraComponent";
            out << YAML::BeginMap; // CameraComponent

            const auto& camera_component = entity.GetComponent<CameraComponent>();
            const auto& camera = camera_component.Camera;

            out << YAML::Key << "Camera" << YAML::Value;
            out << YAML::BeginMap; // Camera
            out << YAML::Key << "ProjectionType"   << YAML::Value << static_cast<int>(camera.GetProjectionType());
            out << YAML::Key << "PerspectiveFOV"   << YAML::Value << camera.GetPerspectiveVerticalFOV();
            out << YAML::Key << "PerspectiveNear"  << YAML::Value << camera.GetPerspectiveNearClip();
            out << YAML::Key << "PerspectiveFar"   << YAML::Value << camera.GetPerspectiveFarClip();
            out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthographicSize();
            out << YAML::Key << "OrthographicNear" << YAML::Value << camera.GetOrthographicNearClip();
            out << YAML::Key << "OrthographicFar"  << YAML::Value << camera.GetOrthographicFarClip();
            out << YAML::EndMap; // Camera

            out << YAML::Key << "Primary" << YAML::Value << camera_component.Primary;
            out << YAML::Key << "FixedAspectRatio" << YAML::Value << camera_component.FixedAspectRatio;

            out << YAML::EndMap; // CameraComponent
        }

        if (entity.HasComponent<SpriteRendererComponent>())
        {
            out << YAML::Key << "SpriteRendererComponent";
            out << YAML::BeginMap; // SpriteRendererComponent

            const auto& spriteRendererComponent = entity.GetComponent<SpriteRendererComponent>();
            out << YAML::Key << "Color" << YAML::Value << spriteRendererComponent.Color;

            out << YAML::EndMap; // SpriteRendererComponent
        }

        out << YAML::EndMap;
    }

    void SceneSerializer::Serialize(const std::string& file_path)
    {
        YAML::Emitter out;
        out << YAML::BeginMap;
        out << YAML::Key << "Scene" << YAML::Value << "Untitled";
        out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
        m_Scene->m_Registry.each([&](auto& entity_id) {
            Entity entity {entity_id, m_Scene.get()};
            SerializeEntity(out, entity);
        });
        out << YAML::EndSeq;
        out << YAML::EndMap;

        std::ofstream fout {file_path, std::ios::out | std::ios::trunc};
        fout << out.c_str();
    }

    void SceneSerializer::SerializeRuntime(const std::string& file_path)
    {
        FENIX_CORE_ASSERT(false, "Not implemented");
    }

    bool SceneSerializer::Deserialize(const std::string& file_path)
    {
        std::ifstream in {file_path, std::ios::in};
        std::stringstream ss;
        ss << in.rdbuf();

        YAML::Node data = YAML::Load(ss.str());
        if (!data["Scene"])
            return false;

        std::string scene_name = data["Scene"].as<std::string>();
        FENIX_CORE_TRACE("Deserializing scene {0}", scene_name);

        auto entities = data["Entities"];
        if (entities)
        {
            for (auto entity : entities)
            {
                uint64_t uuid = entity["Entity"].as<uint64_t>();

                // Tag component
                std::string name;
                auto tag_component = entity["TagComponent"];
                if (tag_component)
                    name = tag_component["Tag"].as<std::string>();

                FENIX_CORE_TRACE("Deserializing entity with ID = {0}, name = {1}", uuid, name);

                Entity deserialized_entity = m_Scene->CreateEntity(name);

                // Transform component
                auto transform_component = entity["TransformComponent"];
                if (transform_component)
                {
                    // Entities always have transforms
                    auto& tc = deserialized_entity.GetComponent<TransformComponent>();
                    tc.Translation = transform_component["Translation"].as<glm::vec3>();
                    tc.Rotation = transform_component["Rotation"].as<glm::vec3>();
                    tc.Scale = transform_component["Scale"].as<glm::vec3>();
                }

                // Camera component
                auto camera_component = entity["CameraComponent"];
                if (camera_component)
                {
                    auto& cc = deserialized_entity.AddComponent<CameraComponent>();

                    auto camera_props = camera_component["Camera"];
                    cc.Camera.SetProjectionType(static_cast<SceneCamera::ProjectionType>(camera_props["ProjectionType"].as<int>()));

                    cc.Camera.SetPerspectiveVerticalFOV(camera_props["PerspectiveFOV"].as<float>());
                    cc.Camera.SetPerspectiveNearClip(camera_props["PerspectiveNear"].as<float>());
                    cc.Camera.SetPerspectiveFarClip(camera_props["PerspectiveFar"].as<float>());

                    cc.Camera.SetOrthographicSize(camera_props["OrthographicSize"].as<float>());
                    cc.Camera.SetOrthographicNearClip(camera_props["OrthographicNear"].as<float>());
                    cc.Camera.SetOrthographicFarClip(camera_props["OrthographicFar"].as<float>());

                    cc.Primary = camera_component["Primary"].as<bool>();
                    cc.FixedAspectRatio = camera_component["FixedAspectRatio"].as<bool>();
                }

                // Sprite Renderer component
                auto sprite_renderer_component = entity["SpriteRendererComponent"];
                if (sprite_renderer_component)
                {
                    auto& sc = deserialized_entity.AddComponent<SpriteRendererComponent>();
                    sc.Color = sprite_renderer_component["Color"].as<glm::vec4>();
                }
            }
        }

        return true;
    }

    bool SceneSerializer::DeserializeRuntime(const std::string& file_path)
    {
        FENIX_CORE_ASSERT(false, "Not implemented");
        return false;
    }

} // namespace fenix
