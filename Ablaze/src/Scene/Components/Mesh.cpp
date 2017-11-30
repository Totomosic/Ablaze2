#include "Mesh.h"

namespace Ablaze
{

	Mesh::Mesh() : Component(),
		m_Models()
	{
		
	}

	Mesh::Mesh(const std::shared_ptr<Model>& model, const std::shared_ptr<MaterialBase>& material, const Maths::Mat4& transform) : Mesh()
	{
		AddModel(model, material, transform);
	}

	Mesh::~Mesh()
	{
		
	}

	const std::shared_ptr<Model>& Mesh::GetModel(int index) const
	{
		return m_Models[index].model;
	}

	std::shared_ptr<Model>& Mesh::GetModel(int index)
	{
		return m_Models[index].model;
	}

	const std::shared_ptr<MaterialBase>& Mesh::Material(int index) const
	{
		return m_Models[index].material;
	}

	std::shared_ptr<MaterialBase>& Mesh::Material(int index)
	{
		return m_Models[index].material;
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

	ModelSet& Mesh::GetModelSet(int index)
	{
		return m_Models[index];
	}

	int Mesh::ModelCount() const
	{
		return m_Models.size();
	}

	void Mesh::AddModel(const std::shared_ptr<Model>& model, const std::shared_ptr<MaterialBase>& material, const Maths::Mat4& transform)
	{
		m_Models.push_back({ model, material, transform });
	}

	void Mesh::SetMaterial(int index, const std::shared_ptr<MaterialBase>& material)
	{
		m_Models[index].material = material;
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
			ModelSet model = { modelSet.model, modelSet.material, modelSet.transform };
			mesh->m_Models.push_back(model);
		}
		return mesh;
	}

}