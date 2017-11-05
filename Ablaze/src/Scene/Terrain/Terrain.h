#pragma once
#include "Common.h"
#include "Scene\Entity.h"
#include "TerrainData.h"
#include "Resources\__Resources__.h"

namespace Ablaze
{

	class AB_API Terrain : public Entity
	{
	private:
		TerrainData m_TerrainData;

	public:
		Terrain(float width, float height, int xVerts, int yVerts, const Material& material, const Color& color = Color::White());
		~Terrain();

		TerrainData& BeginEditing();
		void EndEditing(TerrainData& data);

		friend class TerrainData;

	};

}