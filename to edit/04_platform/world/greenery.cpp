#include "greenery.h"
#include <time.h>
#include <cstdlib>
#include <fstream>

Plant::Plant()
{
	startX = endX = 0;
	startY = endY = 0;
	chance = 0;
	bg = true;
}

Plant::~Plant()
{
	blocks.clear();
	startX = endX = 0;
	startY = endY = 0;
	chance = 0;
	bg = true;
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





Greenery::Greenery()
{
	min = 0;
}

Greenery::~Greenery()
{
	free();
}

void Greenery::free()
{
	min = 0;
	plants.clear();
	blocks.clear();
	sprites.clear();
}

	
void Greenery::load( int type )
{
	free();
	
	sf::Uint8 max;
	if( type == 0 )
	{
		min = 16;
		max = 29 +1;
	}
	else if( type == 1 )
	{
		min = 18;
		max = 30 +1;
	}
	else if( type == 2 )
	{
		min = 18;
		max = 27 +1;
	}
	else if( type == 3 )
	{
		min = 16;
		max = 29 +1;
	}
	
	for( sf::Uint8 i = 0; i < max-min; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ sprites.size() -1 ]->setName( "greenery-sprites[ " +to_string( i+min ) +"]" );
		sprites[ sprites.size() -1 ]->load( "data/sprites/play/" +to_string( type )
		+ "/" +to_string( i+min ) + ".png" );
	}
	
	
	fstream file;
	file.open( "data/txt/greenery/" +to_string( type ) +".txt" );
	if( file.bad() )
	{
		printf( "Can not open file: %s\n", ("data/txt/greenery/" +to_string( type ) +".txt").c_str() );
	}
	else
	{
		// sf::Uint8 nr;
		// int startX, endX;
		// int startY, endY;
		vector <int> block_types;
		
		string line;
		while( getline( file, line ) )
		{
			block_types.clear();
			
			// nr
			string l = "";
			for( unsigned i = 0; i < line.size(); i++ )
			{
				if( line[ i ] == ' ' )
				{
					block_types.push_back( strToInt( l ) );
					l = "";
				}
				else
				{
					l += line[ i ];
				}
			}
			
			plants.push_back( new Plant() );
			
			plants[ plants.size() -1 ]->nr = block_types[ 0 ];
			plants[ plants.size() -1 ]->startX = block_types[ 1 ];
			plants[ plants.size() -1 ]->endX = block_types[ 2 ];
			plants[ plants.size() -1 ]->startY = block_types[ 3 ];
			plants[ plants.size() -1 ]->endY = block_types[ 4 ];
			plants[ plants.size() -1 ]->bg = block_types[ 5 ];
			plants[ plants.size() -1 ]->chance = block_types[ 6 ];
			
			for( unsigned i = 7; i < block_types.size(); i++ )
			{
				plants[ plants.size() -1 ]->add( block_types[ i ] );
			}
		}
	}
	
	// test
	/*
	for( unsigned i = 0; i < plants.size(); i++ )
	{
		printf( "%d %d %d %d %d %d ", plants[ i ]->nr, plants[ i ]->startX, plants[ i ]->endX,
		plants[ i ]->startY, plants[ i ]->endY, plants[ i ]->chance );
		
		for( unsigned j = 0; j < plants[ i ]->getSize(); j++ )
		{
			printf( "%d ", plants[ i ]->getBlocksNr( j ) );
		}
		
		printf( "\n" );
	}
	*/
}

void Greenery::drawBG( sf::RenderWindow* &window, int screen_w )
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->bg )
		{
			if( blocks[ i ]->x > -screen_w/2 && blocks[ i ]->x < screen_w )
			{
				sprites[ blocks[ i ]->nr -min ]->setPosition( blocks[ i ]->x, blocks[ i ]->y );
				window->draw( sprites[ blocks[ i ]->nr -min ]->get() );
			}
		}
	}
}

void Greenery::draw( sf::RenderWindow* &window, int screen_w )
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( !blocks[ i ]->bg )
		{
			if( blocks[ i ]->x > -screen_w/2 && blocks[ i ]->x < screen_w )
			{
				sprites[ blocks[ i ]->nr -min ]->setPosition( blocks[ i ]->x, blocks[ i ]->y );
				window->draw( sprites[ blocks[ i ]->nr -min ]->get() );
			}
		}
	}
}

	
void Greenery::fadein( int v, int max )
{
	for( sf::Uint8 i = 0; i < sprites.size(); i++ )
	{
		sprites[ i ]->fadein( v, max );
	}
}

void Greenery::fadeout( int v, int min )
{
	for( sf::Uint8 i = 0; i < sprites.size(); i++ )
	{
		sprites[ i ]->fadeout( v, min );
	}
}

int Greenery::strToInt(string s)
{
    bool m=false;
    int tmp=0;
    unsigned i=0;
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

unsigned Greenery::getDistance( int v1, int v2 )
{
	int v = v1 -v2;
	
	if( v < 0 )
	{
		v = -v;
	}
		
	return v;
}

void Greenery::positioning( vector < Block* > blocks )
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		bool success = false;
		for( unsigned j = 0; j < plants.size(); j++ )
		{
			if( plants[ j ]->available( blocks[ i ]->nr ) )
			{
				success = true;
				break;
			}
		}
		
		if( success )
		{
			int t = 4;
			while( t-- )
			{
				int random = rand()%plants.size();
				
				if( plants[ random ]->available( blocks[ i ]->nr ) )
				{
					if( rand()%100 < plants[ random ]->chance )
					{
						this->blocks.push_back( new Gre_block() );
					
						this->blocks[ this->blocks.size() -1 ]->nr = plants[ random ]->nr;
						
						int distance = rand()%getDistance( plants[ random ]->startX, plants[ random ]->endX );
						this->blocks[ this->blocks.size() -1 ]->x = plants[ random ]->startX +distance +blocks[ i ]->x;
						
						distance = rand()%getDistance( plants[ random ]->startY, plants[ random ]->endY );
						this->blocks[ this->blocks.size() -1 ]->y = plants[ random ]->startY +distance +blocks[ i ]->y;
						this->blocks[ this->blocks.size() -1 ]->y -= sprites[ this->blocks[ this->blocks.size() -1 ]->nr -min ]->getHeight();
						
						this->blocks[ this->blocks.size() -1 ]->bg = plants[ random ]->bg;
					}
				}
			}
		}
	}
}

void Greenery::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			blocks[ i ]->x += vel;
		}
	}
	else if( direction == 2 )
	{
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			blocks[ i ]->x -= vel;
		}
	}
}

int Greenery::backToGrass( int add )
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		blocks[ i ]->x += add;
	}
	
	return add;
}