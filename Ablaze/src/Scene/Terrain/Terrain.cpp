#include "Terrain.h"

namespace Ablaze
{

	Terrain::Terrain(float width, float height, int xVerts, int zVerts, const Material& material, const Color& color) : Entity(Mesh(ResourceManager::Library().CreateGrid(width, height, xVerts, zVerts, color), material)),
		m_TerrainData(this, width, height, xVerts, zVerts)
	{
	
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