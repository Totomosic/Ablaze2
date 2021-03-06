#pragma once
#include "Common.h"
#include "Graphics\Window.h"

namespace Ablaze
{

	enum class Origin
	{
		TopLeft,
		TopRight,
		BottomLeft,
		BottomRight,
		Center
	};

	enum class MouseButton
	{
		Left,
		Right,
		Middle,		
		Custom0,
		Custom1,
		Custom2,
		Custom3,
		Custom4,
		Custom5
	};

	enum class Keystate
	{
		Pressed,
		Released,
		None
	};

	enum class KeyMod
	{
		None = BIT(0),
		LShift = BIT(1),
		RShift = BIT(2),
		Shift = BIT(3),
		LALT = BIT(4),
		RALT = BIT(5),
		ALT = BIT(6),
		RCTRL = BIT(7),
		LCTRL = BIT(8),
		CTRL = BIT(9),
		NoShift = BIT(10),
		NoALT = BIT(11),
		NoCTRL = BIT(12)
	};

	KeyMod operator|(KeyMod a, KeyMod b);

	enum class Keycode : int
	{
		None = -2,
		UNKNOWN = GLFW_KEY_UNKNOWN,

		N_0 = GLFW_KEY_0,
		N_1 = GLFW_KEY_1,
		N_2 = GLFW_KEY_2,
		N_3 = GLFW_KEY_3,
		N_4 = GLFW_KEY_4,
		N_5 = GLFW_KEY_5,
		N_6 = GLFW_KEY_6,
		N_7 = GLFW_KEY_8,
		N_8 = GLFW_KEY_9,
		N_9 = GLFW_KEY_9,

		A = GLFW_KEY_A,
		B = GLFW_KEY_B,
		C = GLFW_KEY_C,
		D = GLFW_KEY_D,
		E = GLFW_KEY_E,
		F = GLFW_KEY_F,
		G = GLFW_KEY_G,
		H = GLFW_KEY_H,
		I = GLFW_KEY_I,
		J = GLFW_KEY_J,
		K = GLFW_KEY_K,
		L = GLFW_KEY_L,
		M = GLFW_KEY_M,
		N = GLFW_KEY_N,
		O = GLFW_KEY_O,
		P = GLFW_KEY_P,
		Q = GLFW_KEY_Q,
		R = GLFW_KEY_R,
		S = GLFW_KEY_S,
		T = GLFW_KEY_T,
		U = GLFW_KEY_U,
		V = GLFW_KEY_V,
		W = GLFW_KEY_W,
		X = GLFW_KEY_X,
		Y = GLFW_KEY_Y,
		Z = GLFW_KEY_Z,

		COMMA = GLFW_KEY_COMMA,
		PERIOD = GLFW_KEY_PERIOD,
		SLASH = GLFW_KEY_SLASH,
		SEMICOLON = GLFW_KEY_SEMICOLON,
		APOSTROPHE = GLFW_KEY_APOSTROPHE,
		OPENBRACKET = GLFW_KEY_LEFT_BRACKET,
		CLOSEBRACKET = GLFW_KEY_RIGHT_BRACKET,
		HYPHEN = GLFW_KEY_MINUS,
		EQUALS = GLFW_KEY_EQUAL,
		BACKSPACE = GLFW_KEY_BACKSPACE,
		BACKSLASH = GLFW_KEY_BACKSLASH,
		ENTER = GLFW_KEY_ENTER,
		LSHIFT = GLFW_KEY_LEFT_SHIFT,
		RSHIFT = GLFW_KEY_RIGHT_SHIFT,
		LCTRL = GLFW_KEY_LEFT_CONTROL,
		RCTRL = GLFW_KEY_RIGHT_CONTROL,
		LALT = GLFW_KEY_LEFT_ALT,
		RALT = GLFW_KEY_RIGHT_ALT,
		TAB = GLFW_KEY_TAB,
		CAPSLOCK = GLFW_KEY_CAPS_LOCK,
		GRAVEACCENT = GLFW_KEY_GRAVE_ACCENT,
		ESCAPE = GLFW_KEY_ESCAPE,
		SPACE = GLFW_KEY_SPACE,

