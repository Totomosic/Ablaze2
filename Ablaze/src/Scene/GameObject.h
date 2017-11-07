#pragma once
#include "Common.h"

namespace Ablaze
{

	class Layer;
	class ComponentSet;

	// Base class for all Objects in the game
	class AB_API GameObject : public Object
	{
	protected:
		ComponentSet* m_Components;
		uint m_Id;
		Layer* m_Layer;

	protected:
		~GameObject();

	public:
		GameObject();

		const ComponentSet& Components() const;
		ComponentSet& Components();

		String ToString() const override;

		friend class Layer;
		friend class Engine;

	};

}