/// ------------------------------------------------------------ ///
/// Gamepad Directions that apply to the D-Pad and the joysticks ///
/// ------------------------------------------------------------ ///
#define GAMEPADSTATE_UP 1
#define GAMEPADSTATE_RIGHT 2
#define GAMEPADSTATE_DOWN 3
#define GAMEPADSTATE_LEFT 4

#ifndef GAMEPADSTATE_H
#define GAMEPADSTATE_H

/// <summary>
/// The gamepad state is a generic format for stored gamepad input.
/// </summary>
class GamepadState
{
public:
	virtual ~GamepadState() {};

	/// <summary>
	/// Has Start been pressed?
	/// </summary>
	virtual bool Start() = 0;

	/// <summary>
	/// Has Back been pressed?
	/// </summary>
	virtual bool Back() = 0;

	/// <summary>
	/// Has the left trigger been pressed?
	/// </summary>
	virtual bool LeftTrigger() = 0;

	/// <summary>
	/// Has the right trigger been pressed?
	/// </summary>
	virtual bool RightTrigger() = 0;

	/// <summary>
	/// Has the left bumper been pressed?
	/// </summary>
	virtual bool LeftBumper() = 0;

	/// <summary>
	/// Has the right bumper been pressed?
	/// </summary>
	virtual bool RightBumper() = 0;

	/// <summary>
	/// Has the left stick been pressed? (L3)
	/// </summary>
	virtual bool LeftStick() = 0;

	/// <summary>
	/// Has the right stick been pressed? (R3)
	/// </summary>
	virtual bool RightStick() = 0;

	/// <summary>
	/// Has A been pressed?
	/// </summary>
	virtual bool A() = 0;

	/// <summary>
	/// Has B been pressed?
	/// </summary>
	virtual bool B() = 0;

	/// <summary>
	/// Has X been pressed?
	/// </summary>
	virtual bool X() = 0;

	/// <summary>
	/// Has Y been pressed?
	/// </summary>
	virtual bool Y() = 0;

	/// <summary>
	/// Has the dpad been pressed in this direction?
	/// Use the GAMEPAD macros. (example; GAMEPADSTATE_UP)
	/// </summary>
	virtual bool DPadDirection(int) = 0;

	/// <summary>
	/// Has the stick been tilted in this direction?
	/// Use the GAMEPAD macros. (example; GAMEPADSTATE_UP)
	/// </summary>
	virtual bool LeftStickDirection(int) = 0;

	/// <summary>
	/// Has the stick been tilted in this direction?
	/// Use the GAMEPAD macros. (example; GAMEPADSTATE_UP)
	/// </summary>
	virtual bool RightStickDirection(int) = 0;
};

#endif