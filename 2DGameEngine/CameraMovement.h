#ifndef CAMERAMOVEMENT_H
#define CAMERAMOVEMENT_H

/// <summary>
/// Contains ways to move the camera around.
/// </summary>
enum CameraMovement
{
	/// <summary>
	/// Move the mouse towards the edges of the screen to move the camera.
	/// </summary>
	EDGE_PAN,

	/// <summary>
	/// Move the mouse or the XInput left stick to move the camera.
	/// </summary>
	NORMAL,

	/// <summary>
	/// Follow an entity in the active scene with the camera.
	/// </summary>
	ENTITY_CHASE
};

#endif