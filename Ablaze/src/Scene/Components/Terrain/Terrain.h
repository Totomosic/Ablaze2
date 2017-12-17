#pragma once
#include "Common.h"
#include "Scene\Components\Component.h"
#include "TerrainData.h"

namespace Ablaze
{

	class AB_API Terrain : public Component
	{
	private:
		TerrainData m_TerrainData;
		int m_ModelIndex;
		MaterialBase* m_Material;

	public:
		Terrain(float width, float height, int xVerts, int yVerts, MaterialBase* material);

		void Start() override;

		TerrainData& BeginEditing();
		void EndEditing(TerrainData& data);

		String ToString() const override;
		Component* Clone() const override;

		friend class TerrainData;

	};

}