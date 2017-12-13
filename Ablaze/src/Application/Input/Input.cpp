#include "Input.h"
#include "Graphics\Rendering\Graphics.h"

namespace Ablaze
{

	KeyMod operator|(KeyMod a, KeyMod b)
	{
		return (KeyMod)((int)a | (int)b);
	}

	bool Input::s_Started = false;

	int Input::s_MaxButtons = 32;
	int Input::s_MaxKeys = 512;

	bool* Input::s_ButtonsDown = new bool[s_MaxButtons];
	bool* Input::s_KeysDown = new bool[s_MaxKeys];
	std::vector<std::pair<int, Keystate>> Input::s_ButtonsPressed = std::vector<std::pair<int, Keystate>>();
	std::vector<std::pair<int, Keystate>> Input::s_KeysPressed = std::vector<std::pair<int, Keystate>>();
	std::vector<char> Input::s_CharsPressed = std::vector<char>();

	Maths::Vector3f Input::s_MousePosition = Maths::Vector3f(0.0f);
	Maths::Vector3f Input::s_RelMousePosition = Maths::Vector3f(0.0f);
	Maths::Vector2f Input::s_MouseScroll = Maths::Vector2f(0.0f);
	Maths::Vector2f Input::s_RelMouseScroll = Maths::Vector2f(0.0f);

	String Input::ToString() const
	{
		return "Input Manager";
	}

	Maths::Vector2f Input::ScreenSize()
	{
		return Maths::Vector2f(Graphics::CurrentContext().Width(), Graphics::CurrentContext().Height());
	}

	Maths::Vector3f Input::MousePosition(Origin origin)
	{
		switch (origin)
		{
		case Origin::BottomLeft:
			return Maths::Vector3f(s_MousePosition.x, ScreenSize().y - s_MousePosition.y, 0);
		case Origin::TopLeft:
			return s_MousePosition;
		case Origin::Center:
			return Maths::Vector3f(s_MousePosition.x * 2 - ScreenSize().x / 2.0f, -(s_MousePosition.y * 2 - ScreenSize().y / 2.0f), 0);
		case Origin::TopRight:
			return Maths::Vector3f(ScreenSize().x - s_MousePosition.x, s_MousePosition.y, 0);
		case Origin::BottomRight:
			return Maths::Vector3f(ScreenSize().x - s_MousePosition.x, ScreenSize().y - s_MousePosition.y, 0);
		default:
			return MousePosition(Origin::BottomLeft);
		}
	}

	Maths::Vector3f Input::NormalizedMousePosition(Origin origin)
	{
		if (origin != Origin::Center)
		{
			return MousePosition(origin) / Maths::Vector3f(ScreenSize(), 1);
		}
		return MousePosition(origin) / Maths::Vector3f(ScreenSize() / 2, 1);
	}

	Maths::Vector3f Input::RelMousePosition(Origin origin)
	{
		switch (origin)
		{
		case Origin::BottomLeft:
			return Maths::Vector3f(s_RelMousePosition.x, -s_RelMousePosition.y, 0);
		case Origin::TopLeft:
			return s_RelMousePosition;
		case Origin::Center:
			return Maths::Vector3f(s_RelMousePosition.x, -s_RelMousePosition.y, 0);
		case Origin::TopRight:
			return Maths::Vector3f(-s_RelMousePosition.x, s_RelMousePosition.y, 0);
		case Origin::BottomRight:
			return Maths::Vector3f(-s_RelMousePosition.x, -s_RelMousePosition.y, 0);
		default:
			return RelMousePosition(Origin::BottomLeft);
		}
	}

	const Maths::Vector2f& Input::MouseScroll()
	{
		return s_MouseScroll;
	}

	const Maths::Vector2f& Input::RelMouseScroll()
	{
		return s_RelMouseScroll;
	}

	bool Input::MouseButtonDown(MouseButton button, KeyMod mods)
	{
		return MouseButtonDown((int)button, mods);
	}

