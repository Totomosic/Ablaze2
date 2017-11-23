#include "TerrainData.h"
#include "Terrain.h"
#include "Scene\Components\__Components__.h"

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
		if (x < 0)
		{
			return GetHeight(0, z);
		}
		if (x >= m_xVertices)
		{
			return GetHeight(m_xVertices - 1, z);
		}
		if (z < 0)
		{
			return GetHeight(x, 0);
		}
		if (z >= m_zVertices)
		{
			return GetHeight(x, m_zVertices - 1);
		}
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

	void TerrainData::RecalculateNormals()
	{
		for (int j = 0; j < m_zVertices; j++)
		{
			for (int i = 0; i < m_xVertices; i++)
			{
				ApplyNormal(GetVertexIndex(i, j), CalculateNormal(i, j));
			}
		}
	}

	void TerrainData::ApplyNormal(int index, const Maths::Vec3& height)
	{
		m_VertexBuffer->Upload(&height.x, sizeof(float) * 3, (int64)GetNormalIndex(index, m_VertexBuffer));
	}

	void TerrainData::ApplyVertex(int index, float height)
	{
		m_VertexBuffer->Upload(&height, sizeof(float), (int64)GetVBOIndex(index, m_VertexBuffer));
	}

	int TerrainData::GetVBOIndex(int vertexIndex, VertexBuffer* vbo) const
	{
		BufferLayout& layout = vbo->GetLayout();
		int offset = vertexIndex * layout.GetStride();
		offset += layout.OffsetOf(Attribute::Position);
		offset += sizeof(float);
		return offset;
	}

	int TerrainData::GetNormalIndex(int vertexIndex, VertexBuffer* vbo) const
	{
		BufferLayout& layout = vbo->GetLayout();
		int offset = vertexIndex * layout.GetStride();
		offset += layout.OffsetOf(Attribute::Normal);
		return offset;
	}

	Maths::Vec3 TerrainData::CalculateNormal(int x, int y) const
	{
		float heightL = GetHeight(x - 1, y);
		float heightR = GetHeight(x + 1, y);
		float heightD = GetHeight(x, y - 1);
		float heightU = GetHeight(x, y + 1);
		return Maths::Vec3(heightL - heightR, 2.0, heightD - heightU).Normalize();
	}

}