#include "Camera.h"
#include "Graphics\Rendering\Graphics.h"

namespace Ablaze
{

	Camera::Camera(Projection type, const Maths::Matrix4f& projectionMatrix, float nearPlane, float farPlane) : Component(),
		m_ProjectionType(type), m_Projection(projectionMatrix), m_NearPlane(nearPlane), m_FarPlane(farPlane), m_TransformFunc(Camera::DefaultTransform)
	{
		
	}

	Camera::Camera(Projection type) : Camera(type, Maths::Matrix4f::Identity(), 1.0f, 1000.0f)
	{
		if (type == Projection::Perspective)
		{
			m_Projection = Maths::Matrix4f::Perspective(Maths::PI / 3.0, Graphics::CurrentContext().Aspect(), 1.0f, 1000.0f);
		}
		else
		{
			m_Projection = Maths::Matrix4f::Orthographic(0, Graphics::CurrentContext().Width(), 0, Graphics::CurrentContext().Height(), 1.0f, 1000.0);
		}
	}

	Camera::Camera() : Camera(Projection::Perspective, Maths::Matrix4f::Perspective(Maths::PI / 3.0, Graphics::CurrentContext().Aspect(), 1.0f, 1000.0f), 1.0f, 1000.0f)
	{
	
	}

	const Maths::Matrix4f& Camera::ProjectionMatrix() const
	{
		return m_Projection;
	}

	Maths::Matrix4f& Camera::ProjectionMatrix()
	{
		return m_Projection;
	}

	const Maths::Matrix4f Camera::ViewMatrix() const
	{
		return m_TransformFunc(m_GameObject->transform().ToMatrix()).Inverse();
	}

	float Camera::NearPlane() const
	{
		return m_NearPlane;
	}

	float Camera::FarPlane() const
	{
		return m_FarPlane;
	}

	Projection Camera::ProjectionType() const
	{
		return m_ProjectionType;
	}

	Maths::Vector3f Camera::ScreenToWorldPoint(const Maths::Vector3f& screenPoint) const
	{
		Maths::Vector4f ndc;
		ndc.x = Map(screenPoint.x, 0, Graphics::CurrentContext().Width(), -1.0f, 1.0f);
		ndc.y = Map(screenPoint.y, 0, Graphics::CurrentContext().Height(), -1.0f, 1.0f);
		ndc.z = 1.0f;
		ndc.w = 1.0f;
		Maths::Vector4f viewPoint = ProjectionMatrix().Inverse() * ndc;
		Maths::Vector4f worldPoint = ViewMatrix().Inverse() * viewPoint;
		return m_GameObject->transform().Position() + worldPoint.xyz() * screenPoint.z;
	}

	Maths::Ray Camera::ScreenToWorldRay(const Maths::Vector3f& screenPoint) const
	{
		Maths::Vector3f origin = m_GameObject->transform().Position();
		Maths::Vector4f ndc;
		ndc.x = (2.0f * (screenPoint.x - Graphics::CurrentContext().Width() / 2.0f)) / Graphics::CurrentContext().Width();
		ndc.y = (2.0f * (screenPoint.y - Graphics::CurrentContext().Height() / 2.0f)) / Graphics::CurrentContext().Height();
		ndc.z = -1.0f;
		ndc.w = 1.0f;
		Maths::Vector4f viewPoint = ProjectionMatrix().Inverse() * ndc;
		Maths::Vector4f direction = ViewMatrix().Inverse() * viewPoint;
		direction.z *= -1;
		return Maths::Ray(origin, direction.xyz());
	}

	void Camera::SetProjectionMatrix(const Maths::Matrix4f& projection)
	{
		m_Projection = projection;
	}

	void Camera::SetTransformFunc(TransformFunc func)
	{
		m_TransformFunc = func;
	}

	String Camera::ToString() const
	{
		return "Camera";
	}

	void Camera::Serialize(JSONwriter& writer) const
	{
		writer.BeginObject();
		writer.WriteAttribute("Projection", (int)m_ProjectionType);
		writer.WriteAttribute("NearPlane", m_NearPlane);
		writer.WriteAttribute("FarPlane", m_FarPlane);
		writer.WriteObject("ProjectionMatrix", m_Projection);
		writer.EndObject();
	}

	Component* Camera::Clone() const
	{
		Camera* camera = new Camera(m_ProjectionType, m_Projection, m_NearPlane, m_FarPlane);
		return camera;
	}

	Camera* Camera::Perspective(float fov, float aspect, float nearPlane, float farPlane)
	{
		Maths::Matrix4f projection = Maths::Matrix4f::Perspective(fov, aspect, nearPlane, farPlane);
		return new Camera(Projection::Perspective, projection, nearPlane, farPlane);
	}

	Camera* Camera::Orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane)
	{
		Maths::Matrix4f projection = Maths::Matrix4f::Orthographic(left, right, bottom, top, nearPlane, farPlane);
		return new Camera(Projection::Orthographic, projection, nearPlane, farPlane);
	}

	Camera* Camera::Orthographic(float width, float height, float nearPlane, float farPlane)
	{
		return Orthographic(0, width, 0, height, nearPlane, farPlane);
	}

	Maths::Matrix4f Camera::DefaultTransform(const Maths::Matrix4f& in)
	{
		return in;
	}

}