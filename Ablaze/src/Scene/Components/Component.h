#pragma once
#include "Common.h"
#include "Scene\GameObject.h"

namespace Ablaze
{

	class AB_API Component : public Object
	{
	protected:
		GameObject* m_GameObject;

	public:
		Component();
		virtual ~Component();

		GameObject* Owner() const;

		virtual void Start();
		virtual void Update(double elapsedSeconds);

		virtual Component* Clone() const = 0;

		friend class ComponentSet;

	};

}