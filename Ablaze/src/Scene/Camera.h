#pragma once
#include "Common.h"
#include "Entity.h"

namespace Ablaze
{

	enum class Projection
	{
		Perspective, Orthographic
	};

	class AB_API Camera : public Entity
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
		Camera(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Maths::Vec3& scale, const Mesh& mesh, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Maths::Vec3& scale, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Mesh& mesh, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera(const Maths::Vec3& position, const Maths::Quaternion& rotation, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera(const Maths::Vec3& position, const Mesh& mesh, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera(const Maths::Vec3& position, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera(float x, float y, float z, const Maths::Quaternion& rotation, const Maths::Vec3& scale, const Mesh& mesh, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera(float x, float y, float z, const Maths::Quaternion& rotation, const Maths::Vec3& scale, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera(float x, float y, float z, const Maths::Quaternion& rotation, const Mesh& mesh, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera(float x, float y, float z, const Maths::Quaternion& rotation, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera(float x, float y, float z, const Mesh& mesh, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
		Camera(float x, float y, float z, Projection projection = Projection::Perspective, float fov = Maths::PI / 3.0f, float nearPlane = 1.0f, float farPlane = 1000.0f);
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

		void UpdateProjectionMatrix();

		String ToString() const override;

	private:
		void CreateProjectionMatrix();

	};

}