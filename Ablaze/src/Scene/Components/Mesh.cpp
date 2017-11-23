#include "Mesh.h"

namespace Ablaze
{

	Mesh::Mesh() : Component(),
		m_Models()
	{
	
	}

	Mesh::Mesh(const Resource<Model>& model, const MaterialBase& material, const Maths::Mat4& transform) : Mesh()
	{
		AddModel(model, material, transform);
	}

	Mesh::Mesh(const Mesh& other)
		: m_Models(other.m_Models)
	{
		for (ModelSet& set : m_Models)
		{
			set.material = set.material->Clone();
		}
	}

	Mesh::~Mesh()
	{
		for (ModelSet& set : m_Models)
		{
			delete set.material;
		}
	}

	const Resource<Model>& Mesh::GetModel(int index) const
	{
		return m_Models[index].model;
	}

	Resource<Model>& Mesh::GetModel(int index)
	{
		return m_Models[index].model;
	}

	const MaterialBase& Mesh::Material(int index) const
	{
		return *m_Models[index].material;
	}

	MaterialBase& Mesh::Material(int index)
	{
		return *m_Models[index].material;
	}

	const Maths::Mat4& Mesh::GetTransform(int index) const
	{
		return m_Models[index].transform;
	}

	Maths::Mat4& Mesh::GetTransform(int index)
	{
		return m_Models[index].transform;
	}

	const ModelSet& Mesh::GetModelSet(int index) const
	{
		return m_Models[index];
	}

	const std::vector<ModelSet>& Mesh::GetModelSets() const
	{
		return m_Models;
	}

	int Mesh::ModelCount() const
	{
		return m_Models.size();
	}

	void Mesh::AddModel(const Resource<Model>& model, const MaterialBase& material, const Maths::Mat4& transform)
	{
		m_Models.push_back({ model, material.Clone(), transform });
	}

	void Mesh::SetMaterial(int index, const MaterialBase& material)
	{
		delete m_Models[index].material;
		m_Models[index].material = material.Clone();
	}

	String Mesh::ToString() const
	{
		return "Mesh";
	}

	void Mesh::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.BeginArray("Models");
		for (const ModelSet& model : m_Models)
		{
			writer.WriteObject(model.model);
		}
		writer.EndArray();
		writer.BeginArray("Materials");
		for (const ModelSet& model : m_Models)
		{
			writer.WriteObject(*model.material);
		}
		writer.EndArray();
		writer.BeginArray("Transforms");
		for (const ModelSet& model : m_Models)
		{
			writer.WriteObject(model.transform);
		}
		writer.EndArray();
		writer.EndObject();
	}

	Component* Mesh::Clone() const
	{
		Mesh* mesh = new Mesh;
		for (const ModelSet& modelSet : m_Models)
		{
			ModelSet model = { modelSet.model, modelSet.material->Clone(), modelSet.transform };
			mesh->m_Models.push_back(model);
		}
		return mesh;
	}

}