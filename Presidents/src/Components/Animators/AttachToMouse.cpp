#include "AttachToMouse.h"

namespace Presidents
{

	void AttachToMouse::Update(double elapsedSeconds)
	{
		GameObject* camera = GameObject::FindWithTag("Camera");
		Vector3f position = camera->GetComponent<Camera>().ScreenToWorldPoint(Input::MousePosition() + Vector3f(0, 0, 9.5f));
		m_GameObject->transform().LocalPosition() = position;
	}

	String AttachToMouse::ToString() const
	{
		return "AttachToMouse";
	}

	Component* AttachToMouse::Clone() const
	{
		return new AttachToMouse;
	}

}