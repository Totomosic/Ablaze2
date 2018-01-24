#include "Deck.h"

namespace Presidents
{

	Deck::Deck() : Component()
	{
	
	}

	Deck::~Deck()
	{
	
	}

	void Deck::Start()
	{
		Reset();
		Shuffle();
	}

	int Deck::CardCount() const
	{
		return m_Cards.size();
	}

	Card* Deck::TakeTop()
	{
		Card* top = m_Cards.front();
		m_Cards.pop_front();
		return top;
	}

	Card* Deck::PeekTop()
	{
		return m_Cards.front();
	}

	void Deck::AddToTop(Card* card)
	{
		AddAtPosition(card, 0);
	}

	void Deck::AddToBottom(Card* card)
	{
		AddAtPosition(card, m_Cards.size() - 1);
	}

	void Deck::AddAtPosition(Card* card, int position)
	{
		m_Cards.insert(m_Cards.begin() + position, card);
	}

	void Deck::Shuffle()
	{
		std::random_device rd;
		std::mt19937 g(rd());

		std::shuffle(m_Cards.begin(), m_Cards.end(), g);
	}

	void Deck::Reset()
	{
		while (CardCount() > 0)
		{
			TakeTop();
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				Card* card = new Card((CardSuit)i, (CardRank)j);
				AddToTop(card);
			}
		}
		Card* j0 = new Card(CardSuit::Clubs, CardRank::Joker);
		Card* j1 = new Card(CardSuit::Hearts, CardRank::Joker);
		AddToTop(j0);
		AddToTop(j1);
	}

	String Deck::ToString() const
	{
		return "Deck";
	}

	Component* Deck::Clone() const
	{
		Deck* deck = new Deck;
		return deck;
	}

}