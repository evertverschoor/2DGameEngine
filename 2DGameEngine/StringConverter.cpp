#include "StringConverter.h"


StringConverter* StringConverter::c_instance = NULL;


StringConverter::~StringConverter()
{
}


std::wstring StringConverter::StringToWstring(std::string _string)
{
	int len;
	int slength = (int)_string.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, _string.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, _string.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

std::string StringConverter::FloatToString(float _float)
{
	return std::to_string(_float);
}

std::wstring StringConverter::FloatToWstring(float _float)
{
	return StringToWstring(std::to_string(_float));
}

std::wstring StringConverter::IntToWString(int _int)
{
	return std::to_wstring(_int);
}

StringConverter* StringConverter::Instance()
{
	if (!c_instance)
	{
		c_instance = new StringConverter();
	}
	return c_instance;
}

Position* StringConverter::StringToPosition(std::string _string)
{
	int _positions[3];
	std::string _delimiter = ",";

	int i = 0;
	size_t pos = 0;
	std::string token;
	while ((pos = _string.find(_delimiter)) != std::string::npos) {
		token = _string.substr(0, pos);
		_positions[i] = std::stoi(token);
		++i;
		_string.erase(0, pos + _delimiter.length());
	}

	return new Position(_positions[0], _positions[1], _positions[2]);
}


bool StringConverter::StringToBoolean(std::string _string)
{
	return (_string == "1") ? true : false;
}


int StringConverter::StringToInt(std::string _string)
{
	return std::stoi(_string);
}