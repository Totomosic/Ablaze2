#include "Mesh.h"

namespace Ablaze
{

	Mesh::Mesh() : Component(),
		m_Models()
	{
	
	}

	Mesh::Mesh(const Resource<Model>& model, const Material& material, const Maths::Mat4& transform) : Mesh()
	{
		AddModel(model, material, transform);
	}

	const Resource<Model>& Mesh::GetModel(int index) const
	{
		return m_Models[index].model;
	}

	Resource<Model>& Mesh::GetModel(int index)
	{
		return m_Models[index].model;
	}

	const Material& Mesh::GetMaterial(int index) const
	{
		return m_Models[index].material;
	}

	Material& Mesh::GetMaterial(int index)
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

	const std::vector<ModelSet>& Mesh::GetModelSets() const
	{
		return m_Models;
	}

	int Mesh::ModelCount() const
	{
		return m_Models.size();
	}

	void Mesh::AddModel(const Resource<Model>& model, const Material& material, const Maths::Mat4& transform)
	{
		m_Models.push_back({ model, material, transform });
	}

	String Mesh::ToString() const
	{
		return "Mesh";
	}

	Component* Mesh::Clone() const
	{
		Mesh* mesh = new Mesh;
		mesh->m_Models = m_Models;
		return mesh;
	}

}