/// ----------------------------------------- ///
/// Key values to be used with IsKeyPressed() ///
/// ----------------------------------------- ///
#define KEY_A 65
#define KEY_B 66
#define KEY_C 67
#define KEY_D 68
#define KEY_E 69
#define KEY_F 70
#define KEY_G 71
#define KEY_H 72
#define KEY_I 73
#define KEY_J 74
#define KEY_K 75
#define KEY_L 76
#define KEY_M 77
#define KEY_N 78
#define KEY_O 79
#define KEY_P 80
#define KEY_Q 81
#define KEY_R 82
#define KEY_S 83
#define KEY_T 84
#define KEY_U 85
#define KEY_V 86
#define KEY_W 87
#define KEY_X 88
#define KEY_Y 89
#define KEY_Z 90
#define KEY_NUM0 48
#define KEY_NUM1 49
#define KEY_NUM2 50
#define KEY_NUM3 51
#define KEY_NUM4 52
#define KEY_NUM5 53
#define KEY_NUM6 54
#define KEY_NUM7 55
#define KEY_NUM8 56
#define KEY_NUM9 57
#define KEY_SPACE 32
#define KEY_BACKSPACE 8
#define KEY_ENTER 13
#define KEY_ESC 27
#define KEY_SHIFT 16
#define KEY_CTRL 17
#define KEY_TAB  9
#define KEY_PLUS 187
#define KEY_DASH 189
#define KEY_SLASH 220
#define KEY_BACKSLASH 191
#define KEY_PERIOD  190
#define KEY_COMMA 188
#define KEY_UP 38
#define KEY_RIGHT 39
#define KEY_DOWN 40
#define KEY_LEFT 37

#ifndef KEYBOARDSTATE_H
#define KEYBOARDSTATE_H

#include <map>

/// <summary>
/// The generic keyboard state format to be read as user input.
/// </summary>
class KeyboardState
{
public:
	KeyboardState(std::map<int, bool>);
	~KeyboardState();

	/// <summary>
	/// Returns if a certain key is currently pressed.
	/// @param The key that should be checked, use the KEY macros. (example; KEY_A)
	/// </summary>
	bool IsKeyPressed(int);
private:
	std::map<int, bool> finalKeyboardMap;
};

#endif