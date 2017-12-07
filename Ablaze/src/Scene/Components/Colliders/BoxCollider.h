#pragma once
#include "Scene\Components\Component.h"
#include "Scene\Components\Motion\Transform.h"
#include "Endpoint.h"

namespace Ablaze
{

	class AB_API BoxCollider : public Component
	{
	private:
		Maths::Vector3f m_Size;
		Transform m_Transform;

	public:
		BoxCollider(const Maths::Vector3f& size, const Transform& transform);
		BoxCollider(const Maths::Vector3f& size);
		BoxCollider();

		const Maths::Vector3f& Size() const;
		Maths::Vector3f& Size();
		const Transform& transform() const;
		Transform& transform();

		Maths::Vector3f Max() const;
		Maths::Vector3f Min() const;
		Endpoint* Endpoints();

		String ToString() const override;
		Component* Clone() const override;
		void Serialize(JSONwriter& writer);

	};

}