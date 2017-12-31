#include "Mesh.h"

namespace Ablaze
{

	Mesh::Mesh(Model* model, const Material& material) : Asset(),
		m_Model(model), m_DefaultMaterial(material)
	{
		model->Increment();
	}

	Mesh::Mesh(Model* model) : Mesh(model, Material())
	{
	
	}

	Mesh::~Mesh()
	{
		m_Model->Decrement();
	}

	void Mesh::Reload()
	{
	
	}

	Model* Mesh::GetModel() const
	{
		return m_Model;
	}

	const Material& Mesh::GetMaterial() const
	{
		return m_DefaultMaterial;
	}

	Material& Mesh::GetMaterial()
	{
		return m_DefaultMaterial;
	}

	void Mesh::SetModel(Model* model)
	{
		m_Model->Decrement();	
		m_Model = model;
		m_Model->Increment();
	}

	void Mesh::SetMaterial(const Material& material)
	{
		m_DefaultMaterial = material;
	}

	String Mesh::ToString() const
	{
		return "Mesh";
	}

	Mesh* Mesh::Rectangle(float width, float height, const Material& material)
	{
		return new Mesh(Model::Rectangle(width, height), material);
	}

	Mesh* Mesh::Ellipse(float width, float height, const Material& material)
	{
		return new Mesh(Model::Ellipse(width, height), material);
	}

	Mesh* Mesh::Cuboid(float width, float height, float depth, const Material& material)
	{
		return new Mesh(Model::Cuboid(width, height, depth), material);
	}

	Mesh* Mesh::Sphere(float radius, const Material& material)
	{
		return new Mesh(Model::Sphere(radius), material);
	}

	Mesh* Mesh::Grid(float width, float height, int xVerts, int zVerts, const Material& material)
	{
		return new Mesh(Model::Grid(width, height, xVerts, zVerts), material);
	}

}