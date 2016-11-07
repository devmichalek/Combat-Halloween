#include "region/region.h"

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
	
}

void Region::draw( sf::RenderWindow* &window )
{
	
}

void Region::handle( sf::Event &event )
{
	
}

	
void Region::fadein( int v = 1, int max = 255 )
{
	
}

void Region::fadeout( int v = 1, int min = 0 )
{
	
}
