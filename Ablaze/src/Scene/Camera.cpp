#include "Camera.h"
#include "Graphics\Graphics.h"
#include "SceneManager.h"

namespace Ablaze
{

	Camera::Camera(const Transform& transform, const Mesh& mesh, Projection projection, float fov, float nearPlane, float farPlane) : Entity(transform, mesh, false),
		m_Fov(fov), m_ProjectionType(projection), m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
		CreateProjectionMatrix();
		if (SceneManager::Instance().HasScene())
		{
			SceneManager::Instance().CurrentScene().AddCamera(this);
		}
	}

	Camera::Camera(const Transform& transform, Projection projection, float fov, float nearPlane, float farPlane) : Entity(transform, false),
		m_Fov(fov), m_ProjectionType(projection), m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
		CreateProjectionMatrix();
		if (SceneManager::Instance().HasScene())
		{
			SceneManager::Instance().CurrentScene().AddCamera(this);
		}
	}

	Camera::Camera(const Mesh& mesh, Projection projection, float fov, float nearPlane, float farPlane) : Camera(Transform(), mesh, projection, fov, nearPlane, farPlane)
	{

	}

	Camera::Camera(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Maths::Vec3& scale, const Mesh& mesh, Projection projection, float fov, float nearPlane, float farPlane) : Camera(Transform(position, rotation, scale), mesh, projection, fov, nearPlane, farPlane)
	{

	}

	Camera::Camera(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Maths::Vec3& scale, Projection projection, float fov, float nearPlane, float farPlane) : Camera(Transform(position, rotation, scale), projection, fov, nearPlane, farPlane)
	{

	}

	Camera::Camera(const Maths::Vec3& position, const Maths::Quaternion& rotation, const Mesh& mesh, Projection projection, float fov, float nearPlane, float farPlane) : Camera(Transform(position, rotation), mesh, projection, fov, nearPlane, farPlane)
	{

	}

	Camera::Camera(const Maths::Vec3& position, const Maths::Quaternion& rotation, Projection projection, float fov, float nearPlane, float farPlane) : Camera(Transform(position, rotation), projection, fov, nearPlane, farPlane)
	{

	}

	Camera::Camera(const Maths::Vec3& position, const Mesh& mesh, Projection projection, float fov, float nearPlane, float farPlane) : Camera(Transform(position), mesh, projection, fov, nearPlane, farPlane)
	{

	}

	Camera::Camera(const Maths::Vec3& position, Projection projection, float fov, float nearPlane, float farPlane) : Camera(Transform(position), projection, fov, nearPlane, farPlane)
	{

	}

	Camera::Camera(float x, float y, float z, const Maths::Quaternion& rotation, const Maths::Vec3& scale, const Mesh& mesh, Projection projection, float fov, float nearPlane, float farPlane) : Camera(Maths::Vec3(x, y, z), rotation, scale, mesh, projection, fov, nearPlane, farPlane)
	{

	}

	Camera::Camera(float x, float y, float z, const Maths::Quaternion& rotation, const Maths::Vec3& scale, Projection projection, float fov, float nearPlane, float farPlane) : Camera(Maths::Vec3(x, y, z), rotation, scale, projection, fov, nearPlane, farPlane)
	{

	}

	Camera::Camera(float x, float y, float z, const Maths::Quaternion& rotation, const Mesh& mesh, Projection projection, float fov, float nearPlane, float farPlane) : Camera(Maths::Vec3(x, y, z), rotation, mesh, projection, fov, nearPlane, farPlane)
	{

	}

	Camera::Camera(float x, float y, float z, const Maths::Quaternion& rotation, Projection projection, float fov, float nearPlane, float farPlane) : Camera(Maths::Vec3(x, y, z), rotation, projection, fov, nearPlane, farPlane)
	{

	}

	Camera::Camera(float x, float y, float z, const Mesh& mesh, Projection projection, float fov, float nearPlane, float farPlane) : Camera(Maths::Vec3(x, y, z), mesh, projection, fov, nearPlane, farPlane)
	{

	}

	Camera::Camera(float x, float y, float z, Projection projection, float fov, float nearPlane, float farPlane) : Camera(Maths::Vec3(x, y, z), projection, fov, nearPlane, farPlane)
	{

	}

	Camera::Camera(Projection projection, float fov, float nearPlane, float farPlane) : Camera(0, 0, 0, projection, fov, nearPlane, farPlane)
	{

	}

	const Maths::Mat4& Camera::ProjectionMatrix() const
	{
		return m_Projection;
	}

	Maths::Mat4& Camera::ProjectionMatrix()
	{
		return m_Projection;
	}

	Maths::Mat4 Camera::ViewMatrix() const
	{
		return Transform().ToMatrix().Inverse();
	}

	float Camera::NearPlane() const
	{
		return m_NearPlane;
	}

	float& Camera::NearPlane()
	{
		return m_NearPlane;
	}

	float Camera::FarPlane() const
	{
		return m_FarPlane;
	}

	float& Camera::FarPlane()
	{
		return m_FarPlane;
	}

	Projection Camera::ProjectionType() const
	{
		return m_ProjectionType;
	}

	Projection& Camera::ProjectionType()
	{
		return m_ProjectionType;
	}

	void Camera::SetNearPlane(float nearPlane)
	{
		m_NearPlane = nearPlane;
		UpdateProjectionMatrix();
	}

	void Camera::SetFarPlane(float farPlane)
	{
		m_FarPlane = farPlane;
		UpdateProjectionMatrix();
	}

	void Camera::SetFOV(float fov, Angle angleType)
	{
		m_Fov = (angleType == Angle::Degrees) ? ToRadians(fov) : fov;
		UpdateProjectionMatrix();
	}

	void Camera::SetProjectionType(Projection projection)
	{
		m_ProjectionType = projection;
		UpdateProjectionMatrix();
	}

	void Camera::UpdateProjectionMatrix()
	{
		CreateProjectionMatrix();
	}

	String Camera::ToString() const
	{
		return "Camera";
	}

	void Camera::CreateProjectionMatrix()
	{
		if (m_ProjectionType == Projection::Perspective)
		{
			m_Projection = Maths::Mat4::Perspective(m_Fov, Graphics::CurrentContext()->GetAspect(), m_NearPlane, m_FarPlane);
		}
		else
		{
			m_Projection = Maths::Mat4::Orthographic(0, Graphics::CurrentContext()->GetWidth(), 0, Graphics::CurrentContext()->GetHeight(), m_NearPlane, m_FarPlane);
		}
	}

}