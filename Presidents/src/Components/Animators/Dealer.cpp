#include "Dealer.h"
#include "../Hand.h"

namespace Presidents
{

	Dealer::Dealer(int cps) : Component(),
		m_Cps(cps), m_CurrentTime(0.0f)
	{
	
	}

	void Dealer::AddCard(GameObject* card)
	{
		m_Cards.push_back(card);
	}

	void Dealer::Update(double elapsedSeconds)
	{
		if (m_Cards.size() > 0)
		{
			float time = 1.0f / m_Cps;
			m_CurrentTime += (float)elapsedSeconds;
			if (m_CurrentTime >= time)
			{
				m_GameObject->GetComponent<Hand>().AddCard(m_Cards.front(), 4.0f);
				m_Cards.erase(m_Cards.begin());
				m_CurrentTime = 0.0f;
			}
		}
		else
		{
			m_GameObject->Components().RemoveComponent(this);
		}
	}

	void Dealer::DestroyAll()
	{
		for (GameObject* card : m_Cards)
		{
			card->Destroy();
		}
		m_Cards.clear();
	}

	String Dealer::ToString() const
	{
		return "Dealer";
	}

	Component* Dealer::Clone() const
	{
		Dealer* d = new Dealer(m_Cps);
		for (GameObject* card : m_Cards)
		{
			d->AddCard(card);
		}
		return d;
	}

}