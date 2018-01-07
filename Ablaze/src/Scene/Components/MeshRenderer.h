#pragma once
#include "Scene\Components\Component.h"
#include "Resources\Meshes\Mesh.h"

namespace Ablaze
{

	struct AB_API MeshSet
	{
	public:
		Mesh* mesh;
		Maths::Matrix4f transform;

	};

	class AB_API MeshRenderer : public Component
	{
	private:
		std::vector<MeshSet> m_Meshes;
		
	public:
		MeshRenderer();
		MeshRenderer(Mesh* mesh, const Maths::Matrix4f& transform = Maths::Matrix4f::Identity());
		~MeshRenderer() override;

		int MeshCount() const;
		const MeshSet& GetMeshSet(int index) const;
		MeshSet& GetMeshSet(int index);
		Mesh* GetMesh(int index) const;
		const Maths::Matrix4f& GetTransform(int index) const;
		Maths::Matrix4f& GetTransform(int index);

		void AddMesh(Mesh* mesh, const Maths::Matrix4f& transform = Maths::Matrix4f::Identity());

		void SetMesh(int index, Mesh* mesh);
		void SetTransform(int index, const Maths::Matrix4f& transform);

		String ToString() const override;
		Component* Clone() const override;

	};

}