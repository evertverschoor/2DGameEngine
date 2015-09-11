#ifndef LOGGER_H
#define LOGGER_H

#include "Windows.h"
#include <string>
#include <time.h>
#include <fstream>

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

	/// <summary>
	/// Get the instance of the logger using a static call.
	/// </summary>
	static Logger* Instance();
private:
	Logger() {};
	static Logger* l_instance;
};

#endif