#include "vegetation.h"

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

void Plant::setX( int startX, int endX )
{
	this->startX = startX;
	this->endX = endX;
}

void Plant::setY( int startY, int endY )
{
	this->startY = startY;
	this->endY = endY;
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

int Plant::getX()
{
	return rand()%startX +endX;
}

int Plant::getY()
{
	return rand()%startY +endY;
}



Vegetation::Vegetation()
{
	world_type = -1;
	min = max = 0;
}

Vegetation::~Vegetation()
{
	free();
}

void Vegetation::free()
{
	world_type = -1;
	min = max = 0;
	plants.clear();
}

	
void Vegetation::load( int type, vector < Block* > blocks )
{
	free();
	
	Plant* plant = new Plant;
	
	world_type = type;
	
	if( type == 1 )
	{
		min = 18;
		max = 30;
		
		for( int i = 0; i <= 7; i++ )
		{
			plant->add( i );
		}
		
		// crank
		// blocks.push_back( )
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

