#include "PlayerController.h"

PlayerController::PlayerController(float speed) : Component()
{
	m_Speed = speed;
	m_Forward = Keycode::W;
	m_Back = Keycode::S;
	m_Left = Keycode::A;
	m_Right = Keycode::D;
	m_Up = Keycode::None;
	m_Down = Keycode::None;
}

PlayerController::PlayerController() : PlayerController(1)
{

}

float& PlayerController::Speed()
{
	return m_Speed;
}

Keycode& PlayerController::Forward()
{
	return m_Forward;
}

Keycode& PlayerController::Back()
{
	return m_Back;
}

Keycode& PlayerController::Left()
{
	return m_Left;
}

Keycode& PlayerController::Right()
{
	return m_Right;
}

Keycode& PlayerController::Up()
{
	return m_Up;
}

Keycode& PlayerController::Down()
{
	return m_Down;
}

void PlayerController::Update(double elapsedSeconds)
{
	if (Owner()->HasComponent<Transform>())
	{
		Transform& t = Owner()->transform();
		if (Input::KeyDown(m_Forward))
		{
			t.LocalPosition() += t.Forward() * Speed() * elapsedSeconds;
		}
		if (Input::KeyDown(m_Back))
		{
			t.LocalPosition() -= t.Forward() * Speed() * elapsedSeconds;
		}
		if (Input::KeyDown(m_Right))
		{
			t.LocalPosition() += t.Right() * Speed() * elapsedSeconds;
		}
		if (Input::KeyDown(m_Left))
		{
			t.LocalPosition() -= t.Right() * Speed() * elapsedSeconds;
		}
		if (Input::KeyDown(m_Up))
		{
			t.LocalPosition() += t.Up() * Speed() * elapsedSeconds;
		}
		if (Input::KeyDown(m_Down))
		{
			t.LocalPosition() -= t.Up() * Speed() * elapsedSeconds;
		}
	}
}

Component* PlayerController::Clone() const
{
	PlayerController* p = new PlayerController;
	p->m_Forward = m_Forward;
	p->m_Back = m_Back;
	p->m_Left = m_Left;
	p->m_Right = m_Right;
	p->m_Up = m_Up;
	p->m_Down = m_Down;
	return p;
}

String PlayerController::ToString() const
{
	return "PlayerController";
}