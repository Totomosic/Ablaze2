#include "Radius.h"

Radius::Radius(float r, const Color& color) : Component(),
radius(r), color(color)
{

}	

Radius::Radius() : Radius(0, Color::White())
{

}

String Radius::ToString() const
{
	return std::to_string(radius);
}

Component* Radius::Clone() const
{
	Radius* r = new Radius(radius, color);
	return r;
}