#pragma once
#include "Common.h"
#include "Graphics\Buffers\__Buffers__.h"
#include "Resources\Asset.h"
#include "SubModel.h"

namespace Ablaze
{

	struct AB_API VertexSet
	{
		std::vector<Maths::Vector3f> positions;
		std::vector<Maths::Vector3f> normals;
		std::vector<Maths::Vector2f> uvs;
	};

	struct AB_API IndexSet
	{
		uint position;
		uint uv;
		uint normal;

		bool operator==(const IndexSet& other) const
		{
			return position == other.position && uv == other.uv && normal == other.normal;
		}

		friend struct std::hash<IndexSet>;
	};

	class Mesh;

	class AB_API Model : public Asset
	{
	private:
		VertexArray* m_VertexArray;
		std::vector<SubModel*> m_SubModels;

	public:
		Model(VertexArray* vertexArray);
		Model(VertexBuffer* vertices, SubModel* submodel);
		Model(const Filepath& objFile);
		~Model() override;

		VertexArray* GetVertexArray() const;
		SubModel* GetSubModel(int index) const;
		int SubModelCount() const;
		void AddSubModel(SubModel* model);

		void Reload() override;
		String ToString() const override;

	public:
		static Model* Rectangle(float width, float height, const Color& color = Color::White());
		static Model* Ellipse(float width, float height, const Color& color = Color::White());
		static Model* Cuboid(float width, float height, float depth, const Color& color = Color::White());
		static Model* Sphere(float radius, const Color& color = Color::White());
		static Model* Grid(float width, float depth, int xVertices, int zVertices, const Color& color = Color::White());

	private:
		void LoadOBJModel(const String& filename);
		void InsertVertex(std::vector<Vertex>& vertices, std::vector<uint>& indices, std::unordered_map<IndexSet, int>& mapping, VertexSet& inputVertices, IndexSet& indexSet);

	};

}