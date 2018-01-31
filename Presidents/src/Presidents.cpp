#include "AblazeInclude.h"

#include "Components\__Components__.h"
#include "GameManager.h"

namespace Presidents
{

	class Game : public Application
	{
	public:
		GameManager Manager;

	public:
		void Init() override
		{
			Window* window = new Window(1280, 720, "Presidents", Color(10, 108, 3));
			Graphics::Initialise(window);

			LoadCardTextures();

			Scene& scene = SceneManager::Instance().CreateScene();
			Layer& gameBoard = scene.CreateLayer("GameBoard");
			scene.SetCurrentLayer(&gameBoard);

			Manager.Initialise();

			GameObject* cardMat = AddToScene(GameObject::Instantiate("CardMat", 0, 0, -5))
				->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Square(), Material(Color::White(), ResourceManager::DefaultTextureShader(), "Tex0", GetTexture2D("CARD_MAT"))), Matrix4f::Scale(8, 6, 1)))
				->AddComponent(new BoxCollider(Vector3f(8, 6, 0)))
				->AddComponent(new PlayField(RankRules::GreaterThan));

			GameObject* deck = AddToScene(GameObject::Instantiate("Deck", 0, 0, 0))
				->AddComponent(new Deck(1));

			Manager.AddPlayer(PlayerType::Human);
			Manager.AddPlayer(PlayerType::Computer);
			Manager.AddPlayer(PlayerType::Computer);
			Manager.AddPlayer(PlayerType::Computer);

			Manager.SetCurrentPlayer(0);

			GameObject* camera = AddToScene(GameObject::Instantiate("Camera", 0, 0, 10))
				->AddComponent(new Camera(Projection::Perspective));
			gameBoard.SetActiveCamera(camera);

			Reset();

			GraphicsPipeline g;
			g.Renderer = new ForwardRenderer;
			g.Schedule = new RenderSchedule;
			g.Schedule->AddRenderPass(new RenderPass("Default"));
			Graphics::AddGraphicsPipeline(g);
		}

		void LoadCardTextures()
		{
			SetTexture2D("CARD_BACK", new Texture2D("res/CardBack.jpg"));
			SetTexture2D("CARD_MAT", new Texture2D("res/BlackMat.png"));

			SetTexture2D("ACE_HEARTS", new Texture2D("res/Cards/ace_of_hearts.png"));
			SetTexture2D("TWO_HEARTS", new Texture2D("res/Cards/2_of_hearts.png"));
			SetTexture2D("THREE_HEARTS", new Texture2D("res/Cards/3_of_hearts.png"));
			SetTexture2D("FOUR_HEARTS", new Texture2D("res/Cards/4_of_hearts.png"));
			SetTexture2D("FIVE_HEARTS", new Texture2D("res/Cards/5_of_hearts.png"));
			SetTexture2D("SIX_HEARTS", new Texture2D("res/Cards/6_of_hearts.png"));
			SetTexture2D("SEVEN_HEARTS", new Texture2D("res/Cards/7_of_hearts.png"));
			SetTexture2D("EIGHT_HEARTS", new Texture2D("res/Cards/8_of_hearts.png"));
			SetTexture2D("NINE_HEARTS", new Texture2D("res/Cards/9_of_hearts.png"));
			SetTexture2D("TEN_HEARTS", new Texture2D("res/Cards/10_of_hearts.png"));
			SetTexture2D("JACK_HEARTS", new Texture2D("res/Cards/jack_of_hearts2.png"));
			SetTexture2D("QUEEN_HEARTS", new Texture2D("res/Cards/queen_of_hearts2.png"));
			SetTexture2D("KING_HEARTS", new Texture2D("res/Cards/king_of_hearts2.png"));
			SetTexture2D("ACE_DIAMONDS", new Texture2D("res/Cards/ace_of_diamonds.png"));
			SetTexture2D("TWO_DIAMONDS", new Texture2D("res/Cards/2_of_diamonds.png"));
			SetTexture2D("THREE_DIAMONDS", new Texture2D("res/Cards/3_of_diamonds.png"));
			SetTexture2D("FOUR_DIAMONDS", new Texture2D("res/Cards/4_of_diamonds.png"));
			SetTexture2D("FIVE_DIAMONDS", new Texture2D("res/Cards/5_of_diamonds.png"));
			SetTexture2D("SIX_DIAMONDS", new Texture2D("res/Cards/6_of_diamonds.png"));
			SetTexture2D("SEVEN_DIAMONDS", new Texture2D("res/Cards/7_of_diamonds.png"));
			SetTexture2D("EIGHT_DIAMONDS", new Texture2D("res/Cards/8_of_diamonds.png"));
			SetTexture2D("NINE_DIAMONDS", new Texture2D("res/Cards/9_of_diamonds.png"));
			SetTexture2D("TEN_DIAMONDS", new Texture2D("res/Cards/10_of_diamonds.png"));
			SetTexture2D("JACK_DIAMONDS", new Texture2D("res/Cards/jack_of_diamonds2.png"));
			SetTexture2D("QUEEN_DIAMONDS", new Texture2D("res/Cards/queen_of_diamonds2.png"));
			SetTexture2D("KING_DIAMONDS", new Texture2D("res/Cards/king_of_diamonds2.png"));
			SetTexture2D("ACE_CLUBS", new Texture2D("res/Cards/ace_of_clubs.png"));
			SetTexture2D("TWO_CLUBS", new Texture2D("res/Cards/2_of_clubs.png"));
			SetTexture2D("THREE_CLUBS", new Texture2D("res/Cards/3_of_clubs.png"));
			SetTexture2D("FOUR_CLUBS", new Texture2D("res/Cards/4_of_clubs.png"));
			SetTexture2D("FIVE_CLUBS", new Texture2D("res/Cards/5_of_clubs.png"));
			SetTexture2D("SIX_CLUBS", new Texture2D("res/Cards/6_of_clubs.png"));
			SetTexture2D("SEVEN_CLUBS", new Texture2D("res/Cards/7_of_clubs.png"));
			SetTexture2D("EIGHT_CLUBS", new Texture2D("res/Cards/8_of_clubs.png"));
			SetTexture2D("NINE_CLUBS", new Texture2D("res/Cards/9_of_clubs.png"));
			SetTexture2D("TEN_CLUBS", new Texture2D("res/Cards/10_of_clubs.png"));
			SetTexture2D("JACK_CLUBS", new Texture2D("res/Cards/jack_of_clubs2.png"));
			SetTexture2D("QUEEN_CLUBS", new Texture2D("res/Cards/queen_of_clubs2.png"));
			SetTexture2D("KING_CLUBS", new Texture2D("res/Cards/king_of_clubs2.png"));
			SetTexture2D("ACE_SPADES", new Texture2D("res/Cards/ace_of_spades.png"));
			SetTexture2D("TWO_SPADES", new Texture2D("res/Cards/2_of_spades.png"));
			SetTexture2D("THREE_SPADES", new Texture2D("res/Cards/3_of_spades.png"));
			SetTexture2D("FOUR_SPADES", new Texture2D("res/Cards/4_of_spades.png"));
			SetTexture2D("FIVE_SPADES", new Texture2D("res/Cards/5_of_spades.png"));
			SetTexture2D("SIX_SPADES", new Texture2D("res/Cards/6_of_spades.png"));
			SetTexture2D("SEVEN_SPADES", new Texture2D("res/Cards/7_of_spades.png"));
			SetTexture2D("EIGHT_SPADES", new Texture2D("res/Cards/8_of_spades.png"));
			SetTexture2D("NINE_SPADES", new Texture2D("res/Cards/9_of_spades.png"));
			SetTexture2D("TEN_SPADES", new Texture2D("res/Cards/10_of_spades.png"));
			SetTexture2D("JACK_SPADES", new Texture2D("res/Cards/jack_of_spades2.png"));
			SetTexture2D("QUEEN_SPADES", new Texture2D("res/Cards/queen_of_spades2.png"));
			SetTexture2D("KING_SPADES", new Texture2D("res/Cards/king_of_spades2.png"));
			SetTexture2D("JOKER_RED", new Texture2D("res/Cards/red_joker.png"));
			SetTexture2D("JOKER_BLACK", new Texture2D("res/Cards/black_joker.png"));
		}

		GameObject* CreateCard(Card* card, float depth)
		{
			Texture2D* texture = card->GetTexture();
			GameObject* newCard = AddToScene(GameObject::Instantiate("PlayingCard", -8, 0, depth))
				->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Square(), Material(Color::White(), ResourceManager::DefaultTextureShader(), "Tex0", texture)), Matrix4f::Scale(Card::WIDTH, Card::HEIGHT, 1)))
				->AddComponent(card)
				->AddComponent(new BoxCollider(Vector3f(Card::WIDTH, Card::HEIGHT, 0)));
			return newCard;
		}

		void Update() override
		{
			Manager.Update();

			if (Input::KeyPressed(Keycode::R))
			{
				Reset();
			}

			Graphics::CurrentContext().SetTitle("Presidents " + std::to_string((int)Time::AvgFPS()));
			GameObject* hand = GameObject::FindWithTag("Hand");
			Hand& handComp = hand->GetComponent<Hand>();
			Camera& camera = GameObject::FindWithTag("Camera")->GetComponent<Camera>();
			Ray r = camera.ScreenToWorldRay(Input::MousePosition());
			RaycastHit hit = Physics::Raycast(r);

			PlayField& playField = GameObject::FindWithTag("CardMat")->GetComponent<PlayField>();

			if (Input::KeyPressed(Keycode::O))
			{
				handComp.Order();
			}
			if (Input::KeyPressed(Keycode::P) && Manager.IsThisTurn(&handComp))
			{
				Manager.Pass(&handComp);
			}

			Vector3f mousePosition = camera.ScreenToWorldPoint(Input::MousePosition() + Vector3f(0, 0, 9));
			if (Manager.CardCount() > 0 && !hit.DidHit && handComp.CardCount() > 0)
			{
				int index = handComp.CalcIndex(mousePosition.x);				
				if (handComp.IsOpen() && (handComp.OpenIndex() != index))
				{
					handComp.CloseAt();
				}
				if (!handComp.IsOpen() && (handComp.OpenIndex() != index))
				{
					handComp.OpenAt(index);
				}
			}
			else if (handComp.IsOpen())
			{
				handComp.CloseAt();
			}

			handComp.DehighlightAll();
			if (hit.DidHit)
			{				
				GameObject* object = hit.GameObjects[0];
				if (Input::MouseButtonPressed(MouseButton::Left))
				{
					if (object->HasComponent<Card>())
					{						
						if (handComp.ContainsCard(object) && (Manager.CardCount() == 0 || object->GetComponent<Card>().Rank() == Manager.HeldCards()[0]->GetComponent<Card>().Rank()))
						{
							handComp.RemoveCard(object);
							Manager.AddHeldCard(object);
						}
					}
					else if (object->HasComponent<PlayField>() && Manager.IsThisTurn(&handComp))
					{
						if (Manager.CardCount() > 0 && playField.CanBeAdded(Manager.HeldCards()))
						{
							std::vector<GameObject*> cards = Manager.HeldCards();
							Manager.RemoveAllHeldCards();
							playField.PushCards(cards);							
							Manager.NextPlayer();
						}
					}
				}
				else
				{
					if (object->HasComponent<Card>() && handComp.ContainsCard(object))
					{
						handComp.HighlightCard(object, 1);
					}
				}
			}
			else if (Manager.CardCount() > 0)
			{
				if (Input::MouseButtonPressed(0))
				{
					std::vector<GameObject*> heldCards = Manager.HeldCards();
					Manager.RemoveAllHeldCards();
					int index = (handComp.OpenIndex() < 0) ? 0 : handComp.OpenIndex();
					for (int i = heldCards.size() - 1; i >= 0; i--)
					{
						handComp.AddCard(heldCards[i], index);
					}
				}
				else if (Input::MouseButtonPressed(MouseButton::Right))
				{
					int index = (handComp.OpenIndex() < 0) ? 0 : handComp.OpenIndex();
					GameObject* card = Manager.HeldCards()[0];
					Manager.RemoveHeldCard(card);
					handComp.AddCard(card, index);
				}
			}

			Application::Update();
		}

		void Render() override
		{
			Graphics::Clear();
			Graphics::RenderScene();
			Graphics::Present();
		}

		void Reset()
		{
			GameObject::FindAllWith<PlayField>()[0]->GetComponent<PlayField>().Clear();
			Manager.RemoveAllHeldCards();
			for (GameObject* hand : GameObject::FindAllWith<Hand>())
			{
				hand->GetComponent<Hand>().ClearAll();
			}

			GameObject* deck = GameObject::FindWithTag("Deck");
			deck->GetComponent<Deck>().Reset();
			deck->GetComponent<Deck>().Shuffle();

			std::vector<Hand*> hands;
			for (GameObject* c : GameObject::FindAllWith<Hand>())
			{
				if (c->Tag() != "Mouse")
				{
					hands.push_back(&c->GetComponent<Hand>());
				}
			}
			deck->GetComponent<Deck>().DealTo(hands, 10, 20);
		}

	};

}

int main()
{
	Presidents::Game presidents;
	presidents.Start();
	return 0;
}