#ifndef DIMENSION_H
#define DIMENSION_H

/// <summary>
/// A dimension is a simple model that contains a width and height.
/// </summary>
class Dimension
{
public:
	Dimension(int, int);
	~Dimension();
	int Width;
	int Height;
};

#endif