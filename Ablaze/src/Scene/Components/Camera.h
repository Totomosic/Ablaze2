#pragma once
#include "Common.h"
#include "Motion\Transform.h"

namespace Ablaze
{

	enum class Projection
	{
		Perspective, Orthographic
	};

	class AB_API Camera : public Component
	{
	private:
		float m_Fov;
		Projection m_ProjectionType;
		float m_NearPlane;
		float m_FarPlane;
		Maths::Mat4 m_Projection;

	public:
		Camera(Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera(float x, float xMax, float y, float yMax, float nearPlane = 1.0f, float farPlane = 1000.0f);

		const Maths::Mat4& ProjectionMatrix() const;
		Maths::Mat4& ProjectionMatrix();
		float NearPlane() const;
		float& NearPlane();
		float FarPlane() const;
		float& FarPlane();
		Projection ProjectionType() const;
		Projection& ProjectionType();

		void SetNearPlane(float nearPlane);
		void SetFarPlane(float farPlane);
		void SetFOV(float fov, Angle angleType = Angle::Radians);
		void SetProjectionType(Projection projection);

		Maths::Vec3 ScreenToWorldPoint(const Maths::Vec3& screenpoint) const;
		Maths::Vec3 WorldToScreenPoint(const Maths::Vec3& worldpoint) const;

		void UpdateProjectionMatrix();

		String ToString() const override;
		Component* Clone() const override;
		void Serialize(JSONwriter& writer) const override;

	private:
		void CreateProjectionMatrix(float x, float xMax, float y, float yMax);

	};

}