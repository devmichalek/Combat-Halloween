#include "own/file.h"
#include <stdio.h>
#include <sstream>

MyFile::MyFile()
{
	file = NULL;
}

MyFile::~MyFile()
{
	free();
}

void MyFile::free()
{
	if( file != NULL )
	{
		if( file->is_open() )
		{
			file->close();
		}
		
		delete file;
		file = NULL;
	}
}

void MyFile::load( string path, ios_base::openmode mode )
{
	free();
	
	file = new fstream;
	file->open( path, mode );
	
	if( !file->good() )
	{
		printf( "Something went wrong with file from %s\n", path.c_str() );
		free();
	}
}

bool MyFile::is_good()
{
	if( file == NULL )
	{
		return false;
	}
	else if( !file->is_open() )
	{
		return false;
	}
	
	return true;
}

fstream& MyFile::get()
{
	return *file;
}



// other
int con::stoi( string str )
{
	/*
	bool m = false;
	int tmp = 0;
	unsigned i = 0;
	
	
	if( str[ 0 ] == '-' )
	{
		i++;
		m = true;
	}
	
	while( i < str.size() )
	{
		tmp = 10 *tmp +str[ i ] -48;
		i++;
    }
	*/
	
    return std::stoi( str );   
}

float con::stof( string str )
{
	const char* s = str.c_str();
	
	float rez = 0, fact = 1;
	
	if( *s == '-' )
	{
		s++;
		fact = -1;
	}
	
	for( int point_seen = 0; *s; s++ )
	{
		if( *s == '.' )
		{
			point_seen = 1; 
			continue;
		}
		
		int d = *s - '0';
		
		if( d >= 0 && d <= 9 )
		{
			if( point_seen )
			{
				fact /= 10.0f;
			}
				
			rez = rez * 10.0f + static_cast <float> (d);
		}
	}

	return rez *fact;
};

string con::itos( int n )
{
	string tmp;
	 
	if( n < 0 )
	{
		tmp = "-";
		n = -n;
	}
	
	if( n > 9 )
	{
		tmp += itos( n / 10 );
	}
	
	tmp += n % 10 + 48;
	return tmp;
}

string con::ftos( float n )
{
    std::ostringstream b;
	
    b << n;
	
    return b.str();   
}