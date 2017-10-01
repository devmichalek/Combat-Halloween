#pragma once
#define _GLIBCXX_USE_CXX11_ABI 0
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

// conversion
namespace con
{
	int stoi( string str );
	float stof( string str );
	
	string itos( int n );
	string ftos( float n );
}