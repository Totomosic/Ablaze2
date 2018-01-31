#pragma once
#include "AblazeInclude.h"

namespace Presidents
{

	class Dealer : public Component
	{
	private:
		std::vector<GameObject*> m_Cards;
		int m_Cps;

		float m_CurrentTime;

	public:
		Dealer(int cps);

		void AddCard(GameObject* card);

		void Update(double elapsedSeconds);
		void DestroyAll();

		String ToString() const override;
		Component* Clone() const override;

	};

}