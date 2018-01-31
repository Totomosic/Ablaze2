#include "Card.h"

namespace Presidents
{

	const float Card::WIDTH = 500.0f / 250.0f;
	const float Card::HEIGHT = 726.0f / 250.0f;

	Card::Card(CardSuit suit, CardRank rank) : Component(),
		m_Suit(suit), m_Rank(rank)
	{
	
	}

	CardSuit Card::Suit() const
	{
		return m_Suit;
	}

	CardRank Card::Rank() const
	{
		return m_Rank;
	}

	bool Card::IsTrump() const
	{
		return m_Rank == CardRank::Two || m_Rank == CardRank::Joker;
	}

	bool Card::IsFace() const
	{
		return m_Rank == CardRank::Jack || m_Rank == CardRank::Queen || m_Rank == CardRank::King;
	}

	bool Card::IsNumber() const
	{
		return !IsFace() && m_Rank != CardRank::Joker;
	}

	bool Card::IsBlack() const
	{
		return m_Suit == CardSuit::Clubs || m_Suit == CardSuit::Spades;
	}

	bool Card::IsRed() const
	{
		return !IsBlack();
	}

	Texture2D* Card::GetTexture() const
	{
		String textureName = "";
		if (m_Rank == CardRank::Ace)
		{
			textureName += "ACE_";
		}
		else if (m_Rank == CardRank::Two)
		{
			textureName += "TWO_";
		}
		else if (m_Rank == CardRank::Three)
		{
			textureName += "THREE_";
		}
		else if (m_Rank == CardRank::Four)
		{
			textureName += "FOUR_";
		}
		else if (m_Rank == CardRank::Five)
		{
			textureName += "FIVE_";
		}
		else if (m_Rank == CardRank::Six)
		{
			textureName += "SIX_";
		}
		else if (m_Rank == CardRank::Seven)
		{
			textureName += "SEVEN_";
		}
		else if (m_Rank == CardRank::Eight)
		{
			textureName += "EIGHT_";
		}
		else if (m_Rank == CardRank::Nine)
		{
			textureName += "NINE_";
		}
		else if (m_Rank == CardRank::Ten)
		{
			textureName += "TEN_";
		}
		else if (m_Rank == CardRank::Jack)
		{
			textureName += "JACK_";
		}
		else if (m_Rank == CardRank::Queen)
		{
			textureName += "QUEEN_";
		}
		else if (m_Rank == CardRank::King)
		{
			textureName += "KING_";
		}
		else if (m_Rank == CardRank::Joker)
		{
			textureName += "JOKER_";
			if (IsBlack())
			{
				textureName += "BLACK";
			}
			else
			{
				textureName += "RED";
			}
		}

		if (m_Rank != CardRank::Joker)
		{
			if (m_Suit == CardSuit::Clubs)
			{
				textureName += "CLUBS";
			}
			else if (m_Suit == CardSuit::Spades)
			{
				textureName += "SPADES";
			}
			else if (m_Suit == CardSuit::Diamonds)
			{
				textureName += "DIAMONDS";
			}
			else if (m_Suit == CardSuit::Hearts)
			{
				textureName += "HEARTS";
			}
		}
		return GetTexture2D(textureName);
	}

	String Card::ToString() const
	{
		return "Card";
	}

	Component* Card::Clone() const
	{
		Card* c = new Card(m_Suit, m_Rank);
		return c;
	}

}