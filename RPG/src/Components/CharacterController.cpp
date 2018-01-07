#include "CharacterController.h"

namespace Game
{

	CharacterController::CharacterController() : Component()
	{

	}

	GameObject* CharacterController::Fire(float speed, const Vector3f& direction, Model* model, float offset, float size, Shader* shader, const Color& color)
	{
		GameObject* bullet = GameObject::Instantiate("Bullet", m_GameObject->transform().Position().x, m_GameObject->transform().Position().y, m_GameObject->transform().Position().z)
			->AddComponent(new MeshRenderer(new Mesh(model, Material(color, shader)), Matrix4f::Scale(size)))
			->AddComponent(new RigidBody(false));
		bullet->transform().LocalPosition() += m_GameObject->transform().Right() * offset;
		bullet->GetComponent<RigidBody>().Velocity() = direction * speed;
		AddToScene(bullet);
		bullet->Destroy(5);
		return bullet;
	}

	void CharacterController::ShotgunFire(float speed, int count, const Vector3f& primaryDirection, float angle)
	{
		for (int i = 0; i < count; i++)
		{
			Vector3f direction = primaryDirection;
			float mult = -count / 2.0f + 0.5f + i;
			direction = Quaternion::FromAngleAxis(mult * angle, Vector3f::Up()) * direction;
			Fire(speed, direction);
		}
	}

	void CharacterController::Rockets(float speed, int count, const Vector3f& centerPoint)
	{
		for (int i = 0; i < count; i++)
		{
			float offset = Map(i, 0, count - 1, -0.5f, 0.5f);
			Vector3f direction = centerPoint - (m_GameObject->transform().Position() + m_GameObject->transform().Right() * offset);
			direction.y = 0.0f;
			direction = direction.Normalize();
			Fire(speed, direction, ResourceManager::Cube(), offset);
		}
	}

	void CharacterController::Dash(float distance)
	{
		m_GameObject->transform().LocalPosition() += m_GameObject->transform().Forward() * distance;
	}

}