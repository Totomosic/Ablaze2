#pragma once
#include "AblazeInclude.h"

namespace Presidents
{

	struct AB_API CardContainer
	{
		GameObject* Card;
		GameObject* CardHolder;
	};

	class Hand : public Component
	{
	private:
		std::vector<CardContainer> m_Cards;
		float m_FanAngle;

		bool m_IsOpen;
		int m_OpenIndex;
		GameObject* m_Placeholder;

	public:
		Hand(float fanAngle = PI / 180.0f);

		int CardCount() const;
		GameObject* GetCard(int index) const;
		GameObject* GetCardHolder(int index) const;
		bool IsOpen() const;
		int OpenIndex() const;
		std::vector<GameObject*> Cards() const;

		bool ContainsCard(GameObject* card) const;

		GameObject* RemoveCard(int index);
		GameObject* RemoveCard(GameObject* card);
		void AddCard(GameObject* card, int position, float height = 0.0f);
		void AddCard(GameObject* card, float height = 0.0f);

		void HighlightCard(int index, float amount) const;
		void HighlightCard(GameObject* card, float amount) const;
		void DehighlightCard(int index) const;
		void DehighlightCard(GameObject* card) const;
		void DehighlightAll() const;

		void Order();

		void OpenAt(int position);
		void CloseAt();

		void ClearAll();

		int CalcIndex(float xOffset) const;

		String ToString() const override;
		Component* Clone() const override;

	private:
		void UpdateHand();

	};

}