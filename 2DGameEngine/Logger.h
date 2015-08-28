#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <time.h>
#include "Windows.h"

/// <summary>
/// The Logger can write anything to the log file.
/// </summary>
class Logger
{
public:
	~Logger();

	/// <summary>
	/// Write something to the log file.
	/// </summary>
	int Log(std::string);

	int Log(int);

	int Log(float);

	int Log(double);

	int Log(char);

	int Log(bool);

	int Log(LPSTR);

	int Log(LPCWSTR);

	int Log(WPARAM);

	int Log(clock_t);

	static Logger* Instance();
private:
	Logger() {};
	static Logger* l_instance;
};

#endif