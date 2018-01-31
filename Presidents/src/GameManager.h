#pragma once
#include "AblazeInclude.h"
#include "Components\Hand.h"

namespace Presidents
{

	enum class PlayerType
	{
		Human,
		Computer
	};

	struct Player
	{
	public:
		GameObject* Object;
		PlayerType Type;
		GameObject* Anchor;
	};

	class GameManager : public Object
	{
	private:
		GameObject* m_Mouse;
		Hand* m_HeldCards;
		std::vector<Player> m_Players;
		std::vector<int> m_Passed;
		int m_CurrentPlayer;
		int m_LastPlayed;

	public:
		GameManager();

		void Initialise();

		std::vector<GameObject*> HeldCards() const;
		int CardCount() const;
		const std::vector<Player>& Players() const;
		const Player* CurrentPlayer() const;
		bool ContainsCard(GameObject* card) const;
		bool IsThisTurn(Hand* hand) const;

		void AddPlayer(PlayerType type);

		void SetCurrentPlayer(int index);
		void NextPlayer(bool played = true);
		void Pass(Hand* hand);

		void NextRound();

		void Update();
		void AddHeldCard(GameObject* card);
		GameObject* RemoveHeldCard(GameObject* card);
		void RemoveAllHeldCards();

		String ToString() const override;

	private:
		void RunAITurn(Player p);

	};

}