#pragma once
#include "Ablaze.h"

using namespace Ablaze;
using namespace Ablaze::Maths;

class Chatbox : public Component
{
private:
	float m_Width;
	float m_Height;
	std::vector<GameObject*> m_History;
	GameObject* m_CurrentText;
	String m_CurrentString;
	Font* m_Font;
	
	Timer* m_BspaceTimer;
	Timer* m_Other;

	bool m_IsTyping;

public:
	Chatbox(float width, float height, Font* font);
	~Chatbox() override;

	void Start() override;
	void Update(double elapsedSeconds) override;

	void Post(const String& message, const Color& color = Color::Black());

	String ToString() const override;
	Component* Clone() const override;

private:
	void ActivateBackspace();
	void CheckBackspace();
	void UpdateTextModel();

};