#pragma once
#include "Common.h"
#include "Actor.h"

namespace Ablaze
{

	enum class Projection
	{
		Perspective, Orthographic
	};

	class AB_API Camera : public Actor
	{
	protected:
		float m_Fov;
		Projection m_ProjectionType;
		float m_NearPlane;
		float m_FarPlane;
		Maths::Mat4 m_Projection;

	public:
		Camera(const Transform& transform, const Mesh& mesh, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera(const Transform& transform, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera(const Mesh& mesh, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera(Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);

		const Maths::Mat4& ProjectionMatrix() const;
		Maths::Mat4& ProjectionMatrix();
		Maths::Mat4 ViewMatrix() const;
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

		void Update(double elapsedSeconds) override;
		void UpdateProjectionMatrix();

		String ToString() const override;

		friend class Layer;

	private:
		void CreateProjectionMatrix();

	};

}