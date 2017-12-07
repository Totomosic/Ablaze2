#pragma once
#include "Ablaze.h"

using namespace Ablaze;

class PlayerController : public Component
{
private:
	Keycode m_Forward;
	Keycode m_Back;
	Keycode m_Left;
	Keycode m_Right;
	Keycode m_Up;
	Keycode m_Down;
	float m_Speed;

public:
	PlayerController(float speed);
	PlayerController();

	float& Speed();

	Keycode& Forward();
	Keycode& Back();
	Keycode& Left();
	Keycode& Right();
	Keycode& Up();
	Keycode& Down();

	void Update(double elapsedSeconds) override;

	Component* Clone() const override;
	String ToString() const override;

};