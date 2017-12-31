#include "Model.h"
#include "Shapes.h"

template<>
struct std::hash<Ablaze::IndexSet>
{
	const size_t operator()(const Ablaze::IndexSet& key) const
	{
		return (key.position) ^ (key.normal << 14) ^ (key.uv << 23);
	}
};

namespace Ablaze
{

	Model::Model(VertexArray* vertexArray) : Asset(),
		m_VertexArray(vertexArray), m_SubModels()
	{
		for (IndexBuffer* ibo : vertexArray->GetIndexBuffers())
		{
			m_SubModels.push_back(new SubModel(ibo));
		}
	}

	Model::Model(VertexBuffer* vertices, SubModel* submodel) : Model(new VertexArray)
	{
		m_VertexArray->AddVertexBuffer(vertices);
		AddSubModel(submodel);
	}

	Model::Model(const Filepath& objFile) : Model(new VertexArray)
	{
		AB_ASSERT(objFile.Exists(), "OBJ File: " + objFile.Path() + " could not be found");
		LoadOBJModel(objFile.Path());
	}

	Model::~Model()
	{
		delete m_VertexArray;
		for (SubModel* m : m_SubModels)
		{
			delete m;
		}
	}

	VertexArray* Model::GetVertexArray() const
	{
		return m_VertexArray;
	}

	SubModel* Model::GetSubModel(int index) const
	{
		AB_ASSERT(index < m_SubModels.size(), "Index Out of Range");
		return m_SubModels[index];
	}

	int Model::SubModelCount() const
	{
		return m_SubModels.size();
	}

	void Model::AddSubModel(SubModel* submodel)
	{
		m_SubModels.push_back(submodel);
		m_VertexArray->AddIndexBuffer(submodel->GetIndexBuffer());
	}

	void Model::Reload()
	{
	
	}

	String Model::ToString() const
	{
		return "Model";
	}

	Model* Model::Rectangle(float width, float height, const Color& color)
	{
		return new Model(Internal::Shapes::Rectangle(width, height, color));
	}

	Model* Model::Ellipse(float width, float height, const Color& color)
	{
		return new Model(Internal::Shapes::Ellipse(width, height, 100, color));
	}

	Model* Model::Cuboid(float width, float height, float depth, const Color& color)
	{
		return new Model(Internal::Shapes::Cuboid(width, height, depth, color));
	}

	Model* Model::Sphere(float radius, const Color& color)
	{
		return new Model(Internal::Shapes::Sphere(radius, 10, color));
	}

	Model* Model::Grid(float width, float depth, int xVertices, int zVertices, const Color& color)
	{
		return new Model(Internal::Shapes::Grid(width, depth, xVertices, zVertices, color));
	}


	void UpdateMinMax(float x, float y, float z, float* minX, float* maxX, float* minY, float* maxY, float* minZ, float* maxZ)
	{
		if (x < *minX)
		{
			*minX = x;
		}
		if (x > *maxX)
		{
			*maxX = x;
		}
		if (y < *minY)
		{
			*minY = y;
		}
		if (y > *maxY)
		{
			*maxY = y;
		}
		if (z < *minZ)
		{
			*minZ = z;
		}
		if (z > *maxZ)
		{
			*maxZ = z;
		}
	}

