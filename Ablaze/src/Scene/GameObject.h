#pragma once
#include "Common.h"
#include "Resources\Meshes\Materials\Material.h"

namespace Ablaze
{

	class Layer;
	class ComponentSet;
	class Transform;
	class Mesh;

	// Base class for all Objects in the game
	class AB_API GameObject : public Object
	{
	protected:
		ComponentSet* m_Components;
		uint m_Id;
		Layer* m_Layer;

		GameObject* m_Parent;
		String m_Tag;

	protected:
		~GameObject();
		GameObject();

	public:
		GameObject* Parent() const;
		bool HasParent() const;
		Layer* GetLayer() const;

		void SetParent(GameObject* parent);
		void MakeChildOf(GameObject* parent);
		void MakeStandalone();
		void Destroy();

		void SetTag(const String& tag);

		const ComponentSet& Components() const;
		ComponentSet& Components();

		Transform& transform() const;
		Mesh& mesh() const;

		template<typename T>
		T& GetComponent() const
		{
			return *m_Components->GetComponent<T>();
		}

		template<typename T>
		bool HasComponent() const
		{
			return m_Components->HasComponent<T>();
		}

		template<typename T>
		void AddComponent(T* component)
		{
			m_Components->AddComponent(component);
		}
		
		template<typename T>
		void AddComponent()
		{
			AddComponent(new T);
		}

		String ToString() const override;
		void Serialize(JSONwriter& writer) const;
		void Serialize(JSONwriter& writer, const String& parentFile) const;

		friend class Layer;
		friend class Engine;

	public:
		static GameObject* Empty(const String& name);
		static GameObject* Instantiate(const String& name);
		static GameObject* Instantiate(const String& name, float x, float y, float z);
		static GameObject* Instantiate(const String& name, GameObject* prefab);
		static GameObject* Instantiate(const String& name, GameObject* prefab, float x, float y, float z);
		static GameObject* Instantiate(const String& name, GameObject* prefab, GameObject* parent);
		static GameObject* Instantiate(const String& name, GameObject* prefab, GameObject* parent, float x, float y, float z);

		static GameObject* Load(const String& gameobjectFile);
		static GameObject* Deserialize(JSONnode& node);

		static void Destroy(GameObject* gameObject);

		static std::vector<GameObject*> GetAll();
		static std::vector<GameObject*> GetAllWith(const std::vector<std::type_index>& componentTypes, bool onlyIfEnabled = true);

		template<typename T0>
		static std::vector<GameObject*> GetAllWith(bool onlyIfEnabled = true)
		{
			return GetAllWith({ typeid(T0) }, onlyIfEnabled);
		}

		template<typename T0, typename T1>
		static std::vector<GameObject*> GetAllWith(bool onlyIfEnabled = true)
		{
			return GetAllWith({ typeid(T0), typeid(T1) }, onlyIfEnabled);
		}

		template<typename T0, typename T1, typename T2>
		static std::vector<GameObject*> GetAllWith(bool onlyIfEnabled = true)
		{
			return GetAllWith({ typeid(T0), typeid(T1), typeid(T2) }, onlyIfEnabled);
		}

		template<typename T0, typename T1, typename T2, typename T3>
		static std::vector<GameObject*> GetAllWith(bool onlyIfEnabled = true)
		{
			return GetAllWith({ typeid(T0), typeid(T1), typeid(T2), typeid(T3) }, onlyIfEnabled);
		}

		template<typename T0, typename T1, typename T2, typename T3, typename T4>
		static std::vector<GameObject*> GetAllWith(bool onlyIfEnabled = true)
		{
			return GetAllWith({ typeid(T0), typeid(T1), typeid(T2), typeid(T3), typeid(T4) }, onlyIfEnabled);
		}

	private:
		static void LoadTransform(GameObject* object, JSONnode& transformNode);
		static void LoadMesh(GameObject* object, JSONnode& meshNode);

