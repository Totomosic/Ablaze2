#include "Hand.h"
#include "Card.h"
#include "Animators\__Animators__.h"

namespace Presidents
{

	Hand::Hand(float fanAngle) : Component(),
		m_FanAngle(fanAngle), m_IsOpen(false), m_Placeholder(nullptr), m_OpenIndex(-1)
	{
	
	}

	int Hand::CardCount() const
	{
		return m_Cards.size();
	}

	GameObject* Hand::GetCard(int index) const
	{
		return m_Cards[index].Card;
	}

	GameObject* Hand::GetCardHolder(int index) const
	{
		return m_Cards[index].CardHolder;
	}

	bool Hand::IsOpen() const
	{
		return m_IsOpen;
	}

	int Hand::OpenIndex() const
	{
		return m_OpenIndex;
	}

	std::vector<GameObject*> Hand::Cards() const
	{
		std::vector<GameObject*> result;
		for (CardContainer c : m_Cards)
		{
			result.push_back(c.Card);
		}
		return result;
	}

	bool Hand::ContainsCard(GameObject* card) const
	{
		for (const CardContainer& c : m_Cards)
		{
			if (c.Card == card)
			{
				return true;
			}
		}
		return false;
	}

	GameObject* Hand::RemoveCard(int index)
	{
		GameObject* card = GetCard(index);
		card->MakeStandalone();
		card->transform().Reset();
		GameObject* holder = m_Cards[index].CardHolder;
		m_Cards.erase(m_Cards.begin() + index);		
		holder->Destroy();
		UpdateHand();
		return card;
	}

	GameObject* Hand::RemoveCard(GameObject* card)
	{
		for (int i = 0; i < m_Cards.size(); i++)
		{
			if (m_Cards[i].Card == card)
			{
				RemoveCard(i);
			}
		}
		return card;
	}

	void Hand::AddCard(GameObject* card, int position, float height)
	{
		if (m_IsOpen)
		{
			CloseAt();
		}
		int index = m_Cards.size();
		GameObject* holder = AddToScene(GameObject::Instantiate("CardHolder", 0, -100, 0));
		card->MakeChildOf(holder);
		card->transform().LocalPosition() = Vector3f(0, 100 + height, 0);

		if (height > 0)
		{
			card->AddComponent(new MoveToLocation(Vector3f(0, 100, 0), 0.1f));
		}

		holder->MakeChildOf(m_GameObject);
		m_Cards.insert(m_Cards.begin() + position, { card, holder });

		float offset = (position - CardCount() / 2.0f + 0.5f);
		float angle = m_FanAngle * offset;
		holder->transform().LocalRotation() = Quaternion::FromAngleAxis(angle, Vector3f::Forward());

		UpdateHand();
	}

	void Hand::AddCard(GameObject* card, float height)
	{
		AddCard(card, m_Cards.size(), height);
	}

	void Hand::HighlightCard(GameObject* card, float amount) const
	{
		if (card->transform().LocalPosition() != Vector3f(0, 100 + amount, card->transform().LocalPosition().z))
		{
			card->AddComponent(new MoveToLocation(Vector3f(0, 100 + amount, 0), 0.02f));
			card->GetComponent<BoxCollider>().Box().SetSize(Vector3f(Card::WIDTH, Card::HEIGHT + amount * 2, 0));
		}
	}

	void Hand::HighlightCard(int index, float amount) const
	{
		GameObject* card = m_Cards[index].Card;
		HighlightCard(card, amount);
	}

	void Hand::DehighlightCard(GameObject* card) const
	{
		if (card->transform().LocalPosition() != Vector3f(card->transform().LocalPosition().x, 100, card->transform().LocalPosition().z))
		{
			card->AddComponent(new MoveToLocation(Vector3f(0, 100, 0), 0.02f));
			card->GetComponent<BoxCollider>().Box().SetSize(Vector3f(Card::WIDTH, Card::HEIGHT, 0));
		}
	}

	void Hand::DehighlightCard(int index) const
	{
		GameObject* card = m_Cards[index].Card;
		DehighlightCard(card);
	}

	void Hand::DehighlightAll() const
	{
		for (const CardContainer& card : m_Cards)
		{
			DehighlightCard(card.Card);
		}
	}

	void Hand::Order()
	{
		if (!IsOpen())
		{
			std::sort(m_Cards.begin(), m_Cards.end(), [](const CardContainer& c0, const CardContainer& c1) -> bool
			{
				return ((int)c0.Card->GetComponent<Card>().Rank() > (int)c1.Card->GetComponent<Card>().Rank());
			});
			UpdateHand();
		}
	}

	void Hand::OpenAt(int position)
	{
		AB_ASSERT(!m_IsOpen, "Hand was already opened");
		m_Placeholder = GameObject::Instantiate("Placeholder");
		AddCard(m_Placeholder, position);
		m_IsOpen = true;
		m_OpenIndex = position;
		UpdateHand();
	}

	void Hand::CloseAt()
	{
		AB_ASSERT(m_IsOpen, "Hand was not opened");
		RemoveCard(m_Placeholder);
		m_Placeholder->Destroy();
		m_Placeholder = nullptr;
		m_IsOpen = false;
		m_OpenIndex = -1;
		UpdateHand();
	}

	void Hand::ClearAll()
	{
		for (int i = CardCount() - 1; i >= 0; i--)
		{
			CardContainer& c = m_Cards[i];
			c.Card->MakeStandalone();
			c.CardHolder->MakeStandalone();
			c.Card->Destroy();
			c.CardHolder->Destroy();
		}
		m_Cards.clear();
		if (m_GameObject->HasComponent<Dealer>())
		{
			m_GameObject->GetComponent<Dealer>().DestroyAll();
		}
	}

	int Hand::CalcIndex(float xOffset) const
	{
		float perCardOffset = tan(m_FanAngle) * 100;
		float cardSize = Card::WIDTH;
		int cardCount = CardCount();
		if (m_IsOpen)
		{
			cardCount -= 1;
		}
		float handSize = cardSize + (cardCount - 1) * perCardOffset;
		return Clamp(Map(xOffset, -handSize / 2.0f, handSize / 2.0f, 0, cardCount) + 1, 0, cardCount);
	}

	String Hand::ToString() const
	{
		return "Hand";
	}

	Component* Hand::Clone() const
	{
		Hand* h = new Hand(m_FanAngle);
		for (const CardContainer& card : m_Cards)
		{
			h->AddCard(GameObject::Instantiate("Card", card.Card));
		}
		return h;
	}

	void Hand::UpdateHand()
	{
		int cardCount = CardCount();
		for (int i = 0; i < cardCount; i++)
		{
			float offset = (i - cardCount / 2.0f + 0.5f);
			float angle = m_FanAngle * offset;
			GameObject* cardHolder = m_Cards[i].CardHolder;
			cardHolder->AddComponent(new RotateTo(Quaternion::FromAngleAxis(angle, Vector3f::Forward()), 0.1f));
			GameObject* card = m_Cards[i].Card;
			cardHolder->transform().LocalPosition().z = 0.02f * i;
		}
	}

}