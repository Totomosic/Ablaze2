#include "Chatbox.h"

Chatbox::Chatbox(float width, float height, const std::shared_ptr<Font>& font) : Component(),
	m_Width(width), m_Height(height), m_Font(font)
{

}

Chatbox::~Chatbox()
{
	for (GameObject* text : m_History)
	{
		text->Destroy();
	}
	m_CurrentText->Destroy();
}

void Chatbox::Start()
{
	SceneManager::Instance().CurrentScene().SetCurrentLayer(m_GameObject->GetLayer());
	Vector2f size = m_Font->GetSize("pT");
	m_CurrentText = GameObject::Instantiate("CurrentText", nullptr, m_GameObject, -(m_Width / 2.0f) + 5, -(m_Height / 2.0f) + 5, 10);
	m_CurrentText->AddComponent(new Text(m_CurrentString, m_Font, Color::Black(), TextAlignmentH::Left, TextAlignmentV::Bottom));

	m_Other = &Time::CreateNewTimer(0.3, METHOD_0(Chatbox::ActivateBackspace));
	m_Other->Stop();
	m_Other->Reset();
	m_BspaceTimer = &Time::CreateNewTimer(0.05, METHOD_0(Chatbox::CheckBackspace));
	m_BspaceTimer->Stop();
	m_BspaceTimer->Reset();
}

void Chatbox::Update(double elapsedSeconds)
{
	if (Input::KeyPressed(Keycode::ENTER))
	{
		m_IsTyping = !m_IsTyping;
		if (m_IsTyping == false)
		{
			Post(m_CurrentString, Color::Black());
			m_CurrentString.clear();
			UpdateTextModel();
		}
	}
	if (m_IsTyping)
	{
		bool foundChar = false;
		for (char c : Input::CharsPressed())
		{
			foundChar = true;
			m_CurrentString += c;
		}
		if (foundChar)
		{
			UpdateTextModel();
		}
		if (Input::KeyPressed(Keycode::BACKSPACE) && m_CurrentString.length() > 0)
		{
			m_CurrentString.erase(m_CurrentString.end() - 1);
			UpdateTextModel();
			m_Other->Start();
		}
	}
}

void Chatbox::Post(const String& message, const Color& color)
{
	SceneManager::Instance().CurrentScene().SetCurrentLayer(m_GameObject->GetLayer());
	Vector2f size = m_Font->GetSize("pT");
	GameObject* newText = GameObject::Instantiate("__CHAT__MESSAGES__", nullptr, m_GameObject, -(m_Width / 2.0f) + 5, -(m_Height / 2.0f) + 5, 2);
	newText->AddComponent(new Text(message, m_Font, color, TextAlignmentH::Left, TextAlignmentV::Bottom));

	for (GameObject* obj : SceneManager::Instance().CurrentScene().CurrentLayer().GetNamedGameObjects("__CHAT__MESSAGES__"))
	{		
		obj->transform().LocalPosition().y += size.y * 1.5f;
		if (obj->transform().LocalPosition().y > m_Height / 2.0f - size.y)
		{
			obj->Destroy();
		}
	}
}

String Chatbox::ToString() const
{
	return "Chatbox";
}

Component* Chatbox::Clone() const
{
	Chatbox* c = new Chatbox(m_Width, m_Height, m_Font);
	c->m_CurrentText = GameObject::Instantiate("CurrentText", m_CurrentText);
	c->m_CurrentString = m_CurrentString;
	c->m_IsTyping = m_IsTyping;
	return c;
}

void Chatbox::ActivateBackspace()
{
	m_Other->Stop();
	m_Other->Reset();
	m_BspaceTimer->Start();
}

void Chatbox::CheckBackspace()
{
	if (Input::KeyDown(Keycode::BACKSPACE) && m_CurrentString.length() > 0)
	{
		m_CurrentString.erase(m_CurrentString.end() - 1);
		UpdateTextModel();
	}
	else
	{
		m_BspaceTimer->Stop();
		m_BspaceTimer->Reset();
	}
}

void Chatbox::UpdateTextModel()
{
	m_CurrentText->GetComponent<Text>().SetText(m_CurrentString);
}