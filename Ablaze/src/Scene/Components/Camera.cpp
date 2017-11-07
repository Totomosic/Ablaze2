#include "Camera.h"
#include "Graphics\Graphics.h"

namespace Ablaze
{

	Camera::Camera(Projection projection, float fov, float nearPlane, float farPlane) : Component(),
		m_ProjectionType(projection), m_Fov(fov), m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
		CreateProjectionMatrix();
	}

	const Maths::Mat4& Camera::ProjectionMatrix() const
	{
		return m_Projection;
	}

	Maths::Mat4& Camera::ProjectionMatrix()
	{
		return m_Projection;
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

	Component* Camera::Clone() const
	{
		Camera* camera = new Camera(m_ProjectionType, m_Fov, m_NearPlane, m_FarPlane);
		return camera;
	}

	void Camera::CreateProjectionMatrix()
	{
		if (m_ProjectionType == Projection::Perspective)
		{
			m_Projection = Maths::Mat4::Perspective(m_Fov, Graphics::CurrentContext()->Aspect(), m_NearPlane, m_FarPlane);
		}
		else
		{
			m_Projection = Maths::Mat4::Orthographic(0, Graphics::CurrentContext()->Width(), 0, Graphics::CurrentContext()->Height(), m_NearPlane, m_FarPlane);
		}
	}

}