	bool Input::MouseButtonDown(int button, KeyMod mods)
	{
		return s_ButtonsDown[button] && SatisfiesModifiers(mods);
	}

	bool Input::MouseButtonUp(MouseButton button, KeyMod mods)
	{
		return !MouseButtonDown(button, KeyMod::None) && SatisfiesModifiers(mods);
	}

	bool Input::MouseButtonUp(int button, KeyMod mods)
	{
		return !MouseButtonDown(button, KeyMod::None) && SatisfiesModifiers(mods);
	}

	bool Input::MouseButtonPressed(MouseButton button, KeyMod mods)
	{
		return MouseButtonPressed((int)button, mods);
	}

	bool Input::MouseButtonPressed(int button, KeyMod mods)
	{
		for (auto buttonPair : s_ButtonsPressed)
		{
			if (buttonPair.first == button && buttonPair.second == Keystate::Pressed && SatisfiesModifiers(mods))
				return true;
		}
		return false;
	}

	bool Input::MouseButtonReleased(MouseButton button, KeyMod mods)
	{
		return MouseButtonPressed((int)button, mods);
	}

	bool Input::MouseButtonReleased(int button, KeyMod mods)
	{
		for (auto buttonPair : s_ButtonsPressed)
		{
			if (buttonPair.first == button && buttonPair.second == Keystate::Released && SatisfiesModifiers(mods))
				return true;
		}
		return false;
	}

	bool Input::KeyDown(Keycode key, KeyMod mods)
	{
		return KeyDown((int)key, mods);
	}

	bool Input::KeyDown(int key, KeyMod mods)
	{
		return s_KeysDown[key] && SatisfiesModifiers(mods);
	}

	bool Input::KeyUp(Keycode key, KeyMod mods)
	{
		return !KeyDown(key, KeyMod::None) && SatisfiesModifiers(mods);
	}

	bool Input::KeyUp(int key, KeyMod mods)
	{
		return !KeyDown(key, KeyMod::None) && SatisfiesModifiers(mods);
	}

	bool Input::KeyPressed(Keycode key, KeyMod mods)
	{
		return KeyPressed((int)key, mods);
	}

	bool Input::KeyPressed(int key, KeyMod mods)
	{
		for (auto keyPair : s_KeysPressed)
		{
			if (keyPair.first == key && keyPair.second == Keystate::Pressed && SatisfiesModifiers(mods))
				return true;
		}
		return false;
	}

	bool Input::KeyReleased(Keycode key, KeyMod mods)
	{
		return KeyReleased((int)key, mods);
	}

	bool Input::KeyReleased(int key, KeyMod mods)
	{
		for (auto keyPair : s_KeysPressed)
		{
			if (keyPair.first == key && keyPair.second == Keystate::Released && SatisfiesModifiers(mods))
				return true;
		}
		return false;
	}

