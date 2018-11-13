#pragma once
#include <vector>

namespace cmm
{
	class Coxing
	{
	protected:
		enum KEY_ACTION
		{
			MOVE_LEFT = 0,
			MOVE_RIGHT,
			JUMP,
			ATTACK,
			SHIELD
		};

		static std::vector<int> keys;
	public:
		explicit Coxing();
		virtual ~Coxing();
	};

	class Keys : public Coxing
	{
	protected:
		enum KEY_ACTION
		{
			MOVE_LEFT = 0,
			MOVE_RIGHT,
			JUMP,
			ATTACK,
			SHIELD,
			JUMP_ATTACK,
			JUMP_SHIELD,
			PAUSE,
			CHAT,
			AMOUNT
		};

	public:
		explicit Keys();
		virtual ~Keys() override;

		static void setKey(int which, int newKey);	// special for chat class
		static int getKey(int which);
		static int getActiveKeysAmount();
		void resetKeys();
		void saveKeys();
		void loadKeys();
		bool isPossibleKey(const int &code);
	};
}
/*
enum  	Key {
Unknown = -1,
A = 0,
B,
C,
D, // 3
E,
F,
G,
H,
I,
J,
K, // 10
L,
M,
N,
O,
P, // 15
Q,
R,
S,
T,
U, // 20
V,
W,
X,
Y,
Z, // 25
Num0,
Num1,
Num2,
Num3,
Num4, // 30
Num5,
Num6,
Num7,
Num8,
Num9, // 35
Escape,
LControl, // 37
LShift, // 38
LAlt, // 39
LSystem, // 40
RControl, // 41
RShift, // 42
RAlt, // 43
RSystem,
Menu, // 45
LBracket,
RBracket,
SemiColon,
Comma,
Period,  // 50
Quote,
Slash,
BackSlash,
Tilde,
Equal, // 55
Dash,
Space, // 57
Return,
BackSpace,
Tab, // 60
PageUp,
PageDown,
End,
Home,
Insert, // 65
Delete,
Add,
Subtract,
Multiply,
Divide, // 70
Left, // 71
Right, // 72
Up, // 73
Down, // 74
Numpad0, // 75
Numpad1,
Numpad2,
Numpad3,
Numpad4,
Numpad5,
Numpad6,
Numpad7,
Numpad8,
Numpad9, // 84
F1,
F2,
F3,
F4,
F5,
F6,
F7,
F8,
F9,
F10,
F11,
F12,
F13,
F14,
F15,
Pause,
KeyCount
}
*/