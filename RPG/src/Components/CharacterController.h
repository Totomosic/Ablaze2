#pragma once
#include "AblazeInclude.h"

namespace Game
{

	class CharacterController : public Component
	{
	public:
		CharacterController();

		GameObject* Fire(float speed, const Vector3f& direction, Model* model = ResourceManager::Cube(), float offset = 0.0f, float size = 0.1f, Shader* shader = ResourceManager::DefaultColorShader(), const Color& color = Color::White());
		void ShotgunFire(float speed, int count, const Vector3f& primaryDirection, float angle);
		void Rockets(float speed, int count, const Vector3f& centerPoint);
		void Dash(float distance);

	};

}