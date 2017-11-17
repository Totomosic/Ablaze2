#pragma once
#include "Scene\Components\Component.h"

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

		Maths::Vec3 Position() const;
		Maths::Quaternion Rotation() const;
		Maths::Vec3 Scale() const;

		const Maths::Vec3& LocalPosition() const;
		Maths::Vec3& LocalPosition();
		const Maths::Quaternion& LocalRotation() const;
		Maths::Quaternion& LocalRotation();
		const Maths::Vec3& LocalScale() const;
		Maths::Vec3& LocalScale();

		Maths::Vec3 Forward() const;
		Maths::Vec3 Right() const;
		Maths::Vec3 Up() const;

		void Translate(const Maths::Vec3& translation);
		void SetScale(const Maths::Vec3& scale);
		void SetScale(float scale);
		void Rotate(float angle, const Maths::Vec3& axis, Space space = Space::World, Angle angleType = Angle::Radians);
		void Rotate(const Maths::Quaternion& quaternion);

		Maths::Mat4 ToMatrix() const;
		String ToString() const override;

		Component* Clone() const override;

		Transform operator+(const Transform& other) const;

	};

}