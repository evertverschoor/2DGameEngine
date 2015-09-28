#ifndef GFXCONTROLLER_H
#define GFXCONTROLLER_H

/// <summary>
/// The Gfx Controller can be used to activate certain postprocessing effects.
/// </summary>
class GFXController
{
public:
	GFXController();
	~GFXController();

	/// <summary>
	/// Set motion blur state, only if it's turned on by the user in the video settings.
	/// </summary>
	int SetMotionBlur(bool);

	/// <summary>
	/// Returns whether or not motion blur should happen now.
	/// </summary>
	bool MotionBlurOn();
private:
	bool motionBlurToggle;
};

#endif