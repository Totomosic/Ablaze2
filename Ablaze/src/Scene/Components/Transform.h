#pragma once
#include "Component.h"

namespace Ablaze
{

	enum class Space
	{
		Local, World
	};

	enum class Angle
	{
		Radians, Degrees
	};

	class AB_API Transform : public Component
	{
	private:
		Maths::Vec3 m_Position;
		Maths::Quaternion m_Rotation;
		Maths::Vec3 m_Scale;

	public:
		Transform();
		Transform(const Maths::Vec3& position);
		Transform(const Maths::Vec3& position, const Maths::Quaternion& rotation);
		Transform(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Maths::Vec3& scale);
		Transform(const Maths::Vec3& position, const Maths::Vec3& scale);
		Transform(const Maths::Quaternion& rotation, const Maths::Vec3& scale);

		const Maths::Vec3& Position() const;
		Maths::Vec3& Position();
		const Maths::Quaternion& Rotation() const;
		Maths::Quaternion& Rotation();
		const Maths::Vec3& Scale() const;
		Maths::Vec3& Scale();

		Maths::Vec3 Forward() const;
		Maths::Vec3 Right() const;
		Maths::Vec3 Up() const;

		void Translate(const Maths::Vec3& translation);
		void Rotate(float angle, const Maths::Vec3& axis, Space space = Space::World, Angle angleType = Angle::Radians);

		Maths::Mat4 ToMatrix() const;
		String ToString() const override;

		Component* Clone() const override;

		Transform operator+(const Transform& other) const;

	};

}