#pragma once
#include "Common.h"
#include "HeightFunctions\__HeightFunctions__.h"
#include "Graphics\Buffers\__Buffers__.h"

namespace Ablaze
{

	class Terrain;

	class AB_API TerrainData : public Object
	{
	private:
		Terrain* m_Owner;

		float m_Width;
		float m_Depth;
		int m_xVertices;
		int m_zVertices;

		float* m_HeightMap;

	public:
		TerrainData(Terrain* owner, float width, float height, int xVerts, int zVerts);
		TerrainData(const TerrainData& other) = delete;
		~TerrainData();

		float GetHeight(int x, int y) const;
		float GetHeight(float x, float y) const; // Linearly interpolate between vertices

		void SetVertex(int x, int z, float height);
		void SetRegion(int x, int z, int width, int depth, float height);
		void SetRegion(int x, int z, int width, int depth, float* heights);
		void SetRegion(int x, int z, int width, int depth, Heightfunction& function);

		void SetOwner(Terrain* owner);

		String ToString() const override;

	private:
		int GetVertexIndex(int x, int z) const;
		void ApplyHeightmap();
		void ApplyVertex(int index, float height);
		int GetVBOIndex(int vertexIndex, VertexBuffer* vbo) const;

	};

}