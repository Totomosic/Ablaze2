#include "Layer.h"

namespace Ablaze
{

	Layer::Layer(const String& name, Camera* camera) : Object(),
		m_Name(name)
	{
		AddCamera(camera);
	}

	Layer::Layer(const String& name) : Object(),
		m_Name(name), m_Camera(nullptr)
	{
	
	}

	Layer::~Layer()
	{
		for (Entity* entity : m_Entities)
		{
			delete entity;
		}
		for (Camera* camera : m_Cameras)
		{
			delete camera;
		}
		for (Light* light : m_Lights)
		{
			delete light;
		}
	}

	const String& Layer::GetName() const
	{
		return m_Name;
	}

	const std::vector<Entity*>& Layer::GetEntities() const
	{
		return m_Entities;
	}

	std::vector<Entity*>& Layer::GetEntities()
	{
		return m_Entities;
	}

	const std::vector<Camera*>& Layer::GetCameras() const
	{
		return m_Cameras;
	}

	std::vector<Camera*>& Layer::GetCameras()
	{
		return m_Cameras;
	}

	const std::vector<Light*>& Layer::GetLights() const
	{
		return m_Lights;
	}	

	std::vector<Light*>& Layer::GetLights()
	{
		return m_Lights;
	}

	Camera* Layer::GetActiveCamera() const
	{
		return m_Camera;
	}

	bool Layer::HasCamera() const
	{
		return m_Camera != nullptr;
	}

	int Layer::EntityCount() const
	{
		return m_Entities.size();
	}

	int Layer::CameraCount() const
	{
		return m_Cameras.size();
	}

	int Layer::LightCount() const
	{
		return m_Lights.size();
	}

	void Layer::SetActiveCamera(Camera* camera)
	{
		m_Camera = camera;
	}

	void Layer::AddEntity(Entity* entity)
	{
		int index = m_Entities.size();
		m_Entities.push_back(entity);
		entity->SetLayer(this);
	}

	void Layer::AddEntity(Entity* entity, const String& tag)
	{
		int index = m_Entities.size();
		AddEntity(entity);
		TagEntity(entity, tag);
	}

	void Layer::RemoveEntity(Entity* entity)
	{
		
	}

	void Layer::RemoveEntity(int index)
	{
		m_Entities.erase(m_Entities.begin() + index);
	}

	void Layer::AddCamera(Camera* camera)
	{
		int index = m_Cameras.size();
		m_Cameras.push_back(camera);
		camera->SetLayer(this);
		if (!HasCamera())
		{
			SetActiveCamera(m_Cameras[index]);
		}
		camera = m_Cameras[index];
	}

	void Layer::AddCamera(Camera* camera, const String& tag)
	{
		AddCamera(camera);
		TagEntity(camera, tag);
	}

	void Layer::RemoveCamera(Camera* camera)
	{
		
	}

	void Layer::RemoveCamera(int index)
	{
		m_Cameras.erase(m_Cameras.begin() + index);
	}

	void Layer::AddLight(Light* light)
	{
		int index = m_Lights.size();
		m_Lights.push_back(light);
		light->SetLayer(this);
		light = m_Lights[index];
	}

	void Layer::AddLight(Light* light, const String& tag)
	{
		AddLight(light);
		TagEntity(light, tag);
	}

	void Layer::RemoveLight(Light* light)
	{
		
	}

	void Layer::RemoveLight(int index)
	{
		m_Lights.erase(m_Lights.begin() + index);
	}

	void Layer::Clear()
	{
		m_Entities.clear();
	}

	const Entity& Layer::GetEntity(int index) const
	{
		return *m_Entities[index];
	}

	Entity& Layer::GetEntity(int index)
	{
		return *m_Entities[index];
	}

	const Camera& Layer::GetCamera(int index) const
	{
		return *m_Cameras[index];
	}

	Camera& Layer::GetCamera(int index)
	{
		return *m_Cameras[index];
	}

	const Light& Layer::GetLight(int index) const
	{
		return *m_Lights[index];
	}

	Light& Layer::GetLight(int index)
	{
		return *m_Lights[index];
	}

	const Entity& Layer::GetNamedEntity(const String& tag, int index) const
	{
		return *m_NamedEntities.at(tag)[index];
	}

	Entity& Layer::GetNamedEntity(const String& tag, int index)
	{
		if (!TagExists(tag))
		{
			AB_ERROR("Entity with tag: " + tag + " does not exist");
			return *(Entity*)nullptr;
		}
		return *m_NamedEntities.at(tag)[index];
	}

	Entity& Layer::CreateEntity(const Transform& transform, const Mesh& mesh)
	{
		Entity* entity = new Entity(transform, mesh);
		AddEntity(entity);
		return *entity;
	}

	Entity& Layer::CreateEntity(const Transform& transform)
	{
		Entity* entity = new Entity(transform);
		AddEntity(entity);
		return *entity;
	}

	Entity& Layer::CreateEntity(const Mesh& mesh)
	{
		return CreateEntity(Transform(), mesh);
	}

	Entity& Layer::CreateEntity()
	{ 
		return CreateEntity(Transform());
	}

	Entity& Layer::CreateEntity(const Maths::Vec3& position, const Mesh& mesh)
	{ 
		return CreateEntity(Transform(position), mesh);
	}

	Entity& Layer::CreateEntity(const Maths::Vec3& position)
	{
		return CreateEntity(Transform(position));
	}

