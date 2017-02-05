#include "plant.h"

Plant::Plant()
{
	nr = -1;
	bg = true;
	chance = 0;
	startX = endX = 0;
	startY = endY = 0;
}

Plant::~Plant()
{
	free();
}

void Plant::free()
{
	if( !blocks.empty() )
	{
		blocks.clear();
	}
	
	nr = -1;
	bg = true;
	chance = 0;
	startX = endX = 0;
	startY = endY = 0;
}

unsigned Plant::getSize()
{
	return blocks.size();
}

void Plant::add( sf::Uint8 block )
{
	blocks.push_back( block );
}

bool Plant::available( sf::Uint8 block )
{
	for( auto &it :blocks )
	{
		if( block == it )
		{
			return true;
		}
	}
	
	return false;
}

