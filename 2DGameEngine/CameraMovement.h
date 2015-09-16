#ifndef CAMERAMOVEMENT_H
#define CAMERAMOVEMENT_H

/// <summary>
/// Contains ways to move the camera around.
/// </summary>
enum CameraMovement
{
	/// <summary>
	/// Move the mouse or the XInput right stick to move the camera.
	/// </summary>
	NORMAL,

	/// <summary>
	/// Follow an entity in the active scene with the camera.
	/// </summary>
	ENTITY_CHASE
};

#endif