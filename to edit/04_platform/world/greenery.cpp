#include "greenery.h"
#include <time.h>
#include <cstdlib>
#include <fstream>


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
	
	if( !plants.empty() )
	{
		for( unsigned i = 0; i < plants.size(); i++ )
		{
			plants[ i ]->free();
		}
		
		plants.clear();
	}
	
	if( !sprites.empty() )
	{
		for( unsigned i = 0; i < sprites.size(); i++ )
		{
			sprites[ i ]->free();
		}
		
		sprites.clear();
	}
	
	if( !blocks.empty() )
	{
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			blocks[ i ]->free();
		}
		
		blocks.clear();
	}
}

	
void Greenery::load( int type )
{
	free();
	
	fstream file;
	file.open( "data/txt/greenery/" +to_string( type ) +".txt" );
	if( file.bad() )
	{
		printf( "Can not open file: %s\n", ("data/txt/greenery/" +to_string( type ) +".txt").c_str() );
	}
	else
	{
		vector <int> types;
		string line;
		sf::Uint8 max;
		
		// set min
		getline( file, line );
		min = to_int( line );
		
		// set max
		getline( file, line );
		max = to_int( line );
		
		// load sprites
		for( sf::Uint8 i = 0; i < max-min; i++ )
		{
			sprites.push_back( new MySprite() );
			sprites[ sprites.size() -1 ]->setName( "greenery-sprites[ " +to_string( i+min ) +"]" );
			sprites[ sprites.size() -1 ]->load( "data/sprites/play/" +to_string( type )
			+ "/" +to_string( i+min ) + ".png" );
		}
		
		// load rules
		while( getline( file, line ) )
		{
			types.clear();
			
			// nr
			string l = "";
			for( unsigned i = 0; i < line.size(); i++ )
			{
				if( line[ i ] == ' ' )
				{
					types.push_back( to_int( l ) );
					l = "";
				}
				else
				{
					l += line[ i ];
				}
			}
			
			plants.push_back( new Plant() );
			
			plants[ plants.size() -1 ]->nr = 		types[ 0 ];
			plants[ plants.size() -1 ]->startX = 	types[ 1 ];
			plants[ plants.size() -1 ]->endX = 		types[ 2 ];
			plants[ plants.size() -1 ]->startY = 	types[ 3 ];
			plants[ plants.size() -1 ]->endY = 		types[ 4 ];
			plants[ plants.size() -1 ]->bg = 		types[ 5 ];
			plants[ plants.size() -1 ]->chance = 	types[ 6 ];
			
			for( unsigned i = 7; i < types.size(); i++ )
			{
				plants[ plants.size() -1 ]->add( types[ i ] );
			}
		}
	}
	
	file.close();
	
	// Test.
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




int Greenery::to_int( string s )
{
    bool m = false;
    int tmp = 0;
    unsigned i = 0;
	
    if( s[ 0 ] == '-')
    {
		i++;
		m = true;
    }
	
    while( i < s.size() )
    {
		tmp = 10*tmp +s[ i ] -48;
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
	vector <sf::Uint8> available;
	
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		for( unsigned j = 0; j < plants.size(); j++ )
		{
			if( plants[ j ]->available( blocks[ i ]->nr ) )
			{
				available.push_back( j );
			}
		}
		
		if( available.size() > 0 )
		{
			int t = 4;
			while( t-- )
			{
				int random = rand()%available.size();
				int chosen = available[ random ];
				// printf( "chosen %d\n", chosen );
				
				if( rand()%100 < plants[ chosen ]->chance )
				{
					this->blocks.push_back( new GreenBlock() );
				
					this->blocks[ this->blocks.size() -1 ]->nr = plants[ chosen ]->nr;
					
					int distance = rand()%getDistance( plants[ chosen ]->startX, plants[ chosen ]->endX );
					this->blocks[ this->blocks.size() -1 ]->x = plants[ chosen ]->startX +distance +blocks[ i ]->x;
					
					distance = rand()%getDistance( plants[ chosen ]->startY, plants[ chosen ]->endY );
					this->blocks[ this->blocks.size() -1 ]->y = plants[ chosen ]->startY +distance +blocks[ i ]->y;
					this->blocks[ this->blocks.size() -1 ]->y -= sprites[ this->blocks[ this->blocks.size() -1 ]->nr -min ]->getHeight();
					
					this->blocks[ this->blocks.size() -1 ]->bg = plants[ chosen ]->bg;
				}
			}
		}
		
		if( !available.empty() )
		{
			available.clear();
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

void Greenery::backToGrass( int add )
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		blocks[ i ]->x += add;
	}
}