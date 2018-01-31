#include "PlayField.h"
#include "Animators\__Animators__.h"

namespace Presidents
{

	PlayField::PlayField(RankRules rules) : Component(),
		m_Rules(rules)
	{
	
	}

	const std::vector<GameObject*>& PlayField::TopCards() const
	{
		return m_TopCards;
	}

	std::vector<Card*> PlayField::TopCardComponents() const
	{
		std::vector<Card*> result;
		for (GameObject* c : TopCards())
		{
			result.push_back(&c->GetComponent<Card>());
		}
		return result;
	}

	Card* PlayField::TopCardComponent() const
	{
		return &m_TopCards[0]->GetComponent<Card>();
	}

	CardRank PlayField::TopCardRank() const
	{
		return TopCardComponent()->Rank();
	}

	bool PlayField::CanBeAdded(const std::vector<GameObject*>& cards) const
	{
		if (m_TopCards.size() == 0)
		{
			return true;
		}
		if (cards.size() == 0 || cards.size() != m_TopCards.size())
		{
			return false;
		}
		Card& c = cards[0]->GetComponent<Card>();
		if (m_Rules == RankRules::GEqualThan)
		{
			return c.Rank() >= TopCardRank();
		}
		return c.Rank() > TopCardRank();
	}

	void PlayField::PushCards(const std::vector<GameObject*>& cards)
	{
		for (GameObject* card : m_TopCards)
		{
			card->Destroy();
		}
		int size = cards.size();
		int index = 0;
		for (GameObject* card : cards)
		{
			if (card->HasComponent<MoveToLocation>())
			{
				card->RemoveComponent<MoveToLocation>();
			}
			if (card->HasComponent<BoxCollider>())
			{
				card->RemoveComponent<BoxCollider>();
			}
			card->MakeStandalone();
			card->transform().LocalPosition() = Vector3f((index - size / 2.0f + 0.5f) * 0.5f, 0, index * 0.1f);
			index++;
		}
		m_TopCards = cards;
	}

	void PlayField::Clear()
	{
		PushCards({  });
	}

	String PlayField::ToString() const
	{
		return "PlayField";
	}

	Component* PlayField::Clone() const
	{
		return new PlayField(m_Rules);
	}

}