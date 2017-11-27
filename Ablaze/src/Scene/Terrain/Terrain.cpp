#include "Terrain.h"
#include "Resources\__Resources__.h"
#include "Scene\Components\__Components__.h"

namespace Ablaze
{

	Terrain::Terrain(float width, float height, int xVerts, int zVerts, const MaterialBase& material, const Color& color) : GameObject(),
		m_TerrainData(this, width, height, xVerts, zVerts)
	{
		AddComponent<Transform>();
		AddComponent(new Mesh(ResourceManager::Instance().CreateGrid(width, height, xVerts, zVerts, color), material));
		m_TerrainData.m_VertexBuffer = mesh().GetModel(0).Get()->GetVertexArray()->GetVertexBuffer(0);
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
		retval.RecalculateNormals();
	}

}