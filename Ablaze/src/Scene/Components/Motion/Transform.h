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
		Maths::Vector3f m_Position;
		Maths::Quaternion m_Rotation;
		Maths::Vector3f m_Scale;

	public:
		Transform();
		Transform(const Maths::Vector3f& position);
		Transform(const Maths::Vector3f& position, const Maths::Quaternion& rotation);
		Transform(const Maths::Vector3f& position, const Maths::Quaternion& rotation, const Maths::Vector3f& scale);
		Transform(const Maths::Vector3f& position, const Maths::Vector3f& scale);
		Transform(const Maths::Quaternion& rotation, const Maths::Vector3f& scale);

		const Maths::Vector3f Position() const;
		const Maths::Quaternion Rotation() const;
		const Maths::Vector3f Scale() const;

		const Maths::Vector3f& LocalPosition() const;
		Maths::Vector3f& LocalPosition();
		const Maths::Quaternion& LocalRotation() const;
		Maths::Quaternion& LocalRotation();
		const Maths::Vector3f& LocalScale() const;
		Maths::Vector3f& LocalScale();

		Maths::Vector3f Forward() const;
		Maths::Vector3f Right() const;
		Maths::Vector3f Up() const;

		void SetLocalPosition(const Maths::Vector3f& position);
		void SetLocalPosition(float x, float y, float z);
		void Translate(const Maths::Vector3f& translation);
		void Translate(float x, float y, float z);
		void SetLocalScale(const Maths::Vector3f& scale);
		void SetLocalScale(float scale);
		void SetLocalScale(float x, float y, float z);
		void Rotate(float angle, const Maths::Vector3f& axis, Space space = Space::World, Angle angleType = Angle::Radians);
		void Rotate(const Maths::Quaternion& quaternion);

		Maths::Matrix4d ToMatrix() const;
		String ToString() const override;

		Component* Clone() const override;
		void Serialize(JSONwriter& writer) const override;

		Transform operator+(const Transform& other) const;

	};

}