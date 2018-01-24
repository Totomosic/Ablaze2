#pragma once
#include "AblazeInclude.h"
#include "Card.h"

namespace Presidents
{

	class Deck : public Component
	{
	private:
		std::deque<Card*> m_Cards;

	public:
		Deck();
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

		String ToString() const override;
		Component* Clone() const override;

	};

}