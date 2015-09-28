#ifndef CAMERAREMOTE_H
#define CAMERAREMOTE_H

/// <summary>
/// The camera remote allows objects to control the camera without the need of user input.
/// </summary>
class CameraRemote
{
public:
	virtual ~CameraRemote() { };

	/// <summary>
	/// Move the camera certain values in X and Y direction.
	/// @param1 How far the camera moves in direction X.
	/// @param2 How far the camera moves in direction Y.
	/// </summary>
	virtual int RemoteMove(int, int) = 0;
};

#endif