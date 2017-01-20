#include "vegetation.h"
#include <time.h>
#include <cstdlib>
#include <fstream>

Plant::Plant()
{
	startX = endX = 0;
	startY = endY = 0;
}

Plant::~Plant()
{
	blocks.clear();
	startX = endX = 0;
	startY = endY = 0;
}

void Plant::clear()
{
	blocks.clear();
}

void Plant::add( sf::Uint8 block )
{
	blocks.push_back( block );
}


	
bool Plant::available( sf::Uint8 block )
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( block == blocks[ i ] )
		{
			return true;
		}
	}
	
	return false;
}

unsigned Plant::getSize()
{
	return blocks.size();
}

sf::Uint8 Plant::getBlocksNr( sf::Uint8 n )
{
	return blocks[ n ];
}



Vegetation::Vegetation()
{
	min = 0;
}

Vegetation::~Vegetation()
{
	free();
}

void Vegetation::free()
{
	min = 0;
	plants.clear();
	blocks.clear();
	sprites.clear();
}

	
void Vegetation::load( int type, vector < Block* > blocks )
{
	free();
	
	int how_many = 0;
	
	if( type == 1 )
	{
		min = 16;
		
	}
}

void Vegetation::draw( sf::RenderWindow* &window )
{
	
}

	
void Vegetation::fadein( int v, int max )
{
	
}

void Vegetation::fadeout( int v, int min )
{
	
}

