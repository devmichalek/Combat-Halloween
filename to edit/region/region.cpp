#include "region/region.h"
#include <fstream>

Region::Region()
{
	focus = 0;
}

Region::~Region()
{
	free();
}

void Region::free()
{
	picture.free();
	focus = 0;
}

	
void Region::load( string path )
{
	picture.setName( "region-" + path );
	picture.load( path + ".png" );
	
	fstream file; // to set x and y of picture
	file.open( path + ".txt" );
	
	if( file.bad() )
	{
		printf( "Not loaded %s\n", path.c_str() );
	}
	else
	{
		string line;
		
		file >> line;
	}
	
	file.close();
}

void Region::draw( sf::RenderWindow* &window )
{
	
}

void Region::handle( sf::Event &event )
{
	
}

	
void Region::fadein( int v, int max )
{
	picture.fadein( v, max );
}

void Region::fadeout( int v, int min )
{
	picture.fadeout( v, min );
}
