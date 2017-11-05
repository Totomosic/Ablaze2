#pragma once
#include "Common.h"
#include "Camera.h"
#include "Entity.h"
#include "Lighting\__Lighting__.h"

namespace Ablaze
{

	class AB_API Layer : public Object
	{
	private:
		const String& m_Name;
		std::vector<Entity*> m_Entities;
		std::vector<Camera*> m_Cameras;
		std::vector<Light*> m_Lights;
		std::unordered_map<String, std::vector<Entity*>> m_NamedEntities;
		Camera* m_Camera;

	private:
		Layer(const String& name, Camera* camera);
		Layer(const String& name);
		Layer(const Layer& other) = delete;
		~Layer();

	public:
		const String& GetName() const;
		const std::vector<Entity*>& GetEntities() const;
		std::vector<Entity*>& GetEntities();
		const std::vector<Camera*>& GetCameras() const;
		std::vector<Camera*>& GetCameras();
		const std::vector<Light*>& GetLights() const;	
		std::vector<Light*>& GetLights();
		Camera* GetActiveCamera() const;
		bool HasCamera() const;
		int EntityCount() const;
		int CameraCount() const;
		int LightCount() const;

		void SetActiveCamera(Camera* camera);
		void AddEntity(Entity* entity);
		void AddEntity(Entity* entity, const String& tag);
		void RemoveEntity(Entity* entity);
		void RemoveEntity(int index);
		void AddCamera(Camera* camera);
		void AddCamera(Camera* camera, const String& tag);
		void RemoveCamera(Camera* camera);
		void RemoveCamera(int index);
		void AddLight(Light* light);
		void AddLight(Light* light, const String& tag);
		void RemoveLight(Light* light);
		void RemoveLight(int index);
		void Clear();

		const Entity& GetEntity(int index) const;
		Entity& GetEntity(int index);
		const Camera& GetCamera(int index) const;
		Camera& GetCamera(int index);
		const Light& GetLight(int index) const;
		Light& GetLight(int index);
		const Entity& GetNamedEntity(const String& tag, int index = 0) const;
		Entity& GetNamedEntity(const String& tag, int index = 0);

		template<typename T>
		const T& GetNamedEntity(const String& tag, int index = 0) const
		{
			return *((T*)&GetNamedEntity(tag, index));
		}

		template<typename T>
		T& GetNamedEntity(const String& tag, int index = 0)
		{
			return *((T*)&GetNamedEntity(tag, index));
		}

		Entity& CreateEntity(const Transform& transform, const Mesh& mesh);
		Entity& CreateEntity(const Transform& transform);
		Entity& CreateEntity(const Mesh& mesh);
		Entity& CreateEntity();
		Entity& CreateEntity(const Maths::Vec3& position, const Mesh& mesh);
		Entity& CreateEntity(const Maths::Vec3& position);
		Entity& CreateEntity(float x, float y, float z, const Mesh& mesh);
		Entity& CreateEntity(float x, float y, float z);

		Actor& CreateActor(const Transform& transform, const Mesh& mesh);
		Actor& CreateActor(const Transform& transform);
		Actor& CreateActor(const Mesh& mesh);
		Actor& CreateActor();
		Actor& CreateActor(const Maths::Vec3& position, const Mesh& mesh);
		Actor& CreateActor(const Maths::Vec3& position);
		Actor& CreateActor(float x, float y, float z, const Mesh& mesh);
		Actor& CreateActor(float x, float y, float z);

		Camera& CreateCamera(const Transform& transform, const Mesh& mesh, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera& CreateCamera(const Transform& transform, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera& CreateCamera(const Mesh& mesh, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera& CreateCamera(Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera& CreateCamera(const Maths::Vec3& position, const Mesh& mesh, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera& CreateCamera(const Maths::Vec3& position, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera& CreateCamera(float x, float y, float z, const Mesh& mesh, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera& CreateCamera(float x, float y, float z, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);

		Light& CreateLight(const Transform& transform, LightType type = LightType::Point, const Color& color = Color::White(), float intensity = 1.0f, const Maths::Vec3& attenuation = Maths::Vec3(1.0f, 0.0f, 0.0f));
		Light& CreateLight(LightType type = LightType::Point, const Color& color = Color::White(), float intensity = 1.0f, const Maths::Vec3& attenuation = Maths::Vec3(1.0f, 0.0f, 0.0f));
		Light& CreateLight(const Maths::Vec3& position, LightType type = LightType::Point, const Color& color = Color::White(), float intensity = 1.0f, const Maths::Vec3& attenuation = Maths::Vec3(1.0f, 0.0f, 0.0f));
		Light& CreateLight(float x, float y, float z, LightType type = LightType::Point, const Color& color = Color::White(), float intensity = 1.0f, const Maths::Vec3& attenuation = Maths::Vec3(1.0f, 0.0f, 0.0f));
		Light& CreateSun(const Transform& transform);
		Light& CreateSun(const Maths::Vec3& position);
		Light& CreateSun(float x, float y, float z);

		String ToString() const override;

		friend class Scene;
		friend class Entity;

	private:
		void TagEntity(Entity* entity, const String& tag);
		bool TagExists(const String& tag);

	};

}