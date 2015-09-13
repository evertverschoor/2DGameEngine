#include "Camera.h"


Camera::Camera(int _gamepadno, Dimension* _virtualResolution, GFXController* _gfx, VideoSettings* _settings)
{
	gamepadNumber = _gamepadno;
	virtualResolution = _virtualResolution;
	gfx = _gfx;
	settings = _settings;
	
	cameraPosition.X = 0;
	cameraPosition.Y = 0;

	// Default camera movement mode is MOUSE_MOVE
	SetCameraMovement(CameraMovement::NORMAL);

	lastMouseX = NULL;
	lastMouseY = NULL;

	monitorCenterX = settings->monitorRes->width / 2;
	monitorCenterY = settings->monitorRes->height / 2;

	windowCenterX = settings->screenRes->width / 2;
	windowCenterY = settings->screenRes->height / 2;

	Logger::Instance()->Log("\nWindowCenterX: ");
	Logger::Instance()->Log(windowCenterX);
	Logger::Instance()->Log("\nWindowCenterY: ");
	Logger::Instance()->Log(windowCenterY);
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
	if (settings->motionBlur) CalculateMotionBlur(_newPosX - cameraPosition.X, _newPosY - cameraPosition.Y);

	// Make the jump
	JumpTo(_newPosX, _newPosY);

	return 1;
}


Position* Camera::GetPosition()
{
	return &cameraPosition;
}


int Camera::SetCameraMovement(CameraMovement _value)
{
	movement = _value;
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
	// Initialize the move amounts, depending on what direction(s) the stick is facing
	int _moveX = 0;
	int _moveY = 0;

	if (_state->RightStickDirection(GAMEPADSTATE_RIGHT))
	{
		_moveX += 50;
	}
	if (_state->RightStickDirection(GAMEPADSTATE_LEFT))
	{
		_moveX -= 50;
	}
	if (_state->RightStickDirection(GAMEPADSTATE_UP))
	{
		_moveY -= 50;
	}
	if (_state->RightStickDirection(GAMEPADSTATE_DOWN))
	{
		_moveY += 50;
	}

	Move(_moveX, _moveY);

	return 0;
}


int Camera::HandleKeyboardInput(KeyboardState* _state)
{
	return 1;
}


int Camera::HandleMouseInput(MouseState*_state )
{
	// Save the current mouse positions
	int _mouseX = _state->GetCursorPosition()->X;
	int _mouseY = _state->GetCursorPosition()->Y;

	// Set the last mouse positions for the first time
	if (NULL == lastMouseX)
	{
		lastMouseX = _mouseX;
		lastMouseY = _mouseY;
	}

	// See if the camera needs to be moved based on the movement method
	switch (movement)
	{
		case NORMAL: 
			MoveCameraNormal(_mouseX, _mouseY); 
			break;
		case EDGE_PAN: 
			MoveCameraEdgePan(_mouseX, _mouseY); 
			break;
	}

	// Update the last mouse positions with current ones
	lastMouseX = _mouseX;
	lastMouseY = _mouseY;

	return 1;
}


int Camera::MoveCameraNormal(int _mouseX, int _mouseY)
{
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

	// Move the camera in deltaX and deltaY direction
	Move(_deltaX, _deltaY);

	// Return the cursor to the center of the screen
	SetCursorPos(monitorCenterX, monitorCenterY);

	return 1;
}


int Camera::MoveCameraEdgePan(int _mouseX, int _mouseY)
{
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