	void Input::CaptureCursor()
	{
		glfwSetInputMode(Graphics::CurrentContext().WindowHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}

	void Input::ReleaseCursor()
	{
		glfwSetInputMode(Graphics::CurrentContext().WindowHandle(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}

	const std::vector<char>& Input::CharsPressed()
	{
		return s_CharsPressed;
	}

	void Input::Initialise()
	{
		for (int i = 0; i < s_MaxButtons; i++)
		{
			s_ButtonsDown[i] = false;
		}
		for (int j = 0; j < s_MaxKeys; j++)
		{
			s_KeysDown[j] = false;
		}
	}

	void Input::Start()
	{
		s_Started = true;
		glfwPollEvents();
	}

	void Input::End()
	{
		s_RelMousePosition = Maths::Vector3f(0);
		s_RelMouseScroll = Maths::Vector2f(0);
		s_KeysPressed.clear();
		s_ButtonsPressed.clear();
		s_CharsPressed.clear();

		s_Started = false;
	}

	bool Input::SatisfiesModifiers(KeyMod mods)
	{
		if (mods == KeyMod::None)
		{
			return true;
		}
		bool result = true;

		if (IsBitSet((int)mods, 1))
		{
			// LShift
			result = result && (KeyDown(Keycode::LSHIFT, KeyMod::None));
		}
		if (IsBitSet((int)mods, 2))
		{
			// RShift
			result = result && (KeyDown(Keycode::RSHIFT, KeyMod::None));
		}
		if (IsBitSet((int)mods, 3))
		{
			// Either Shift
			result = result && (KeyDown(Keycode::LSHIFT, KeyMod::None) || KeyDown(Keycode::RSHIFT, KeyMod::None));
		}
		if (IsBitSet((int)mods, 4))
		{
			// LALT
			result = result && (KeyDown(Keycode::LALT, KeyMod::None));
		}
		if (IsBitSet((int)mods, 5))
		{
			// RALT
			result = result && (KeyDown(Keycode::RALT, KeyMod::None));
		}
		if (IsBitSet((int)mods, 6))
		{
			// Either ALT
			result = result && (KeyDown(Keycode::LALT, KeyMod::None) || KeyDown(Keycode::RALT, KeyMod::None));
		}
		if (IsBitSet((int)mods, 7))
		{
			// RCTRL
			result = result && (KeyDown(Keycode::RCTRL, KeyMod::None));
		}
		if (IsBitSet((int)mods, 8))
		{
			// LCTRL
			result = result && (KeyDown(Keycode::LCTRL, KeyMod::None));
		}
		if (IsBitSet((int)mods, 9))
		{
			// Either CTRL
			result = result && (KeyDown(Keycode::LCTRL, KeyMod::None) || KeyDown(Keycode::RCTRL, KeyMod::None));
		}
		if (IsBitSet((int)mods, 10))
		{
			// No shift
			result = result && !(KeyDown(Keycode::LSHIFT, KeyMod::None) || KeyDown(Keycode::RSHIFT, KeyMod::None));
		}
		if (IsBitSet((int)mods, 11))
		{
			// No alt
			result = result && !(KeyDown(Keycode::LALT, KeyMod::None) || KeyDown(Keycode::RALT, KeyMod::None));
		}
		if (IsBitSet((int)mods, 12))
		{
			// No ctrl
			result = result && !(KeyDown(Keycode::LCTRL, KeyMod::None) || KeyDown(Keycode::RCTRL, KeyMod::None));
		}

		return result;
	}

	void Input::MousePositionCallback(GLFWwindow* window, double x, double y)
	{
		s_RelMousePosition = s_MousePosition - Maths::Vector3f((float)x, (float)y, 0);
		s_MousePosition.x = (float)x;
		s_MousePosition.y = (float)y;
	}

	void Input::MousePressedCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			s_ButtonsDown[button] = true;
			s_ButtonsPressed.push_back(std::pair<int, Keystate>(button, Keystate::Pressed));
		}
		else if (action == GLFW_RELEASE)
		{
			s_ButtonsDown[button] = false;
			s_ButtonsPressed.push_back(std::pair<int, Keystate>(button, Keystate::Released));
		}
	}

	void Input::KeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			s_KeysDown[key] = true;
			s_KeysPressed.emplace_back(key, Keystate::Pressed);
		}
		else if (action == GLFW_RELEASE)
		{
			s_KeysDown[key] = false;
			s_KeysPressed.emplace_back(key, Keystate::Released);
		}
	}

	void Input::MouseScrollCallback(GLFWwindow* window, double xScroll, double yScroll)
	{
		s_RelMouseScroll = Maths::Vector2f((float)xScroll, (float)yScroll);
		s_MouseScroll += s_RelMouseScroll;
	}

	void Input::CharPressedCallback(GLFWwindow* window, uint c)
	{
		s_CharsPressed.push_back((char)c);
	}

}