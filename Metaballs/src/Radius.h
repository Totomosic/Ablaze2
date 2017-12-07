#pragma once
#include "Ablaze.h"

using namespace Ablaze;

struct Radius : public Component
{
public:
	float radius;
	Color color;

public:
	Radius(float r, const Color& color);
	Radius();

	String ToString() const override;
	Component* Clone() const override;

};