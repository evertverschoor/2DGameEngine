#ifndef POSITION_H
#define POSITION_H

/// <summary>
/// A position is a simple model that contains X, Y and Z-values.
/// </summary>
class Position
{
public:
	Position();
	Position(double, double, double);
	~Position();

	double X;
	double Y;
	double Z;
};

#endif