		template<typename T>
		static void LoadModel(Mesh* mesh, JSONnode& modelNode, const Material<T>& material)
		{
			if (!modelNode.HasChildren())
			{
				mesh->AddModel(ResourceManager::Library().LoadOBJModel(modelNode.Data()), material);
			}
			else if (modelNode["Type"].Data() == "Rectangle")
			{
				float w = stof(modelNode["Width"].Data());
				float h = stof(modelNode["Height"].Data());
				mesh->AddModel(ResourceManager::Library().CreateRectangle(w, h), material);
			}
			else if (modelNode["Type"].Data() == "Ellipse")
			{
				float w = stof(modelNode["Width"].Data());
				float h = stof(modelNode["Height"].Data());
				mesh->AddModel(ResourceManager::Library().CreateEllipse(w, h), material);
			}
			else if (modelNode["Type"].Data() == "Circle")
			{
				float r = stof(modelNode["Radius"].Data());
				mesh->AddModel(ResourceManager::Library().CreateCircle(r), material);
			}
			else if (modelNode["Type"].Data() == "Cuboid")
			{
				float w = stof(modelNode["Width"].Data());
				float h = stof(modelNode["Height"].Data());
				float d = stof(modelNode["Depth"].Data());
				mesh->AddModel(ResourceManager::Library().CreateCuboid(w, h, d), material);
			}
			else if (modelNode["Type"].Data() == "Plane")
			{
				float w = stof(modelNode["Width"].Data());
				float d = stof(modelNode["Depth"].Data());
				mesh->AddModel(ResourceManager::Library().CreatePlane(w, d), material);
			}
			else if (modelNode["Type"].Data() == "Sphere")
			{
				float r = stof(modelNode["Radius"].Data());
				mesh->AddModel(ResourceManager::Library().CreateSphere(r), material);
			}
		}

		template<typename T>
		static void LoadMaterial(Mesh* mesh, JSONnode& meshNode)
		{
			JSONnode& materialNode = meshNode["Material"];
			Color c = Color::White();
			if (materialNode.HasChild("Color"))
			{
				JSONnode& colorNode = materialNode["Color"];
				c.r = stoi(colorNode["r"].Data()) / 255.0f;
				c.g = stoi(colorNode["g"].Data()) / 255.0f;
				c.b = stoi(colorNode["b"].Data()) / 255.0f;
				if (colorNode.HasChild("a"))
				{
					c.a = stoi(colorNode["a"].Data()) / 255.0f;
				}
			}
			if (materialNode["Shader"].Data() == "DefaultColorShader")
			{
				Material<T> material = Material<T>(c, ResourceManager::Library().DefaultColorShader());
				JSONnode& model = meshNode["Model"];
				LoadModel(mesh, model, material);
			}
			else if (materialNode["Shader"].Data() == "LightingColorShader")
			{
				Material<T> material = Material<T>(c, ResourceManager::Library().LightingColorShader());
				JSONnode& model = meshNode["Model"];
				LoadModel(mesh, model, material);
			}
			else if (materialNode["Shader"].Data() == "DefaultTextureShader")
			{
				Material<T> material = Material<T>(c, ResourceManager::Library().DefaultTextureShader());
				if (materialNode.HasChild("Sampler") && materialNode.HasChild("Texture"))
				{
					material.Textures().AddTexture(materialNode["Sampler"].Data(), ResourceManager::Library().Load<T>(materialNode["Texture"].Data()));
				}
				JSONnode& model = meshNode["Model"];
				LoadModel(mesh, model, material);
			}
			else if (materialNode["Shader"].Data() == "LightingTextureShader")
			{
				Material<T> material = Material<T>(c, ResourceManager::Library().LightingTextureShader());
				if (materialNode.HasChild("Sampler") && materialNode.HasChild("Texture"))
				{
					material.Textures().AddTexture(materialNode["Sampler"].Data(), ResourceManager::Library().Load<T>(materialNode["Texture"].Data()));
				}
				JSONnode& model = meshNode["Model"];
				LoadModel(mesh, model, material);
			}
			else
			{
				Material<T> material = Material<T>(c, ResourceManager::Library().LoadShader(materialNode["Shader"].Data()));
				if (materialNode.HasChild("Sampler") && materialNode.HasChild("Texture"))
				{
					material.Textures().AddTexture(materialNode["Sampler"].Data(), ResourceManager::Library().Load<T>(materialNode["Texture"].Data()));
				}
				JSONnode& model = meshNode["Model"];
				LoadModel(mesh, model, material);
			}
		}

	};

}