		Left = GLFW_KEY_LEFT,
		Up = GLFW_KEY_UP,
		Right = GLFW_KEY_RIGHT,
		Down = GLFW_KEY_DOWN,

		F1 = GLFW_KEY_F1,
		F2 = GLFW_KEY_F2,
		F3 = GLFW_KEY_F3,
		F4 = GLFW_KEY_F4,
		F5 = GLFW_KEY_F5,
		F6 = GLFW_KEY_F6,
		F7 = GLFW_KEY_F7,
		F8 = GLFW_KEY_F8,
		F9 = GLFW_KEY_F9,
		F10 = GLFW_KEY_F10,
		F11 = GLFW_KEY_F11,
		F12 = GLFW_KEY_F12

	};

	class AB_API Input : public Object
	{
	private:
		static bool s_Started;

		static int s_MaxKeys;
		static int s_MaxButtons;

		static bool* s_KeysDown;
		static bool* s_ButtonsDown;
		static std::vector<std::pair<int, Keystate>> s_KeysPressed;
		static std::vector<std::pair<int, Keystate>> s_ButtonsPressed;
		static std::vector<char> s_CharsPressed;

		static Maths::Vector3f s_MousePosition; // Represented as TopLeft Origin
		static Maths::Vector3f s_RelMousePosition; // Represented as TopLeft Origin
		static Maths::Vector2f s_MouseScroll;
		static Maths::Vector2f s_RelMouseScroll;

	public:
		Input() = delete;

		String ToString() const override;

	public:
		static Maths::Vector2f ScreenSize();

		static Maths::Vector3f MousePosition(Origin origin = Origin::BottomLeft);
		static Maths::Vector3f NormalizedMousePosition(Origin origin = Origin::BottomLeft);
		static Maths::Vector3f RelMousePosition(Origin origin = Origin::BottomLeft);
		static const Maths::Vector2f& MouseScroll();
		static const Maths::Vector2f& RelMouseScroll();
		static bool MouseButtonDown(MouseButton button, KeyMod mods = KeyMod::None);
		static bool MouseButtonDown(int button, KeyMod mods = KeyMod::None);
		static bool MouseButtonUp(MouseButton button, KeyMod mods = KeyMod::None);
		static bool MouseButtonUp(int button, KeyMod mods = KeyMod::None);
		static bool MouseButtonPressed(MouseButton button, KeyMod mods = KeyMod::None);
		static bool MouseButtonPressed(int button, KeyMod mods = KeyMod::None);
		static bool MouseButtonReleased(MouseButton button, KeyMod mods = KeyMod::None);
		static bool MouseButtonReleased(int button, KeyMod mods = KeyMod::None);

		static bool KeyDown(Keycode key, KeyMod mods = KeyMod::None);
		static bool KeyDown(int key, KeyMod mods = KeyMod::None);
		static bool KeyUp(Keycode key, KeyMod mods = KeyMod::None);
		static bool KeyUp(int key, KeyMod mods = KeyMod::None);
		static bool KeyPressed(Keycode key, KeyMod mods = KeyMod::None);
		static bool KeyPressed(int key, KeyMod mods = KeyMod::None);
		static bool KeyReleased(Keycode key, KeyMod mods = KeyMod::None);
		static bool KeyReleased(int key, KeyMod mods = KeyMod::None);

		static void CaptureCursor();
		static void ReleaseCursor();

		static const std::vector<char>& CharsPressed();

		friend class Window;
		friend class Application;
		friend class Engine;

	private:
		static void Initialise();
		static void Start();
		static void End();
		static bool SatisfiesModifiers(KeyMod modifier);

		static void MousePositionCallback(GLFWwindow* window, double mouseX, double mouseY);
		static void MousePressedCallback(GLFWwindow* window, int button, int action, int mods);
		static void KeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseScrollCallback(GLFWwindow* window, double scrollX, double scrollY);
		static void CharPressedCallback(GLFWwindow* window, uint c);

	};

}