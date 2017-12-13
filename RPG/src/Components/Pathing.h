#pragma once
#include "Ablaze.h"

using namespace Ablaze;
using namespace Ablaze::Maths;

class Pathing : public Component
{
private:
	Vector3f m_Target;
	float m_Speed;

public:
	Pathing(float speed = 10);
	Pathing(const Maths::Vector3f& target, float speed = 10);

	bool HasReachedTarget() const;

	void Update(double elapsedSeconds) override;
	void SetTarget(const Maths::Vector3f& target);
	void SetSpeed(float speed);

	Component* Clone() const override;
	String ToString() const override;

};