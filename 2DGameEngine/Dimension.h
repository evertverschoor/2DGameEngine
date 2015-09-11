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

	/// <summary>
	/// The width of the dimension.
	/// </summary>
	int width;

	/// <summary>
	/// The height of the dimension.
	/// </summary>
	int height;
};

#endif