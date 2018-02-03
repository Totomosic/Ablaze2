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
		RenderOrder m_Order;
		std::deque<GameObject*> m_Queue;

	public:
		RenderQueue(RenderOrder order = RenderOrder::None);

		int Size() const;

		void Enqueue(GameObject* object);
		void Sort();
		GameObject* Next();
		void Clear();

		String ToString() const override;

	private:
		static bool FToBSort(GameObject* left, GameObject* right);

	};

}