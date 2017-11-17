#include "Terrain.h"

namespace Ablaze
{

	Terrain::Terrain(float width, float height, int xVerts, int zVerts, const MaterialBase& material, const Color& color) : GameObject(),
		m_TerrainData(this, width, height, xVerts, zVerts)
	{
		//Mesh(ResourceManager::Library().CreateGrid(width, height, xVerts, zVerts, color), material);
	}

	Terrain::~Terrain()
	{
	
	}

	TerrainData& Terrain::BeginEditing()
	{
		return m_TerrainData;
	}

	void Terrain::EndEditing(TerrainData& retval)
	{
		
	}

}