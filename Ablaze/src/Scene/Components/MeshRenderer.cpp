#include "MeshRenderer.h"

namespace Ablaze
{

	MeshRenderer::MeshRenderer() : Component(),
		m_Meshes()
	{

	}

	MeshRenderer::MeshRenderer(Mesh* mesh, const Maths::Matrix4f& transform) : MeshRenderer()
	{
		AddMesh(mesh, transform);
	}

	MeshRenderer::~MeshRenderer()
	{
		for (MeshSet& set : m_Meshes)
		{
			set.mesh->Decrement();
		}
	}

	int MeshRenderer::MeshCount() const
	{
		return m_Meshes.size();
	}

	const MeshSet& MeshRenderer::GetMeshSet(int index) const
	{
		AB_ASSERT(index < MeshCount(), "Index Out of Range");
		return m_Meshes[index];
	}

	MeshSet& MeshRenderer::GetMeshSet(int index)
	{
		AB_ASSERT(index < MeshCount(), "Index Out of Range");
		return m_Meshes[index];
	}

	Mesh* MeshRenderer::GetMesh(int index) const
	{
		return GetMeshSet(index).mesh;
	}

	const Maths::Matrix4f& MeshRenderer::GetTransform(int index) const
	{
		return GetMeshSet(index).transform;
	}

	Maths::Matrix4f& MeshRenderer::GetTransform(int index)
	{
		return GetMeshSet(index).transform;
	}

	void MeshRenderer::AddMesh(Mesh* mesh, const Maths::Matrix4f& transform)
	{
		m_Meshes.push_back({ mesh, transform });
		mesh->Increment();
	}

	void MeshRenderer::SetMesh(int index, Mesh* mesh)
	{
		Mesh* prev = GetMesh(index);
		mesh->Increment();
		m_Meshes[index].mesh = mesh;
		prev->Decrement();
	}

	void MeshRenderer::SetTransform(int index, const Maths::Matrix4f& transform)
	{
		AB_ASSERT(index < MeshCount(), "Index Out of Range");
		m_Meshes[index].transform = transform;
	}

	String MeshRenderer::ToString() const
	{
		return "MeshRenderer";
	}

	Component* MeshRenderer::Clone() const
	{
		MeshRenderer* mr = new MeshRenderer;
		for (const MeshSet& set : m_Meshes)
		{
			mr->AddMesh(set.mesh, set.transform); // increments mesh ref count
		}
		return mr;
	}

}