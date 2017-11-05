#include "TerrainData.h"
#include "Terrain.h"

namespace Ablaze
{
	
	TerrainData::TerrainData(Terrain* owner, float width, float depth, int xVerts, int zVerts) : Object(),
		m_Owner(owner), m_Width(width), m_Depth(depth), m_xVertices(xVerts), m_zVertices(zVerts), m_HeightMap(new float[m_xVertices * m_zVertices])
	{
		memset(m_HeightMap, 0, m_xVertices * m_zVertices * sizeof(float));
	}

	TerrainData::~TerrainData()
	{
		delete[] m_HeightMap;
	}

	float TerrainData::GetHeight(int x, int z) const
	{
		return m_HeightMap[GetVertexIndex(x, z)];
	}

	float TerrainData::GetHeight(float x, float z) const
	{
		int intX = (int)x;
		int intZ = (int)z;
		float fracX = x - intX;
		float fracZ = z - intZ;

		float f0 = GetHeight(intX, intZ);
		float f1 = GetHeight(intX + 1, intZ);
		float f2 = GetHeight(intX, intZ + 1);
		float f3 = GetHeight(intX + 1, intZ + 1);

		float i0 = Map(fracX, 0.0f, 1.0f, f0, f1);
		float i1 = Map(fracX, 0.0f, 1.0f, f2, f3);
		
		return Map(fracZ, 0.0f, 1.0f, i0, i1);
	}

	void TerrainData::SetVertex(int x, int y, float height)
	{
		int index = GetVertexIndex(x, y);
		m_HeightMap[index] = height;
		ApplyVertex(index, height);
	}

	void TerrainData::SetRegion(int x, int z, int width, int depth, float height)
	{
		for (int i = z; i < z + depth; i++)
		{
			for (int j = x; j < x + width; j++)
			{
				SetVertex(j, i, height);
			}
		}
	}

	void TerrainData::SetRegion(int x, int z, int width, int depth, float* heights)
	{
		int index = 0;
		for (int i = z; i < z + depth; i++)
		{
			for (int j = x; j < x + width; j++)
			{
				SetVertex(j, i, heights[index]);
				index++;
			}
		}
	}

	void TerrainData::SetRegion(int x, int z, int width, int depth, Heightfunction& function)
	{
		float* data = function(x, z, width, depth);
		SetRegion(x, z, width, depth, data);
		delete[] data;
	}

	void TerrainData::SetOwner(Terrain* terrain)
	{
		m_Owner = terrain;
	}

	String TerrainData::ToString() const
	{
		return "TerrainData";
	}

	int TerrainData::GetVertexIndex(int x, int z) const
	{
		return x + z * m_xVertices;
	}

	void TerrainData::ApplyHeightmap()
	{

	}

	void TerrainData::ApplyVertex(int index, float height)
	{
		VertexBuffer* vbo = m_Owner->GetMesh().GetModel(0)->GetVertexArray()->GetVertexBuffer(0);
		vbo->Upload(&height, sizeof(float), (int64)GetVBOIndex(index, vbo));
	}

	int TerrainData::GetVBOIndex(int vertexIndex, VertexBuffer* vbo) const
	{
		BufferLayout& layout = vbo->GetLayout();
		int offset = vertexIndex * layout.GetStride();
		offset += layout.OffsetOf(Attribute::Position);
		offset += sizeof(float);
		return offset;
	}

}