#ifndef GFXCONTROLLER_H
#define GFXCONTROLLER_H

#include "Renderer.h"

/// <summary>
/// The Gfx Controller can be used to activate certain postprocessing effects.
/// </summary>
class GFXController
{
public:
	GFXController(Renderer*);
	~GFXController();

	/// <summary>
	/// Set the current motion blur angle and amount, put 0.0f on amount for no motion blur.
	/// @param1 The motion blur angle, between 0 and 360.
	/// @param2 The motion blur amount.
	/// </summary>
	int SetMotionBlur(float, float);
private:
	Renderer* gameRenderer;
};

#endif