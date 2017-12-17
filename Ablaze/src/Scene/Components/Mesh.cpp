#include "Mesh.h"

namespace Ablaze
{

	Mesh::Mesh() : Component(),
		m_Models()
	{
		
	}

	Mesh::Mesh(Model* model, MaterialBase* material, const Maths::Matrix4d& transform, bool canDeleteModel, bool canDeleteMaterial) : Mesh()
	{
		AddModel(model, material, transform, canDeleteModel, canDeleteMaterial);
	}

	Mesh::~Mesh()
	{
		for (ModelSet& model : m_Models)
		{
			if (model.deleteModel)
			{
				delete model.model;
			}
			if (model.deleteMaterial)
			{
				delete model.material;
			}
		}
	}

	Model* const Mesh::GetModel(int index) const
	{
		return m_Models[index].model;
	}

	Model* Mesh::GetModel(int index)
	{
		return m_Models[index].model;
	}

	MaterialBase* const Mesh::GetMaterial(int index) const
	{
		return m_Models[index].material;
	}

	MaterialBase* Mesh::GetMaterial(int index)
	{
		return m_Models[index].material;
	}

	const Maths::Matrix4d& Mesh::GetTransform(int index) const
	{
		return m_Models[index].transform;
	}

	Maths::Matrix4d& Mesh::GetTransform(int index)
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

	void Mesh::AddModel(Model* model, MaterialBase* material, const Maths::Matrix4d& transform, bool canDeleteModel, bool canDeleteMaterial)
	{
		m_Models.push_back({ model, material, transform, canDeleteModel, canDeleteMaterial });
	}

	void Mesh::SetModel(int index, Model* model)
	{
		Model* prev = m_Models[index].model;
		m_Models[index].model = model;
		if (m_Models[index].deleteModel)
		{
			delete prev;
		}
	}

	void Mesh::SetMaterial(int index, MaterialBase* material)
	{
		MaterialBase* prev = m_Models[index].material;
		m_Models[index].material = material;
		if (m_Models[index].deleteMaterial)
		{
			delete prev;
		}
	}

	void Mesh::RemoveModel(int index)
	{
		m_Models.erase(m_Models.begin() + index);
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
		mesh->m_Models = m_Models;
		return mesh;
	}

}