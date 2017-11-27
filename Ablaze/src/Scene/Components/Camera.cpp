#include "Camera.h"
#include "Graphics\Rendering\Graphics.h"

namespace Ablaze
{

	Camera::Camera(Projection projection, float fov, float nearPlane, float farPlane) : Component(),
		m_ProjectionType(projection), m_Fov(fov), m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
		if (Graphics::IsInitialised())
		{
			CreateProjectionMatrix(0, Graphics::CurrentContext()->Width(), 0, Graphics::CurrentContext()->Height());
		}
	}

	Camera::Camera(float x, float xMax, float y, float yMax, float nearPlane, float farPlane) : Component(),
		m_ProjectionType(Projection::Orthographic), m_Fov(Maths::PI / 3), m_NearPlane(nearPlane), m_FarPlane(farPlane)
	{
		CreateProjectionMatrix(x, xMax, y, yMax);
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
		CreateProjectionMatrix(0, Graphics::CurrentContext()->Width(), 0, Graphics::CurrentContext()->Height());
	}

	String Camera::ToString() const
	{
		return "Camera";
	}

	void Camera::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.WriteAttribute("FOV", m_Fov);
		writer.WriteAttribute("Projection", (int)m_ProjectionType);
		writer.WriteAttribute("NearPlane", m_NearPlane);
		writer.WriteAttribute("FarPlane", m_FarPlane);
		writer.WriteObject("ProjectionMatrix", m_Projection);
		writer.EndObject();
	}

	Component* Camera::Clone() const
	{
		Camera* camera = new Camera(m_ProjectionType, m_Fov, m_NearPlane, m_FarPlane);
		return camera;
	}

	void Camera::CreateProjectionMatrix(float x, float width, float y, float height)
	{
		if (m_ProjectionType == Projection::Perspective)
		{
			m_Projection = Maths::Mat4::Perspective(m_Fov, Graphics::CurrentContext()->Aspect(), m_NearPlane, m_FarPlane);
		}
		else
		{
			m_Projection = Maths::Mat4::Orthographic(x, width, y, height, m_NearPlane, m_FarPlane);
		}
	}

}