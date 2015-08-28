#include "Logger.h"
#include "Windows.h"
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <stddef.h>


Logger* Logger::l_instance = NULL;


Logger::~Logger()
{
	delete l_instance;
}


int Logger::Log(std::string _text)
{
	std::ofstream outfile;
	outfile.open("Data/Log.txt", std::ios_base::app);
	outfile << _text;
	return 1;
}


int Logger::Log(int _text)
{
	std::ofstream outfile;
	outfile.open("Data/Log.txt", std::ios_base::app);
	outfile << _text;
	return 1;
}


int Logger::Log(float _text)
{
	std::ofstream outfile;
	outfile.open("Data/Log.txt", std::ios_base::app);
	outfile << _text;
	return 1;
}

int Logger::Log(double _text)
{
	std::ofstream outfile;
	outfile.open("Data/Log.txt", std::ios_base::app);
	outfile << _text;
	return 1;
}


int Logger::Log(char _text)
{
	std::ofstream outfile;
	outfile.open("Data/Log.txt", std::ios_base::app);
	outfile << _text;
	return 1;
}


int Logger::Log(bool _bool)
{
	std::string _text = _bool ? "Yes" : "No";
	std::ofstream outfile;
	outfile.open("Data/Log.txt", std::ios_base::app);
	outfile << _text;
	return 1;
}


int Logger::Log(LPSTR _text)
{
	std::ofstream outfile;
	outfile.open("Data/Log.txt", std::ios_base::app);
	outfile << _text;
	return 1;
}


int Logger::Log(LPCWSTR _text)
{
	std::ofstream outfile;
	outfile.open("Data/Log.txt", std::ios_base::app);
	outfile << _text;
	return 1;
}


int Logger::Log(WPARAM _text)
{
	std::ofstream outfile;
	outfile.open("Data/Log.txt", std::ios_base::app);
	outfile << _text;
	return 1;
}

int Logger::Log(clock_t _text)
{
	std::ofstream outfile;
	outfile.open("Data/Log.txt", std::ios_base::app);
	outfile << _text;
	return 1;
}


Logger* Logger::Instance()
{
	if (!l_instance)
	{
		l_instance = new Logger();
	}
	return l_instance;
}