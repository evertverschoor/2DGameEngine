#ifndef CAMERA_H
#define CAMERA_H

#include "Position.h"
#include "Dimension.h"
#include "CameraMovement.h"
#include "PcInputHandler.h"
#include "GamepadInputHandler.h"
#include "VideoSettings.h"
#include "Entity.h"
#include "TimeController.h"

#define CAMERA_DEFAULT_SPEED 50
#define CAMERA_DEFAULT_MOMENTUM_INCREASE 2

/// <summary>
/// The camera is used by the renderer to determine what portion of the active scene to draw.
/// It is controlled by user input or chases an entity in the active scene.
/// </summary>
class Camera : public PcInputHandler, public GamepadInputHandler
{
public:
	/// <summary>
	/// @param1 The gamepad number
	/// @param2 The virtual resolution (make sure the virtual resolution is the same everywhere)
	/// @param3 The Video settings so the camera can determine the screen size
	/// </summary>
	Camera(int, Dimension*, VideoSettings*);
	~Camera();

	/// <summary>
	/// Returns the current camera position.
	/// </summary>
	Position* GetPosition();

	/// <summary>
	/// Set the way the camera moves, use values from CameraMovement enum.
	/// </summary>
	int SetCameraMovement(CameraMovement);

	/// <summary>
	/// Set the entity that will be chased when the camera movement is set to ENTITY_CHASE
	/// </summary>
	int SetChasableEntity(Entity*);

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

	VideoSettings* settings;
	TimeController* time;

	// Camera movement mode
	CameraMovement movement;

	// Entity to chase if the mode is ENTITY_CHASE
	Entity* chasableEntity;

	// Gamepad number that controls the camera
	int gamepadNumber;

	// Measurement values so the calculations only have to be done once and not every frame
	int monitorCenterX, monitorCenterY;
	int windowCenterX, windowCenterY;
	int virtualCenterX, virtualCenterY;
	int entityCenterX, entityCenterY;

	// Camera momentum for smooth camera movement
	int momentum;

	/// <summary>
	/// Move the camera based on the entity we're chasing.
	/// </summary>
	int ChaseEntity();

	/// <summary>
	/// Jump the camera to new X and Y coordinates.
	/// Using this function never makes motion blur happen.
	/// </summary>
	int JumpTo(int, int);

	/// <summary>
	/// Move the camera certain values in X and Y direction.
	/// Using this function makes motion blur happen.
	/// @param1 How far the camera moves in direction X.
	/// @param2 How far the camera moves in direction Y.
	/// </summary>
	int Move(int, int);
};

#endif