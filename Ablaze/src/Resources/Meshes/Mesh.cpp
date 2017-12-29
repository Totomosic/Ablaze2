#include "Mesh.h"

namespace Ablaze
{

	Mesh::Mesh(Model* model, Material* material) : Asset(),
		m_Model(model), m_DefaultMaterial(material)
	{
		model->Increment();
		material->Increment();
	}

	Mesh::~Mesh()
	{
		m_Model->Decrement();
		m_DefaultMaterial->Decrement();
	}

	void Mesh::Reload()
	{
	
	}

	Model* Mesh::GetModel() const
	{
		return m_Model;
	}

	Material* Mesh::GetDefaultMaterial() const
	{
		return m_DefaultMaterial;
	}

	void Mesh::SetModel(Model* model)
	{
		m_Model->Decrement();	
		m_Model = model;
		m_Model->Increment();
	}

	void Mesh::SetDefaultMaterial(Material* material)
	{
		m_DefaultMaterial->Decrement();
		m_DefaultMaterial = material;
		m_DefaultMaterial->Increment();
	}

	String Mesh::ToString() const
	{
		return "Mesh";
	}

	Mesh* Mesh::Rectangle(float width, float height, Material* material)
	{
		return new Mesh(Model::Rectangle(width, height), material);
	}

	Mesh* Mesh::Ellipse(float width, float height, Material* material)
	{
		return new Mesh(Model::Ellipse(width, height), material);
	}

	Mesh* Mesh::Cuboid(float width, float height, float depth, Material* material)
	{
		return new Mesh(Model::Cuboid(width, height, depth), material);
	}

	Mesh* Mesh::Sphere(float radius, Material* material)
	{
		return new Mesh(Model::Sphere(radius), material);
	}

	Mesh* Mesh::Grid(float width, float height, int xVerts, int zVerts, Material* material)
	{
		return new Mesh(Model::Grid(width, height, xVerts, zVerts), material);
	}

}