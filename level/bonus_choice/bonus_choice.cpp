/**
    bonus_choice.h
    Purpose: class Bonus_choice - choose additional world.

    @author Adrian Michalek
    @version 2017.04.29
	@email adrmic98@gmail.com
*/

#include "bonus_choice.h"
#include "file/file.h"

Bonus_choice::Bonus_choice()
{
	result = -1;
	
	range = 0;
	keep = false;
}

Bonus_choice::~Bonus_choice()
{
	free();
}

void Bonus_choice::free()
{
	if( !unlocked.empty() )
	{
		unlocked.clear();
	}
	
	if( !world.empty() )
	{
		for( auto &it :world )
		{
			it->free();
		}
		
		world.clear();
	}

	result = -1;
	
	range = 0;
	keep = false;
	
	click.free();
}



void Bonus_choice::load()
{
	free();
	
	for( int i = 0; i < 5; i ++ )
	{
		world.push_back( new MySprite() );
		world[ i ]->setName( "bonus_choice-world[ " + con::itos( i ) + " ]" );
		world[ i ]->load( "data/level/w" + con::itos( i ) + ".png", 2 );
		world[ i ]->setScale( 0.8, 0.8 );
		// printf( "%d\n", i );
	}
	
	click.setID( "choice-click" );
	click.load( "data/menu/click.wav", 50 );
}

void Bonus_choice::handle( sf::Event &event )
{
	if( world[ 0 ]->getAlpha() == 0xFF )
	{
		int x, y;
		
		for( auto &it :world )
		{
			it->setOffset( 0 );
		}

		if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
			
			for( unsigned i = 0; i < world.size(); i++ )
			{
				if( unlocked[ i ] )
				{
					if( world[ i ]->checkCollision( x, y ) )
					{
						world[ i ]->setOffset( 1 );
						break;
					}
					else
					{
						focus = false;
					}
				}
			}
		}

		if( event.type == sf::Event::MouseButtonPressed )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
			
			for( unsigned i = 0; i < world.size(); i++ )
			{
				if( unlocked[ i ] )
				{
					if( world[ i ]->checkCollision( x, y ) )
					{
						world[ i ]->setOffset( 1 );
						result = i;
						
						if( play )
						{
							click.play();
						}
						focus = true;
						
						break;
					}
				}
			}
		}
			
		if( event.type == sf::Event::MouseButtonReleased )
		{
			focus = false;
		}
	}
}

void Bonus_choice::draw( sf::RenderWindow &window )
{
	for( auto &it :world )
	{
		window.draw( it->get() );
	}
}



void Bonus_choice::fadein( int j, int max )
{
	for( auto &it :world )
	{
		it->fadein( j, max );
	}
}

void Bonus_choice::fadeout( int j, int min )
{
	for( auto &it :world )
	{
		it->fadeout( j, min );
	}
}



int Bonus_choice::getResult()
{
	return result;
}

bool Bonus_choice::isChosen()
{
	if( result != -1 )
	{
		return true;
	}
	
	return false;
}



void Bonus_choice::reset( float x, float y, float w )
{
	if( !unlocked.empty() )
	{
		unlocked.clear();
	}
	
	// load unlocked worlds
	MyFile file;
	file.load( "data/txt/world/bonus.txt" );
	if( file.is_good() )
	{
		string line;
		while( file.get() >> line )
		{
			// printf( "%d\n", con::stoi( line ) );
			unlocked.push_back( static_cast <bool> (con::stoi( line )) );
		}
		
		// printf( "unlocked size = %d\n", unlocked.size() );
	}
	file.free();
	
	result = -1;
	
	for( unsigned i = 0; i < world.size(); i++ )
	{
		world[ i ]->setPosition( (x +w/2) +(w +40)*i +world[ i ]->getWidth()/2, y +5 );
	}
	
	range = 0;
	keep = false;
}

bool Bonus_choice::move( int vel, int scope )
{
	if( vel < 0 )
	{
		if( range > scope )
		{
			keep = true;
		}
	}
	else if( vel > 0 )
	{
		if( range < scope )
		{
			keep = true;
		}
	}
	
	if( keep )
	{
		range += vel;
		
		for( auto &it :world )
		{
			it->setPosition( it->getX() +vel, it->getY() );
		}
	}
	else
	{
		range = scope;
	}
	
	if( range == scope )
	{
		return true;
	}
	
	return false;
}