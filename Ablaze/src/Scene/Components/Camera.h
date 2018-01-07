#pragma once
#include "Common.h"
#include "Motion\Transform.h"

namespace Ablaze
{

	enum class Projection
	{
		Perspective,
		Orthographic
	};

	class AB_API Camera : public Component
	{
		typedef Maths::Matrix4f(*TransformFunc)(const Maths::Matrix4f&);

	private:
		Projection m_ProjectionType;
		float m_NearPlane;
		float m_FarPlane;
		Maths::Matrix4f m_Projection;

		TransformFunc m_TransformFunc;

	public:
		Camera(Projection type, const Maths::Matrix4f& projectionMatrix, float nearPlane, float farPlane);
		Camera(Projection type);
		Camera();

		const Maths::Matrix4f& ProjectionMatrix() const;
		Maths::Matrix4f& ProjectionMatrix();
		const Maths::Matrix4f ViewMatrix() const;
		float NearPlane() const;
		float FarPlane() const;
		Projection ProjectionType() const;

		Maths::Vector3f ScreenToWorldPoint(const Maths::Vector3f& screenpoint) const;
		Maths::Vector3f WorldToScreenPoint(const Maths::Vector3f& worldpoint) const;
		Maths::Ray ScreenToWorldRay(const Maths::Vector3f& screenPoint) const;

		void SetProjectionMatrix(const Maths::Matrix4f& projection);
		void SetTransformFunc(TransformFunc func);

		String ToString() const override;
		Component* Clone() const override;
		void Serialize(JSONwriter& writer) const override;

	public:
		static Camera* Perspective(float fov, float aspect, float nearPlane = 1.0f, float farPlane = 1000.0f);
		static Camera* Orthographic(float left, float right, float bottom, float top, float nearPlane = 1.0f, float farPlane = 1000.0f);
		static Camera* Orthographic(float width, float height, float nearPlane = 1.0f, float farPlane = 1000.0f);

		static Maths::Matrix4f DefaultTransform(const Maths::Matrix4f& in);

	};

}