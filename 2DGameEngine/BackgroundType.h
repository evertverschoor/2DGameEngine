#ifndef BACKGROUNDTYPE_H
#define BACKGROUNDTYPE_H

/// <summary>
/// The way a background behaves.
/// PERSIST means it stays in view.
/// MOVE means it stays at position 0,0 and moves when the camera does.
/// SLOW_MOVE is move but much slower, creating a fake distance effect.
/// </summary>
enum BackgroundType
{
	PERSIST,
	MOVE,
	SLOW_MOVE
};

#endif