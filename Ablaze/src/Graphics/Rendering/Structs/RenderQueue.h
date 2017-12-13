#pragma once
#include "Common.h"
#include "Scene\GameObject.h"

namespace Ablaze
{

	enum class RenderOrder
	{
		None,
		BackToFront,
		FrontToBack,
		StateChanges // Minimise textures/shader changes
	};

	class AB_API RenderQueue : public Object
	{
	private:
		std::deque<GameObject*> m_Queue;

	public:
		RenderQueue();

		void Enqueue(GameObject* object);
		GameObject* Next();
		void Clear();

		String ToString() const override;

	};

}