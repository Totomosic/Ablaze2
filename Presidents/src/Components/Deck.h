#pragma once
#include "AblazeInclude.h"
#include "Card.h"
#include "Hand.h"

namespace Presidents
{

	class Deck : public Component
	{
	private:
		std::deque<Card*> m_Cards;
		int m_DeckCount;

	public:
		Deck(int deckCount = 1);
		~Deck() override;

		void Start() override;

		int CardCount() const;
		
		Card* TakeTop();
		Card* PeekTop();

		void AddToTop(Card* card);
		void AddToBottom(Card* card);
		void AddAtPosition(Card* card, int position);
		
		void Shuffle();
		void Reset();
		void DealTo(const std::vector<Hand*>& hands, int cps, int maxCards = 10000);

		String ToString() const override;
		Component* Clone() const override;

	private:
		GameObject* CreateCard(Card* card);

	};

}