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
		Centre
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
		None = 1,
		LShift = 2,
		RShift = 4,
		Shift = 8,
		LALT = 16,
		RALT = 32,
		ALT = 64,
		RCTRL = 128,
		LCTRL = 256,
		CTRL = 512,
		NoShift = 1024,
		NoALT = 2048,
		NoCTRL = 4096
	};

	KeyMod operator|(KeyMod a, KeyMod b);

	enum class Keycode
	{
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
		static int s_MaxKeys;
		static int s_MaxButtons;

		static bool* s_KeysDown;
		static bool* s_ButtonsDown;
		static std::vector<std::pair<int, Keystate>> s_KeysPressed;
		static std::vector<std::pair<int, Keystate>> s_ButtonsPressed;

		static Maths::Vec3 s_MousePosition; // Represented as TopLeft Origin
		static Maths::Vec3 s_RelMousePosition; // Represented as TopLeft Origin
		static Maths::Vec2 s_MouseScroll;
		static Maths::Vec2 s_RelMouseScroll;

	public:
		Input() = delete;

		String ToString() const override;

	public:
		static Maths::Vec2 ScreenSize();

		static Maths::Vec3 MousePosition(Origin origin = Origin::BottomLeft);
		static Maths::Vec3 NormalizedMousePosition(Origin origin = Origin::BottomLeft);
		static Maths::Vec3 RelMousePosition(Origin origin = Origin::BottomLeft);
		static const Maths::Vec2& MouseScroll();
		static const Maths::Vec2& RelMouseScroll();
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

		friend class Window;
		friend class Application;
		friend class Engine;

	private:
		static void Initialise();
		static void Update();
		static bool SatisfiesModifiers(KeyMod modifier);

		static void MousePositionCallback(GLFWwindow* window, double mouseX, double mouseY);
		static void MousePressedCallback(GLFWwindow* window, int button, int action, int mods);
		static void KeyPressedCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseScrollCallback(GLFWwindow* window, double scrollX, double scrollY);

	};

}