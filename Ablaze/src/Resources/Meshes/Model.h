#pragma once
#include "Common.h"
#include "Resources\Asset.h"
#include "Graphics\Buffers\__Buffers__.h"

namespace Ablaze
{

	namespace Internal
	{
		class Shapes;
	}

	class AB_API Model : public Asset
	{
	public:
		struct VertexSet
		{
			std::vector<Maths::Vec3> positions, normals;
			std::vector<Maths::Vec2> uvs;
		};

		struct IndexSet
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

	private:
		VertexArray* m_VertexArray;

	private:
		Model();
		Model(VertexArray* vertexArray);
		Model(const String& filename);
		~Model(); // Prevent stack objects and can only be deleted by ResourceManager

	public:
		VertexArray* GetVertexArray() const;

		void Reload() override;
		void Bind() const;
		void Unbind() const;

		String ToString() const override;
		void Serialize(JSONwriter& writer) const;

		friend class ResourceManager;
		friend class Internal::Shapes;

	private:
		void LoadOBJModel(const String& filename);
		void InsertVertex(std::vector<Vertex>& vertices, std::vector<uint>& indices, std::unordered_map<IndexSet, int>& mapping, VertexSet& inputVertices, IndexSet& indexSet);

	};

}