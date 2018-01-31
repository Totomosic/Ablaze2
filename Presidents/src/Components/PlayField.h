#pragma once
#include "AblazeInclude.h"
#include "Card.h"

namespace Presidents
{

	enum class RankRules
	{
		GreaterThan,
		GEqualThan
	};

	class PlayField : public Component
	{
	private:
		RankRules m_Rules;
		std::vector<GameObject*> m_TopCards;

	public:
		PlayField(RankRules rules);

		const std::vector<GameObject*>& TopCards() const;
		std::vector<Card*> TopCardComponents() const;
		Card* TopCardComponent() const;
		CardRank TopCardRank() const;

		bool CanBeAdded(const std::vector<GameObject*>& cards) const;
		void PushCards(const std::vector<GameObject*>& cards);

		void Clear();

		String ToString() const override;
		Component* Clone() const override;

	};

}