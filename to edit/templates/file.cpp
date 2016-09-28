#include "templates/file.h"

#include <stdio.h>

int File::strToInt( std::string s )
{
    bool m=false;
    int tmp=0;
    int i=0;
    if(s[0]=='-')
    {
          i++;
          m = true;
    }
	
    while(i<s.size())
    {
      tmp = 10*tmp+s[i]-48;
      i++;
    }
	
    return m ? -tmp : tmp;   
}


File::File()
{
	name = "";
	flag = std::ios::in | std::ios::app | std::ios::out;
}

File::~File()
{
	free();
}

void File::free()
{
	close();
	name = "";
	flag = std::ios::in | std::ios::app | std::ios::out;
	line.clear();
}

void File::load( std::string path, std::ios_base::openmode flag )
{
	close();
	
	file.open( path.c_str(), flag );
	
	if( file.bad() )
	{
		printf( "Can not load %s!\n", path.c_str() );
	}
	else
	{
		name = path;
		this->flag = flag;
		
		
		line.clear();
		std::string str;
		while( file >> str )
		{
			line.push_back( str );
		}
		
		//for( unsigned i = 0; i < line.size(); i++ )
		//{
		//	printf( "nr %d =   %s\n", i, line[ i ].c_str() );
		//}
		
		// printf( "%s\n", type.c_str() );
	}
}

void File::reload()
{
	load( name, flag );
}

void File::close()
{
	if( file.is_open() )
	{
		file.close();
	}
}


std::string File::s( int nr )
{
	return line[ nr ];
}


int File::i( int nr )
{
	return strToInt( line[ nr ] );
}
