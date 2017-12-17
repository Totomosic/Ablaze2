#include "Ablaze.h"
#include <Windows.h>
#include <commdlg.h>

using namespace Ablaze;
using namespace Ablaze::Maths;
using namespace Ablaze::VM;

namespace TextEditor
{

	class Game : public Application
	{
	public:
		Window* m_Window;

		std::vector<GameObject*> m_Texts;
		GameObject* m_CurrentText;
		String m_CurrentString;

	public:
		void Init() override
		{
			m_Window = new Window(800, 600, "Text Editor", Color::White() * 0.9f);
			Graphics::Initialise(m_Window);

			SetFont("Font", new Font("res/Arial.ttf", 18));
			m_CurrentString = "";

			Scene& scene = SceneManager::Instance().CreateScene();
			Layer& layer = scene.CreateLayer("Text");

			CreateNewText();

			GameObject* canvas = GameObject::Instantiate("Canvas", 0, 0, 10);
			canvas->AddComponent(new Camera(Projection::Orthographic));
			layer.SetActiveCamera(canvas);			

			GraphicsPipeline g;
			g.Renderer = new ForwardRenderer;
			g.Schedule = new RenderSchedule;
			g.Schedule->AddRenderPass(new RenderPass("Default"));
			Graphics::AddGraphicsPipeline(g);
		}

		void Tick() override
		{

		}

		void Update() override
		{

			if (Input::KeyPressed(Keycode::ENTER))
			{
				CreateNewText();
			}
			bool foundChar = false;
			for (char c : Input::CharsPressed())
			{
				AddCharacter(c);
				foundChar = true;
			}
			if (foundChar)
			{
				UpdateCurrentText();
			}

			if (Input::KeyPressed(Keycode::BACKSPACE))
			{
				RemoveCharacter();
			}

			if (Input::KeyPressed(Keycode::S, KeyMod::CTRL))
			{
				char filename[MAX_PATH];
				OPENFILENAME ofn;
				ZeroMemory(&filename, sizeof(filename));
				ZeroMemory(&ofn, sizeof(ofn));
				ofn.lStructSize = sizeof(ofn);
				ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
				ofn.lpstrFilter = "Text Files (*.txt)\0*.txt\0Any File (*.*)\0*.*\0";
				ofn.lpstrFile = filename;
				ofn.nMaxFile = MAX_PATH;
				ofn.lpstrTitle = "Save as";
				ofn.Flags = OFN_DONTADDTORECENT;

				if (GetSaveFileName(&ofn))
				{
					SaveFile(filename);
				}
			}

			Application::Update();
		}

		void Render() override
		{
			Application::Render();

			Graphics::Clear();
			Graphics::RenderScene();
			Graphics::Present();

		}

		void RemoveCharacter()
		{
			if (m_CurrentString.length() > 0)
			{
				m_CurrentString.erase(m_CurrentString.end() - 1);
				UpdateCurrentText();
			}
			else if (m_Texts.size() > 1)
			{
				RemoveCurrentText();
				RemoveCharacter();
			}
		}

		void CreateNewText()
		{
			m_CurrentString.clear();
			Vector2f fontSize = GetFont("Font")->GetSize("pT");
			GameObject* text = GameObject::Instantiate("__TEXT__", 5, WindowHeight() - 5 - fontSize.y * (m_Texts.size() + 1) - m_Texts.size() * 3, 0);
			text->AddComponent(new Text(m_CurrentString, GetFont("Font"), Color::Black(), TextAlignmentH::Left, TextAlignmentV::Bottom));

			m_Texts.push_back(text);
			m_CurrentText = text;
		}

		void RemoveCurrentText()
		{
			m_Texts.pop_back();
			m_CurrentText->Destroy();
			m_CurrentText = m_Texts.back();
			m_CurrentString = m_CurrentText->GetComponent<Text>().RawString();
		}

		void UpdateCurrentText()
		{
			m_CurrentText->GetComponent<Text>().SetText(m_CurrentString);
		}

		void AddCharacter(char c)
		{
			m_CurrentString += c;
			Vector2f textSize = GetFont("Font")->GetSize(m_CurrentString);
			if (textSize.x > WindowWidth() - 10 - 5)
			{
				UpdateCurrentText();
				CreateNewText();
			}
		}

		void Reset()
		{
			for (GameObject* text : m_Texts)
			{
				text->Destroy();
			}
			m_Texts.clear();
			m_CurrentText = nullptr;
			m_CurrentString.clear();
		}

		void OpenFile(const String& file)
		{
			Reset();
			File f = Filesystem::OpenFile(file);
			String text = f.ReadText();
			std::vector<String> lines = SplitString(text, "\n");
			for (String& line : lines)
			{
				CreateNewText();
				m_CurrentString = line;
				UpdateCurrentText();
			}
		}

		void SaveFile(const String& file)
		{
			String str = "";
			for (GameObject* text : m_Texts)
			{
				str += text->GetComponent<Text>().RawString() + "\n";
			}
			str.erase(str.end() - 1); // Remove last new line
			File f = Filesystem::OpenFile(file, OpenFlags::Override);
			f.WriteText(str);
		}

	};

}

int main()
{
	TextEditor::Game g;
	g.Start();
	return 0;
}