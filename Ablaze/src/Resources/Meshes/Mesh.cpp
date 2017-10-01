#include "Mesh.h"

namespace Ablaze
{

	Mesh::Mesh() : Object(),
		m_Models(), m_Materials()
	{
	
	}

	Mesh::Mesh(const Resource<Model>& model, Material* material) : Mesh()
	{
		AddModel(model, material);
	}

	Mesh::~Mesh()
	{
		for (auto material : m_Materials)
		{
			delete material;
		}
	}

	const Resource<Model>& Mesh::GetModel(int index) const
	{
		return m_Models[index];
	}

	Resource<Model>& Mesh::GetModel(int index)
	{
		return m_Models[index];
	}

	Material* Mesh::GetMaterial(int index) const
	{
		return m_Materials[index];
	}

	std::pair<const Resource<Model>&, Material*> Mesh::GetPair(int index) const
	{
		return std::pair<const Resource<Model>&, Material*>(GetModel(index), GetMaterial(index));
	}

	const std::vector<Resource<Model>>& Mesh::GetAllModels() const
	{
		return m_Models;
	}

	const std::vector<Material*>& Mesh::GetAllMaterials() const
	{
		return m_Materials;
	}

	void Mesh::AddModel(const Resource<Model>& model, Material* material)
	{
		m_Models.push_back(model);
		m_Materials.push_back(material);
	}

	String Mesh::ToString() const
	{
		return "Mesh";
	}

}