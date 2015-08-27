#ifndef STRINGCONVERTER_H
#define STRINGCONVERTER_H

#include <string>
#include "windows.h"

class StringConverter
{
public:
	~StringConverter();

	std::wstring StringToWstring(std::string);

	static StringConverter* Instance();
private:
	StringConverter() {};
	static StringConverter* c_instance;
};

#endif