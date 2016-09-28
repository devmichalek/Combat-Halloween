#pragma once

#include <fstream>
#include <string>
#include <vector>

class File
{
	std::fstream file;
	std::string name;
	std::ios_base::openmode flag;
	
	std::vector <std::string> line;
	
public:

	int strToInt( std::string s );

	File();
	~File();
	void free();
	
	void load( std::string path, std::ios_base::openmode flag = std::ios::in );
	void reload();	// set pointers from file on start
	void close();
	
	std::string s( int nr = 0 );
	int i( int nr = 0 );
};