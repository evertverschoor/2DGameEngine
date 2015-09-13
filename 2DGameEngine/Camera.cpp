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
	SetCameraMovement(CameraMovement::MOUSE_MOVE);

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
	if (_x >= 0 && _x <= sceneSize->width - virtualResolution->width) cameraPosition.X = _x;
	if (_y >= 0 && _y <= sceneSize->height - virtualResolution->height) cameraPosition.Y = _y;

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
	return 1;
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
		case MOUSE_MOVE: 
			MoveCameraMouseMove(_mouseX, _mouseY); 
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


int Camera::MoveCameraMouseMove(int _mouseX, int _mouseY)
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

	/*Logger::Instance()->Log("\nMouseX: ");
	Logger::Instance()->Log(_mouseX);
	Logger::Instance()->Log("\nMouseY: ");
	Logger::Instance()->Log(_mouseY);*/

	// Replace the camera based on that distance
	JumpTo(cameraPosition.X + _deltaX, cameraPosition.Y + _deltaY);

	// Calculate motion blur based on this information, if turned on
	if (settings->motionBlur) CalculateMotionBlur(_deltaX, _deltaY);

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