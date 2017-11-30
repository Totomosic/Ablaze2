#pragma once
#include "Common.h"
#include "Scene\GameObject.h"
#include "TerrainData.h"
#include "Resources\__Resources__.h"

namespace Ablaze
{

	class AB_API Terrain : public GameObject
	{
	private:
		TerrainData m_TerrainData;

	public:
		Terrain(float width, float height, int xVerts, int yVerts, const std::shared_ptr<MaterialBase>& material, const Color& color = Color::White());
		~Terrain();

		TerrainData& BeginEditing();
		void EndEditing(TerrainData& data);

		friend class TerrainData;

	};

}