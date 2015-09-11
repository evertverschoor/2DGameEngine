#ifndef STRINGCONVERTER_H
#define STRINGCONVERTER_H

#include <string>
#include "windows.h"
#include "Position.h"

/// <summary>
/// The string converter can be called on statically to handle any complicated string conversions.
/// </summary>
class StringConverter
{
public:
	~StringConverter();

	/// <summary>
	/// Convert a wstring to a string.
	/// </summary>
	std::wstring StringToWstring(std::string);

	/// <summary>
	/// Convert a float to a string.
	/// </summary>
	std::string FloatToString(float);

	/// <summary>
	/// Convert a float to a wstring.
	/// </summary>
	std::wstring FloatToWstring(float);

	/// <summary>
	/// Convert an int to a wstring.
	/// </summary>
	std::wstring IntToWString(int);

	/// <summary>
	/// Convert a string to a position.
	/// </summary>
	Position* StringToPosition(std::string);

	/// <summary>
	/// Convert a string to a boolean.
	/// </summary>
	bool StringToBoolean(std::string);

	/// <summary>
	/// Convert a string to an int.
	/// </summary>
	int StringToInt(std::string);

	/// <summary>
	/// Get the instance of the string converter using a static call.
	/// </summary>
	static StringConverter* Instance();
private:
	StringConverter() {};
	static StringConverter* c_instance;
};

#endif