#include "greenery.h"
#include <cstdlib>
#include "file/file.h"


Greenery::Greenery()
{
	width = 0;
	screen_w = 0;
	min = 0;
}

Greenery::~Greenery()
{
	free();
}

void Greenery::free()
{
	width = 0;
	screen_w = 0;
	min = 0;
	
	if( !plants.empty() )
	{
		for( auto &i :plants )
		{
			i->free();
		}
		
		plants.clear();
	}
	
	if( !blocks.empty() )
	{
		for( auto &i :blocks )
		{
			i->free();
		}
		
		blocks.clear();
	}
	
	if( !sprites.empty() )
	{
		for( auto &i :sprites )
		{
			i->free();
		}
		
		sprites.clear();
	}
}

void Greenery::reset( int distance )
{
	while( true )
	{
		if( distance > 0 )
		{
			for( auto &it :blocks )
			{
				it->x ++;
			}
			
			distance --;
		}
		else
		{
			break;
		}
	}
}



void Greenery::load( int type, int width, int screen_w )
{
	free();
	
	MyFile file;
	file.load( "data/txt/greenery/" +con::itos( type ) +".txt" );
	if( file.is_good() )
	{
		vector <int> types;
		string line;
		sf::Uint8 max;
		
		// set min
		getline( file.get(), line );
		min = con::stoi( line );
		
		// set max
		getline( file.get(), line );
		max = con::stoi( line );
		
		// load sprites
		for( sf::Uint8 i = 0; i < max-min; i++ )
		{
			sprites.push_back( new MySprite() );
			sprites[ sprites.size() -1 ]->setName( "greenery-sprites[ " +con::itos( i+min ) +"]" );
			sprites[ sprites.size() -1 ]->load( "data/04_platform/world/" +con::itos( type )
			+ "/" +con::itos( i+min ) + ".png" );
		}
		
		// load rules
		while( getline( file.get(), line ) )
		{
			types.clear();
			
			// nr
			string l = "";
			for( unsigned i = 0; i < line.size(); i++ )
			{
				if( line[ i ] == ' ' )
				{
					types.push_back( con::stoi( l ) );
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
		
		this->width = width;
		this->screen_w = screen_w;
	}
	
	file.free();
	
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

void Greenery::draw( sf::RenderWindow* &window )
{
	for( auto &it :blocks )
	{
		if( !it->bg )
		{
			if( it->x > -width*3 && it->x < screen_w +width*3 )
			{
				sprites[ it->nr -min ]->setPosition( it->x, it->y );
				window->draw( sprites[ it->nr -min ]->get() );
			}
		}
	}
}

void Greenery::draw_bg( sf::RenderWindow* &window )
{
	for( auto &it :blocks )
	{
		if( it->bg )
		{
			if( it->x > -width*3 && it->x < screen_w )
			{
				sprites[ it->nr -min ]->setPosition( it->x, it->y );
				window->draw( sprites[ it->nr -min ]->get() );
			}
		}
	}
}



void Greenery::fadein( int v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
}

void Greenery::fadeout( int v, int min )
{
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
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

void Greenery::positioning( vector <Block*> blocks )
{
	vector <sf::Uint8> available;
	
	for( auto &it :blocks )
	{
		for( unsigned i = 0; i < plants.size(); i++ )
		{
			if( plants[ i ]->available( it->nr ) )
			{
				available.push_back( i );
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
					this->blocks.push_back( new Green() );
				
					this->blocks[ this->blocks.size() -1 ]->nr = plants[ chosen ]->nr;
					
					int distance = rand()%getDistance( plants[ chosen ]->startX, plants[ chosen ]->endX );
					this->blocks[ this->blocks.size() -1 ]->x = plants[ chosen ]->startX +distance +it->x;
					
					distance = rand()%getDistance( plants[ chosen ]->startY, plants[ chosen ]->endY );
					this->blocks[ this->blocks.size() -1 ]->y = plants[ chosen ]->startY +distance +it->y;
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
		for( auto &it :blocks )
		{
			it->x += vel;
		}
	}
	else if( direction == 2 )
	{
		for( auto &it :blocks )
		{
			it->x -= vel;
		}
	}
}

void Greenery::undoFall( sf::Uint8 add )
{
	for( auto &i :blocks )
	{
		i->x += add;
	}
}

void Greenery::setColor( sf::Color color )
{
	for( auto &i :sprites )
	{
		i->setColor( color );
	}
}