#include "AblazeInclude.h"

#include "Components\__Components__.h"

namespace Presidents
{

	class Game : public Application
	{
	public:

	public:
		void Init() override
		{
			Window* window = new Window(1280, 720, "Presidents");
			Graphics::Initialise(window);

			LoadCardTextures();

			Scene& scene = SceneManager::Instance().CreateScene();
			Layer& gameBoard = scene.CreateLayer("GameBoard");
			scene.SetCurrentLayer(&gameBoard);

			GameObject* deck = AddToScene(GameObject::Instantiate("Deck", 200, WindowHeight() / 2, 0))
				->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Square(), Material(Color::White(), ResourceManager::DefaultTextureShader(), "Tex0", GetTexture2D("CARD_BACK"))), Matrix4f::Scale(Card::WIDTH, Card::HEIGHT, 1)))
				->AddComponent<Deck>();

			GameObject* camera = AddToScene(GameObject::Instantiate("Camera", 0, 0, 10))
				->AddComponent(new Camera(Projection::Orthographic));
			gameBoard.SetActiveCamera(camera);

			GraphicsPipeline g;
			g.Renderer = new ForwardRenderer;
			g.Schedule = new RenderSchedule;
			g.Schedule->AddRenderPass(new RenderPass("Default"));
			Graphics::AddGraphicsPipeline(g);
		}

		void LoadCardTextures()
		{
			SetTexture2D("CARD_BACK", new Texture2D("res/CardBack.jpg"));
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

		GameObject* CreateCard(Card* card)
		{
			GameObject* newCard = AddToScene(GameObject::Instantiate("PlayingCard", 400, WindowHeight() / 2, 0))
				->AddComponent(new MeshRenderer(new Mesh(ResourceManager::Square(), Material(Color::White(), ResourceManager::DefaultTextureShader(), "Tex0", card->GetTexture())), Matrix4f::Scale(Card::WIDTH, Card::HEIGHT, 1)))
				->AddComponent(card);
			return newCard;
		}

		void Update() override
		{
			static float depth = -500;
			
			if (Input::MouseButtonPressed(MouseButton::Left))
			{
				GameObject* deck = GameObject::FindWithTag("Deck");
				if (deck->GetComponent<Deck>().CardCount() > 0)
				{
					GameObject* card = CreateCard(deck->GetComponent<Deck>().TakeTop());
					card->transform().LocalPosition().z = depth;
					depth += 1.0f;
				}
				else
				{
					for (GameObject* deleteCard : GameObject::FindAllWithTag("PlayingCard"))
					{
						deleteCard->Destroy();
					}
					deck->GetComponent<Deck>().Reset();
					deck->GetComponent<Deck>().Shuffle();
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

	};

}

int main()
{
	Presidents::Game presidents;
	presidents.Start();
	return 0;
}