#include "Camera.h"


Camera::Camera(int _gamepadno, Dimension* _virtualResolution, GFXController* _gfx, VideoSettings* _settings, TimeController* _time)
{
	gamepadNumber = _gamepadno;
	virtualResolution = _virtualResolution;
	gfx = _gfx;
	settings = _settings;
	time = _time;

	// Default camera movement mode is MOUSE_MOVE
	SetCameraMovement(CameraMovement::NORMAL);

	// And no chasable entity yet
	chasableEntity = NULL;

	// Determine the monitor center
	monitorCenterX = settings->monitorRes->width / 2;
	monitorCenterY = settings->monitorRes->height / 2;

	// Determine the window center
	windowCenterX = settings->screenRes->width / 2;
	windowCenterY = settings->screenRes->height / 2;

	// Determine the virtual resolution center
	virtualCenterX = virtualResolution->width / 2;
	virtualCenterY = virtualResolution->height / 2;

	// Put a temporary entity center
	entityCenterX = 100;
	entityCenterY = 100;
}


Camera::~Camera()
{
}


int Camera::JumpTo(int _x, int _y)
{
	cameraPosition.X = _x;
	cameraPosition.Y = _y;

	return 1;
}


int Camera::Move(int _x, int _y)
{
	// Calculate the new position
	int _newPosX = cameraPosition.X + _x;
	int _newPosY = cameraPosition.Y + _y;

	// Validate the new position for values below 0
	if (0 > _newPosX) _newPosX = 0;
	if (0 > _newPosY) _newPosY = 0;

	// Validate the new position for values above the scene size
	if (sceneSize->width < _newPosX) _newPosX = sceneSize->width;
	if (sceneSize->height < _newPosY) _newPosY = sceneSize->height;

	// Calculate motion blur based on x and y move values, if turned on
	if (settings->motionBlur && movement == NORMAL) CalculateMotionBlur(_newPosX - cameraPosition.X, _newPosY - cameraPosition.Y);

	// Make the jump
	JumpTo(_newPosX, _newPosY);

	return 1;
}


Position* Camera::GetPosition()
{
	if (movement == ENTITY_CHASE && chasableEntity != NULL) ChaseEntity();
	return &cameraPosition;
}


int Camera::SetCameraMovement(CameraMovement _value)
{
	movement = _value;
	return 1;
}


int Camera::SetChasableEntity(Entity* _entity)
{
	chasableEntity = _entity;
	entityCenterX = _entity->GetHitbox()->width / 2;
	entityCenterY = _entity->GetHitbox()->height / 2;

	return 1;
}


int Camera::SetActiveSceneSize(Dimension* _size)
{
	sceneSize = _size;
	return 1;
}


int Camera::GetGamepadNumber()
{
	return gamepadNumber;
}


int Camera::HandleGamepadInput(GamepadState* _state)
{
	// Only move the camera if the camera movement is set to NORMAL
	if (movement != NORMAL) return 0;

	// Normalize the movespeed for all framerates
	int _moveAmount = time->GetMoveDistanceForSpeed(CAMERA_DEFAULT_SPEED);

	// Initialize the move amounts, depending on what direction(s) the stick is facing
	int _moveX = 0;
	int _moveY = 0;

	if (_state->RightStickDirection(GAMEPADSTATE_RIGHT))
	{
		_moveX += _moveAmount;
	}
	if (_state->RightStickDirection(GAMEPADSTATE_LEFT))
	{
		_moveX -= _moveAmount;
	}
	if (_state->RightStickDirection(GAMEPADSTATE_UP))
	{
		_moveY -= _moveAmount;
	}
	if (_state->RightStickDirection(GAMEPADSTATE_DOWN))
	{
		_moveY += _moveAmount;
	}

	// Only call Move() if _moveX or _moveY is not 0
	if(_moveX != 0 || _moveY != 0) Move(_moveX, _moveY);

	return 0;
}


int Camera::HandleKeyboardInput(KeyboardState* _state)
{
	return 1;
}


int Camera::HandleMouseInput(MouseState*_state )
{
	// Only move the camera if the camera movement is set to NORMAL
	if (movement != NORMAL) return 0;

	// Save the current mouse positions
	int _mouseX = _state->GetCursorPosition()->X;
	int _mouseY = _state->GetCursorPosition()->Y;

	// If the mouse is located at the center, it means this is the call from SetCursorPos at the bottom of this function, ignore it
	if (_mouseX == windowCenterX && _mouseY == windowCenterY) return 0;

	// Calculate the distance the mouse has covered since last time
	int _deltaX, _deltaY;

	// If we're in full screen and lower render resolution than the native resolution,
	// the window center is not the same as the actual screen center because the image is being stretched
	// but the mouse behaves as if it's on the native resolution.
	if (settings->fullscreen)
	{
		_deltaX = _mouseX - monitorCenterX; // <- so we use monitor center here
		_deltaY = _mouseY - monitorCenterY;
	}

	// not full screen
	else
	{
		_deltaX = _mouseX - windowCenterX; // <- and window center here
		_deltaY = _mouseY - windowCenterY;
	}

	// If either DeltaX or DeltaY is not 0
	if (_deltaX != 0 || _deltaY != 0)
	{
		// Move the camera
		Move(_deltaX, _deltaY);

		// Return the cursor to the center of the screen
		SetCursorPos(monitorCenterX, monitorCenterY);
	}

	return 1;
}


int Camera::CalculateMotionBlur(float _deltaX, float _deltaY)
{
	// Calculate angle
	float _angle = atan2(_deltaX, _deltaY) * (180 / PI);

	// Pass the information along, amount is the average of deltaX and deltaY
	gfx->SetMotionBlur(_angle -90, fabs(_deltaX + _deltaY) / 2);

	return 1;
}


int Camera::ChaseEntity()
{
	Move(
		chasableEntity->GetPosition()->X - virtualCenterX + entityCenterX - cameraPosition.X, 
		chasableEntity->GetPosition()->Y - virtualCenterY + entityCenterY - cameraPosition.Y
	);
	return 1;
}