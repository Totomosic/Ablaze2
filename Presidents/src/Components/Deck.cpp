#include "Deck.h"
#include "Card.h"
#include "Animators\Dealer.h"

namespace Presidents
{

	Deck::Deck(int deckCount) : Component(),
		m_DeckCount(deckCount)
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
		for (int i = 0; i < m_DeckCount; i++)
		{
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
	}

	void Deck::DealTo(const std::vector<Hand*>& hands, int cps, int maxCards)
	{
		std::vector<Dealer*> dealers;
		for (int i = 0; i < hands.size(); i++)
		{
			dealers.push_back(new Dealer(cps));
			hands[i]->Owner()->AddComponent(dealers[i]);
		}
		int cardCount = 0;
		while (cardCount < maxCards && CardCount() > 0)
		{
			for (int i = 0; i < hands.size(); i++)
			{
				dealers[i]->AddCard(CreateCard(TakeTop()));
			}
			cardCount++;
		}
	}

	String Deck::ToString() const
	{
		return "Deck";
	}

	Component* Deck::Clone() const
	{
		Deck* deck = new Deck(m_DeckCount);
		return deck;
	}

	GameObject* Deck::CreateCard(Card* card)
	{
		Texture2D* texture = card->GetTexture();
		GameObject* newCard = AddToScene(GameObject::Instantiate("PlayingCard", -10000, 0, 0))
			->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Square(), Material(Color::White(), ResourceManager::DefaultTextureShader(), "Tex0", texture)), Matrix4f::Scale(Card::WIDTH, Card::HEIGHT, 1)))
			->AddComponent(card)
			->AddComponent(new BoxCollider(Vector3f(Card::WIDTH, Card::HEIGHT, 0)));
		return newCard;
	}

}