	Entity& Layer::CreateEntity(float x, float y, float z, const Mesh& mesh)
	{ 
		return CreateEntity(Maths::Vec3(x, y, z), mesh);
	}

	Entity& Layer::CreateEntity(float x, float y, float z)
	{ 
		return CreateEntity(Maths::Vec3(x, y, z));
	}


	Actor& Layer::CreateActor(const Transform& transform, const Mesh& mesh)
	{ 
		Actor* actor = new Actor(transform, mesh);
		AddEntity(actor);
		return *actor;
	}

	Actor& Layer::CreateActor(const Transform& transform)
	{
		Actor* actor = new Actor(transform);
		AddEntity(actor);
		return *actor;
	}

	Actor& Layer::CreateActor(const Mesh& mesh)
	{ 
		return CreateActor(Transform(), mesh);
	}

	Actor& Layer::CreateActor()
	{ 
		return CreateActor(Transform());
	}

	Actor& Layer::CreateActor(const Maths::Vec3& position, const Mesh& mesh)
	{ 
		return CreateActor(Transform(position), mesh);
	}

	Actor& Layer::CreateActor(const Maths::Vec3& position)
	{
		return CreateActor(Transform(position));
	}

	Actor& Layer::CreateActor(float x, float y, float z, const Mesh& mesh)
	{
		return CreateActor(Maths::Vec3(x, y, z), mesh);
	}

	Actor& Layer::CreateActor(float x, float y, float z)
	{ 
		return CreateActor(Maths::Vec3(x, y, z));
	}


	Camera& Layer::CreateCamera(const Transform& transform, const Mesh& mesh, Projection projection, float fov, float nearPlane, float farPlane)
	{
		Camera* camera = new Camera(transform, mesh, projection, fov, nearPlane, farPlane);
		AddCamera(camera);
		return *camera;
	}

	Camera& Layer::CreateCamera(const Transform& transform, Projection projection, float fov, float nearPlane, float farPlane)
	{
		Camera* camera = new Camera(transform, projection, fov, nearPlane, farPlane);
		AddCamera(camera);
		return *camera;
	}

	Camera& Layer::CreateCamera(const Mesh& mesh, Projection projection, float fov, float nearPlane, float farPlane)
	{
		return CreateCamera(Transform(), mesh, projection, fov, nearPlane, farPlane);
	}

	Camera& Layer::CreateCamera(Projection projection, float fov, float nearPlane, float farPlane)
	{ 
		return CreateCamera(Transform(), projection, fov, nearPlane, farPlane);
	}

	Camera& Layer::CreateCamera(const Maths::Vec3& position, const Mesh& mesh, Projection projection, float fov, float nearPlane, float farPlane)
	{ 
		return CreateCamera(Transform(position), mesh, projection, fov, nearPlane, farPlane);
	}

	Camera& Layer::CreateCamera(const Maths::Vec3& position, Projection projection, float fov, float nearPlane, float farPlane)
	{ 
		return CreateCamera(Transform(position), projection, fov, nearPlane, farPlane);
	}

	Camera& Layer::CreateCamera(float x, float y, float z, const Mesh& mesh, Projection projection, float fov, float nearPlane , float farPlane)
	{ 
		return CreateCamera(Maths::Vec3(x, y, z), mesh, projection, fov, nearPlane, farPlane);
	}

	Camera& Layer::CreateCamera(float x, float y, float z, Projection projection, float fov, float nearPlane, float farPlane)
	{ 
		return CreateCamera(Maths::Vec3(x, y, z), projection, fov, nearPlane, farPlane);
	}

	Light& Layer::CreateLight(const Transform& transform, LightType type, const Color& color, float intensity, const Maths::Vec3& attenuation)
	{ 
		Light* light = new Light(transform, type, color, intensity, attenuation);
		AddLight(light);
		return *light;
	}

	Light& Layer::CreateLight(LightType type , const Color& color, float intensity, const Maths::Vec3& attenuation)
	{
		return CreateLight(Transform(), type, color, intensity, attenuation);
	}

	Light& Layer::CreateLight(const Maths::Vec3& position, LightType type, const Color& color, float intensity, const Maths::Vec3& attenuation)
	{ 
		return CreateLight(Transform(position), type, color, intensity, attenuation);
	}

	Light& Layer::CreateLight(float x, float y, float z, LightType type, const Color& color, float intensity, const Maths::Vec3& attenuation)
	{ 
		return CreateLight(Maths::Vec3(x, y, z), type, color, intensity, attenuation);
	}

	Light& Layer::CreateSun(const Transform& transform)
	{ 
		Light* light = Light::Sun(transform.Position());
		AddLight(light);
		return *light;
	}

	Light& Layer::CreateSun(const Maths::Vec3& position)
	{ 
		Light* light = Light::Sun(position);
		AddLight(light);
		return *light;
	}

	Light& Layer::CreateSun(float x, float y, float z)
	{ 
		return CreateSun(Maths::Vec3(x, y, z));
	}

	String Layer::ToString() const
	{
		return "Layer";
	}

	void Layer::TagEntity(Entity* entity, const String& tag)
	{
		if (TagExists(tag))
		{
			m_NamedEntities[tag].push_back(entity);
		}
		else
		{
			m_NamedEntities[tag] = std::vector<Entity*>();
			m_NamedEntities[tag].push_back(entity);
		}
	}

	bool Layer::TagExists(const String& tag)
	{
		return m_NamedEntities.find(tag) != m_NamedEntities.end();
	}

}