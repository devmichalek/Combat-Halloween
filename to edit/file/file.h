#pragma once

#include <fstream>
#include <string>

using namespace std;

class MyFile
{
	fstream* file;
	
public:
	
	MyFile();
	~MyFile();
	void free();
	
	void load( string path, ios_base::openmode mode = ios::in | ios::out );
	
	bool is_good();
	fstream& get();
};

namespace con
{
	int stoi( string str );
	float stof( const char* s );
	
	string itos( int n );
}