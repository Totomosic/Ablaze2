#pragma once
#include "Scene\Components\Component.h"
#include "Scene\Physics\__Physics__.h"

namespace Ablaze
{

	class AB_API BoxCollider : public Component
	{
	private:
		OBB m_BoundingBox;

	public:
		BoxCollider(const OBB& boundingBox);

		const OBB& Box() const;
		OBB& Box();

		Component* Clone() const override;
		String ToString() const override;

	};

}