	void Model::LoadOBJModel(const String& filename)
	{
		File f = Filesystem::OpenFile(filename, OpenFlags::Read);
		String data = f.ReadText();
		std::vector<String> lines = SplitString(data, "\n");
		f.Close();
		VertexSet inputVertices;
		std::vector<Vertex> vertices;
		std::vector<uint> indices;
		std::unordered_map<IndexSet, int> mapping;

		float minX = (float)+1e10;
		float maxX = (float)-1e10;
		float minY = (float)+1e10;
		float maxY = (float)-1e10;
		float minZ = (float)+1e10;
		float maxZ = (float)-1e10;

		uint i = 0;
		for (String line : lines)
		{
			const char* cstr = line.c_str();
			if (strstr(cstr, "#")) // Comment
			{
				continue;
			}
			if (strstr(cstr, "mtl")) // material
			{
				continue;
			}
			if (strstr(cstr, "s")) // ??
			{
				continue;
			}
			if (strstr(cstr, "g")) // ??
			{
				continue;
			}
			if (strstr(cstr, "off")) // ??
			{
				continue;
			}
			else if (strstr(cstr, "v"))
			{
				if (strstr(cstr, "vt"))
				{
					Maths::Vector2f uv;
					int result = sscanf(cstr, "%*s %f %f", &uv.x, &uv.y);
					if (result != 2)
						continue;
					inputVertices.uvs.push_back(uv);
				}
				else if (strstr(cstr, "vn"))
				{
					Maths::Vector3f normal;
					int result = sscanf(cstr, "%*s %f %f %f", &normal.x, &normal.y, &normal.z);
					if (result != 3)
						continue;
					inputVertices.normals.push_back(normal);
				}
				else
				{
					Maths::Vector3f position;
					int result = sscanf(cstr, "%*s %f %f %f", &position.x, &position.y, &position.z);
					UpdateMinMax(position.x, position.y, position.z, &minX, &maxX, &minY, &maxY, &minZ, &maxZ);
					if (result != 3)
						continue;
					inputVertices.positions.push_back(position);
				}
			}
			else if (strstr(cstr, "f"))
			{
				IndexSet firstIndexSet[4];
				IndexSet indexSet[3];
				int result = sscanf(cstr, "%*s %d/%d/%d %d/%d/%d %d/%d/%d %d/%d/%d", &firstIndexSet[0].position, &firstIndexSet[0].uv, &firstIndexSet[0].normal, &firstIndexSet[1].position, &firstIndexSet[1].uv, &firstIndexSet[1].normal, &firstIndexSet[2].position, &firstIndexSet[2].uv, &firstIndexSet[2].normal, &firstIndexSet[3].position, &firstIndexSet[3].uv, &firstIndexSet[3].normal);
				if (result == 12)
				{
					InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[0]);
					InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[1]);
					InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[2]);
					InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[0]);
					InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[2]);
					InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[3]);
				}
				else
				{
					result = sscanf(cstr, "%*s %d/%d/%d %d/%d/%d %d/%d/%d", &indexSet[0].position, &indexSet[0].uv, &indexSet[0].normal, &indexSet[1].position, &indexSet[1].uv, &indexSet[1].normal, &indexSet[2].position, &indexSet[2].uv, &indexSet[2].normal);
					if (result == 9)
					{
						InsertVertex(vertices, indices, mapping, inputVertices, indexSet[0]);
						InsertVertex(vertices, indices, mapping, inputVertices, indexSet[1]);
						InsertVertex(vertices, indices, mapping, inputVertices, indexSet[2]);
					}
					else
					{
						result = sscanf(cstr, "%*s %d//%d %d//%d %d//%d %d//%d", &firstIndexSet[0].position, &firstIndexSet[0].normal, &firstIndexSet[1].position, &firstIndexSet[1].normal, &firstIndexSet[2].position, &firstIndexSet[2].normal, &firstIndexSet[3].position, &firstIndexSet[3].normal);
						if (result == 8)
						{
							firstIndexSet[0].uv = 0;
							firstIndexSet[1].uv = 0;
							firstIndexSet[2].uv = 0;
							firstIndexSet[3].uv = 0;
							InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[0]);
							InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[1]);
							InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[2]);
							InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[0]);
							InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[2]);
							InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[3]);
						}
						else
						{
							result = sscanf(cstr, "%*s %d//%d %d//%d %d//%d", &indexSet[0].position, &indexSet[0].normal, &indexSet[1].position, &indexSet[1].normal, &indexSet[2].position, &indexSet[2].normal);
							if (result == 6)
							{
								indexSet[0].uv = 0;
								indexSet[1].uv = 0;
								indexSet[2].uv = 0;
								InsertVertex(vertices, indices, mapping, inputVertices, indexSet[0]);
								InsertVertex(vertices, indices, mapping, inputVertices, indexSet[1]);
								InsertVertex(vertices, indices, mapping, inputVertices, indexSet[2]);
							}
							else
							{
								result = sscanf(cstr, "%*s %d/%d %d/%d %d/%d", &indexSet[0].position, &indexSet[0].uv, &indexSet[1].position, &indexSet[1].uv, &indexSet[2].position, &indexSet[2].uv);
								if (result == 6)
								{
									indexSet[0].normal = 0;
									indexSet[1].normal = 0;
									indexSet[2].normal = 0;
									InsertVertex(vertices, indices, mapping, inputVertices, indexSet[0]);
									InsertVertex(vertices, indices, mapping, inputVertices, indexSet[1]);
									InsertVertex(vertices, indices, mapping, inputVertices, indexSet[2]);
								}
								else
								{
									result = sscanf(cstr, "%*s %d/%d %d/%d %d/%d %d/%d", &firstIndexSet[0].position, &firstIndexSet[0].uv, &firstIndexSet[1].position, &firstIndexSet[1].uv, &firstIndexSet[2].position, &firstIndexSet[2].uv, &firstIndexSet[3].position, &firstIndexSet[3].uv);
									if (result == 8)
									{
										firstIndexSet[0].normal = 0;
										firstIndexSet[1].normal = 0;
										firstIndexSet[2].normal = 0;
										firstIndexSet[3].normal = 0;
										InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[0]);
										InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[1]);
										InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[2]);
										InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[0]);
										InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[2]);
										InsertVertex(vertices, indices, mapping, inputVertices, firstIndexSet[3]);
									}
									else
									{
										AB_ERROR("Skipped Loading SubModel Face");
										continue;
									}
								}
							}
						}
					}
				}
			}
		}

		VertexBuffer* vbo = m_VertexArray->CreateAttribute(vertices.size() * sizeof(Vertex), BufferLayout::Vertex());
		vbo->Upload(&vertices[0], vertices.size() * sizeof(Vertex));
		IndexBuffer* buffer = m_VertexArray->CreateIndexBuffer(&indices[0], indices.size() * sizeof(GLuint));
		m_SubModels.push_back(new SubModel(buffer));
	}

	void Model::InsertVertex(std::vector<Vertex>& vertices, std::vector<uint>& indices, std::unordered_map<IndexSet, int>& mapping, VertexSet& inputVertices, IndexSet& indexSet)
	{
		auto lookup = mapping.find(indexSet);
		if (lookup != mapping.end())
		{
			indices.push_back(lookup->second);
		}
		else
		{
			mapping[indexSet] = (int)vertices.size();
			indices.push_back(vertices.size());

			Maths::Vector3f position;
			Maths::Vector3f normal;
			Maths::Vector2f tex;

			if (indexSet.position == 0 || indexSet.position - 1 >= inputVertices.positions.size())
			{

			}
			else
			{
				position = inputVertices.positions[indexSet.position - 1];
			}

			if (indexSet.normal == 0 || indexSet.normal - 1 >= inputVertices.normals.size())
			{
				normal = Maths::Vector3f(0, 1, 0);
			}
			else
			{
				normal = inputVertices.normals[indexSet.normal - 1];
			}

			if (indexSet.uv == 0 || indexSet.uv - 1 >= inputVertices.uvs.size())
			{
				tex = Maths::Vector2f(0, 0);
			}
			else
			{
				tex = inputVertices.uvs[indexSet.uv - 1];
			}

			Vertex vertex = { position, normal, tex, Color::White(), Maths::Vector3f(0, 0, 1) };
			vertices.push_back(vertex);
		}
	}

}
