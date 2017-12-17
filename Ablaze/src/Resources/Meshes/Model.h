#pragma once
#include "Common.h"
#include "ModelInfo.h"
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
			std::vector<Maths::Vector3f> positions, normals;
			std::vector<Maths::Vector2f> uvs;
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

	public:
		Model();
		Model(VertexArray* vertexArray);
		Model(const String& filename);
		Model(const Model& other) = delete;
		~Model(); // Prevent stack objects and can only be deleted by ResourceManager

	public:
		VertexArray* GetVertexArray() const;

		void Reload() override;
		void Bind() const;
		void Unbind() const;

		ModelInfo Info() const;

		String ToString() const override;

		friend class ResourceManager;
		friend class Internal::Shapes;
		template<typename> friend class Resource;

	public:
		static Model* Rectangle(float width, float height, const Color& color = Color::White());
		static Model* Ellipse(float width, float height, const Color& color = Color::White());
		static Model* Cuboid(float width, float height, float depth, const Color& color = Color::White());
		static Model* Sphere(float radius, int spacing = 10, const Color& color = Color::White());
		static Model* Grid(float width, float depth, int xVerts, int zVerts, const Color& color = Color::White());

	private:
		void LoadOBJModel(const String& filename);
		void InsertVertex(std::vector<Vertex>& vertices, std::vector<uint>& indices, std::unordered_map<IndexSet, int>& mapping, VertexSet& inputVertices, IndexSet& indexSet);

	};

}