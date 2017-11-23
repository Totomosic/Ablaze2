#pragma once
#include "Scene\Components\Component.h"
#include "Scene\Components\Motion\Transform.h"
#include "Endpoint.h"

namespace Ablaze
{

	class AB_API BoxCollider : public Component
	{
	private:
		Maths::Vec3 m_Size;
		Transform m_Transform;

	public:
		BoxCollider(const Maths::Vec3& size, const Transform& transform);
		BoxCollider(const Maths::Vec3& size);
		BoxCollider();

		const Maths::Vec3& Size() const;
		Maths::Vec3& Size();
		const Transform& transform() const;
		Transform& transform();

		Maths::Vec3 Max() const;
		Maths::Vec3 Min() const;
		Endpoint* Endpoints();

		String ToString() const override;
		Component* Clone() const override;
		void Serialize(JSONwriter& writer);

	};

}