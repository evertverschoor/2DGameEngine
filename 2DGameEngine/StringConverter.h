#ifndef STRINGCONVERTER_H
#define STRINGCONVERTER_H

#include <string>
#include "windows.h"
#include "Position.h"

class StringConverter
{
public:
	~StringConverter();

	std::wstring StringToWstring(std::string);
	std::string FloatToString(float);
	std::wstring FloatToWstring(float);
	std::wstring IntToWString(int);
	Position* StringToPosition(std::string);
	bool StringToBoolean(std::string);
	int StringToInt(std::string);

	static StringConverter* Instance();
private:
	StringConverter() {};
	static StringConverter* c_instance;
};

#endif