#pragma once
#include "Common.h"
#include "Scene\GameObject.h"
#include "Scene\ComponentSet.h"

namespace Ablaze
{

	class AB_API Component : public Object
	{
	protected:
		GameObject* m_GameObject;
		bool m_Enabled;

	public:
		Component();
		virtual ~Component();

		GameObject* Owner() const;
		const bool Enabled() const;
		bool& Enabled();

		void Enable();
		void Disable();

		virtual void Start();
		virtual void Update(double elapsedSeconds);
		virtual void LateUpdate(double elapsedSeconds);

		virtual Component* Clone() const = 0;
		virtual void Serialize(JSONwriter& writer) const;

		friend class ComponentSet;

	};

}