#include "GameManager.h"
#include "Components\Animators\__Animators__.h"
#include "Components\Card.h"
#include "Components\PlayField.h"

namespace Presidents
{

	GameManager::GameManager() : Object(),
		m_CurrentPlayer(-1)
	{
		
	}

	void GameManager::Initialise()
	{
		m_Mouse = AddToScene(GameObject::Instantiate("Mouse", 0, 0, 0))
			->AddComponent(new Hand(PI / 360.0f))
			->AddComponent<AttachToMouse>();
		m_HeldCards = &m_Mouse->GetComponent<Hand>();
	}

	std::vector<GameObject*> GameManager::HeldCards() const
	{
		return m_HeldCards->Cards();
	}

	const std::vector<Player>& GameManager::Players() const
	{
		return m_Players;
	}

	const Player* GameManager::CurrentPlayer() const
	{
		return &m_Players[m_CurrentPlayer];
	}

	int GameManager::CardCount() const
	{
		return m_HeldCards->CardCount();
	}

	bool GameManager::ContainsCard(GameObject* card) const
	{
		return m_HeldCards->ContainsCard(card);
	}

	bool GameManager::IsThisTurn(Hand* hand) const
	{
		return &m_Players[m_CurrentPlayer].Object->GetComponent<Hand>() == hand;
	}

	void GameManager::AddPlayer(PlayerType type)
	{
		float screenWidth = tan(PI / 3.0) * 10 / 2.0f;
		float screenHeight = screenWidth / Graphics::CurrentContext().Aspect();

		GameObject* playersHand = AddToScene(GameObject::Instantiate("Hand", 0, 0, 0))
			->AddComponent(new Hand(PI / 360.0f));
		if (type == PlayerType::Computer)
		{
			playersHand->transform().LocalScale() = Vector3f(0.5f);
		}
		GameObject* anchor = AddToScene(GameObject::Instantiate("Anchor", 0, 0, 0));
		playersHand->MakeChildOf(anchor);
		m_Players.push_back({ playersHand, type, anchor });

		int playerCount = m_Players.size();
		float angle = 2 * PI / playerCount;
		for (int i = 0; i < playerCount; i++)
		{
			float width = screenWidth + ((m_Players[i].Type == PlayerType::Computer) ? 2 : 0);
			float height = screenHeight + ((m_Players[i].Type == PlayerType::Computer) ? 1 : 0);
			float angleAround = i * angle;
			m_Players[i].Anchor->transform().LocalRotation() = Quaternion::FromAngleAxis(angleAround, Vector3f::Forward());
			float adjustedAngle = angleAround + PI / 2.0f;
			m_Players[i].Object->transform().LocalPosition().y = -sqrt(pow(width * cos(adjustedAngle), 2) + pow(height * sin(adjustedAngle), 2));
		}

	}

	void GameManager::Update()
	{  

	}

	void GameManager::SetCurrentPlayer(int index)
	{
		m_CurrentPlayer = index;
	}

	void GameManager::NextPlayer(bool played)
	{
		Player& currentPlayer = m_Players[m_CurrentPlayer];

		// If they played a card, update last played
		if (played)
		{
			m_LastPlayed = m_CurrentPlayer;
		}

		m_CurrentPlayer++;
		m_CurrentPlayer %= m_Players.size();
		Player& newPlayer = m_Players[m_CurrentPlayer];

		// Test if this player has already passed
		if (std::find(m_Passed.begin(), m_Passed.end(), m_CurrentPlayer) != m_Passed.end())
		{
			NextPlayer(false);
			return;
		}

		// Test if all other players have passed
		if (m_CurrentPlayer == m_LastPlayed)
		{
			NextRound();
			return;
		}

		// If the player is an AI, run the AI
		if (newPlayer.Type == PlayerType::Computer)
		{
			RunAITurn(newPlayer);
		}

	}

	void GameManager::Pass(Hand* hand)
	{
		for (int i = 0; i < m_Players.size(); i++)
		{
			if (&m_Players[i].Object->GetComponent<Hand>() == hand)
			{
				m_Passed.push_back(i);
			}
		}
		NextPlayer(false);
	}

	void GameManager::NextRound()
	{
		m_CurrentPlayer = m_LastPlayed;
		m_LastPlayed = -1;
		m_Passed.clear();
		PlayField& playField = GameObject::FindAllWith<PlayField>()[0]->GetComponent<PlayField>();
		playField.Clear();
		if (m_Players[m_CurrentPlayer].Type == PlayerType::Computer)
		{
			RunAITurn(m_Players[m_CurrentPlayer]);
		}
	}

	void GameManager::AddHeldCard(GameObject* card)
	{
		m_HeldCards->AddCard(card);
		card->RemoveComponent<BoxCollider>();
	}

	GameObject* GameManager::RemoveHeldCard(GameObject* card)
	{
		card->AddComponent(new BoxCollider(Vector3f(Card::WIDTH, Card::HEIGHT, 0)));
		m_HeldCards->RemoveCard(card);
		return card;
	}

	void GameManager::RemoveAllHeldCards()
	{
		for (int i = CardCount() - 1; i >= 0; i--)
		{
			GameObject* card = m_HeldCards->RemoveCard(i);
			card->AddComponent(new BoxCollider(Vector3f(Card::WIDTH, Card::HEIGHT, 0)));
		}
	}

	String GameManager::ToString() const
	{
		return "GameManager";
	}

	void GameManager::RunAITurn(Player p)
	{
		Hand& h = p.Object->GetComponent<Hand>();
		PlayField& playField = GameObject::FindAllWith<PlayField>()[0]->GetComponent<PlayField>();
		h.Order();
		for (int i = h.CardCount() - 1; i >= 0; i--)
		{
			if (playField.CanBeAdded({ h.Cards()[i] }))
			{
				GameObject* card = h.RemoveCard(i);
				playField.PushCards({ card });
				NextPlayer();
				return;
			}
		}
		Pass(&p.Object->GetComponent<Hand>());
	}

}