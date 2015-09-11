#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <fstream>

/// <summary>
/// Reads any text-based file.
/// </summary>
class FileReader
{
public:
	~FileReader();

	/// <summary>
	/// Read a file and return it as a string.
	/// @param The filename.
	/// </summary>
	std::string ReadFile(std::string);

	/// <summary
	/// Get the singleton instance.
	/// </summary>
	static FileReader* Instance();
private:
	FileReader() {};
	static FileReader* r_instance;
};

#endif