#include "Terrain.h"
#include "Resources\__Resources__.h"
#include "Scene\Components\__Components__.h"

namespace Ablaze
{

	Terrain::Terrain(float width, float height, int xVerts, int zVerts, const std::shared_ptr<MaterialBase>& material, const Color& color) : GameObject(),
		m_TerrainData(this, width, height, xVerts, zVerts)
	{
		AddComponent<Transform>();
		transform().LocalScale() = Maths::Vector3f(width, 1, height);
		AddComponent(new Mesh(ResourceManager::Instance().CreateGrid(xVerts, zVerts, color), material));
		m_TerrainData.m_VertexBuffer = mesh().GetModel(0)->GetVertexArray()->GetVertexBuffer(0);
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