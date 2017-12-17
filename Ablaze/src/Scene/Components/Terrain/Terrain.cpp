#include "Terrain.h"
#include "Resources\__Resources__.h"

#include "Scene\Components\Mesh.h"
#include "Scene\Components\Motion\Transform.h"

namespace Ablaze
{

	Terrain::Terrain(float width, float height, int xVerts, int zVerts, MaterialBase* material) : Component(),
		m_TerrainData(this, width, height, xVerts, zVerts), m_ModelIndex(-1), m_Material(material)
	{
		
	}

	void Terrain::Start()
	{
		if (m_GameObject->HasComponent<Mesh>())
		{
			m_ModelIndex = m_GameObject->mesh().ModelCount();
			m_GameObject->mesh().AddModel(Model::Grid(m_TerrainData.m_Width, m_TerrainData.m_Depth, m_TerrainData.m_xVertices, m_TerrainData.m_zVertices), m_Material);
		}
		else
		{
			m_ModelIndex = 0;
			m_GameObject->AddComponent(new Mesh(Model::Grid(m_TerrainData.m_Width, m_TerrainData.m_Depth, m_TerrainData.m_xVertices, m_TerrainData.m_zVertices), m_Material));
		}
		m_TerrainData.m_VertexBuffer = m_GameObject->mesh().GetModel(m_ModelIndex)->GetVertexArray()->GetVertexBuffer(0);
	}

	TerrainData& Terrain::BeginEditing()
	{
		return m_TerrainData;
	}

	void Terrain::EndEditing(TerrainData& retval)
	{
		retval.RecalculateNormals();
	}

	String Terrain::ToString() const
	{
		return "Terrain";
	}

	Component* Terrain::Clone() const
	{
		Terrain* t = new Terrain(m_TerrainData.m_Width, m_TerrainData.m_Depth, m_TerrainData.m_xVertices, m_TerrainData.m_zVertices, m_Material);
		t->m_ModelIndex = m_ModelIndex;
		t->m_TerrainData = m_TerrainData;
		return t;
	}

}