#ifndef POSITION_H
#define POSITION_H

#include "Logger.h"

/// <summary>
/// A position is a simple model that contains X, Y and Z-values.
/// </summary>
class Position
{
public:
	Position();
	Position(int, int, int);
	~Position();

	int X;
	int Y;
	int Z;
};

#endif