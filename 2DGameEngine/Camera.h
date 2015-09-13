#ifndef CAMERA_H
#define CAMERA_H

#include "Position.h"
#include "Dimension.h"
#include "CameraMovement.h"
#include "PcInputHandler.h"
#include "GamepadInputHandler.h"
#include "GFXController.h"
#include "VideoSettings.h"

#define PI 3.14159265358979323846

/// <summary>
/// The camera is used by the renderer to determine what portion of the active scene to draw.
/// </summary>
class Camera : public PcInputHandler, public GamepadInputHandler
{
public:
	/// <summary>
	/// @param1 The gamepad number
	/// @param2 The virtual resolution (make sure the virtual resolution is the same everywhere)
	/// @param3 The GFXController the camera uses to pass motion blur information
	/// @param4 The Video settings so the camera can determine whether or not to calculace motion blur
	/// </summary>
	Camera(int, Dimension*, GFXController*, VideoSettings*);
	~Camera();

	/// <summary>
	/// Jump the camera to new X and Y coordinates.
	/// </summary>
	int JumpTo(int, int);

	/// <summary>
	/// Returns the current camera position.
	/// </summary>
	Position* GetPosition();

	/// <summary>
	/// Set the way the camera moves, use values from CameraMovement enum.
	/// </summary>
	int SetCameraMovement(CameraMovement);

	/// <summary>
	/// The size of the active scene is needed to calculate how far the camera may move.
	/// </summary>
	int SetActiveSceneSize(Dimension*);

	int GetGamepadNumber();
	int HandleGamepadInput(GamepadState*);
	int HandleKeyboardInput(KeyboardState*);
	int HandleMouseInput(MouseState*);
private:
	Position cameraPosition;
	Dimension* virtualResolution;
	Dimension* sceneSize;

	GFXController* gfx;
	VideoSettings* settings;

	CameraMovement movement;
	int gamepadNumber;

	int lastMouseX, lastMouseY;
	int monitorCenterX, monitorCenterY;
	int windowCenterX, windowCenterY;

	/// <summary>
	/// Move the camera using the edge pan method.
	/// </summary>
	int MoveCameraEdgePan(int, int);

	/// <summary>
	/// Move the camera using the mouse move method.
	/// </summary>
	int MoveCameraMouseMove(int, int);

	/// <summary>
	/// Calculate the motion blur from two deltas
	/// @param1 Delta X (difference between current and last mouse X position)
	/// @param2 Delta Y (difference between current and last mouse Y position)
	/// </summary>
	int CalculateMotionBlur(float, float);
};

#endif