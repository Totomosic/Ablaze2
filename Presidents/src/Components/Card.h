#pragma once
#include "AblazeInclude.h"

namespace Presidents
{

	enum class CardSuit
	{
		Hearts,
		Diamonds,
		Spades,
		Clubs
	};

	enum class CardRank
	{
		Three,
		Four,
		Five,
		Six,
		Seven,
		Eight,
		Nine,
		Ten,
		Jack,
		Queen,
		King,
		Ace,
		Two,
		Joker
	};

	class Card : public Component
	{
	public:
		static const int WIDTH = 500 / 4;
		static const int HEIGHT = 726 / 4;

	private:
		CardSuit m_Suit;
		CardRank m_Rank;

	public:
		Card(CardSuit suit, CardRank rank);

		CardSuit Suit() const;
		CardRank Rank() const;
		bool IsTrump() const;
		bool IsFace() const;
		bool IsNumber() const;
		bool IsRed() const;
		bool IsBlack() const;

		Texture2D* GetTexture() const;

		String ToString() const override;
		Component* Clone() const override;

	};

}