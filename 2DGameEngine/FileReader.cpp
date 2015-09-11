#include "FileReader.h"


FileReader* FileReader::r_instance = NULL;


FileReader::~FileReader()
{
}


std::string FileReader::ReadFile(std::string _fileName)
{
	char _lines[80][80];
	int _linecounter = 0;

	std::ifstream _file;
	_file.open(_fileName, std::ios_base::app);

	if (!_file) return 0;
	
	while (!_file.eof())
	{
		_file >> _lines[_linecounter];
		++_linecounter;
	}

	std::string _fileString;
	for (int i = 0; i < _linecounter; i++)
	{
		_fileString += _lines[i];
	}

	return _fileString;
}


FileReader* FileReader::Instance()
{
	if (!r_instance)
	{
		r_instance = new FileReader();
	}
	return r_instance;
}