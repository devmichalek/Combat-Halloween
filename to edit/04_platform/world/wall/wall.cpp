#include "wall.h"
#include <time.h>
#include <cstdlib>


Wall::Wall()
{
	min = 0;
	width = 0;
	screen_w = 0;
}

Wall::~Wall()
{
	free();
}

void Wall::free()
{
	min = 0;
	width = 0;
	screen_w = 0;
	
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

void Wall::reset( int distance )
{
	while( true )
	{
		if( distance > 0 )
		{
			for( auto &it :blocks )
			{
				it->moveX( 1 );
			}
			
			distance --;
		}
		else
		{
			break;
		}
	}
}


void Wall::load( int type, int width, int screen_w )
{
	free();
	
	min = 8;
	this->width = width;
	this->screen_w = screen_w;
	
	for( int i = 0; i < 5; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ i ]->setName( "wall-sprites[" +to_string( i ) +"]" );
		sprites[ i ]->load( "data/sprites/play/" +to_string( type ) +"/" +to_string( i +min ) +".png" );
	}
	
	sprites.push_back( new MySprite() );
	sprites[ sprites.size()-1 ]->setName( "wall-sprites[5]" );
	sprites[ sprites.size()-1 ]->load( "data/sprites/play/" +to_string( type ) +"/15.png" );
}

void Wall::draw( sf::RenderWindow* &window )
{
	for( auto &it :blocks )
	{
		it->moving( width );
		
		for( unsigned j = 0; j < it->getSize(); j++ )
		{
			if( it->getX(j) > -width*2 && it->getX(j) < screen_w +width*2 )
			{
				sprites[ it->getNr(j) ]->setPosition( it->getX(j), it->getY(j) );
				window->draw( sprites[ it->getNr(j) ]->get() );
			}
		}
	}
}


void Wall::fadein( int v, int max )
{
	for( auto &i :sprites )
	{
		i->fadein( v, max );
	}
}

void Wall::fadeout( int v, int min )
{
	for( auto &i :sprites )
	{
		i->fadeout( v, min );
	}
}




void Wall::positioning( vector <Block*> blocks, int chance )
{
	for( unsigned i = 0; i < blocks.size() -2; i++ )
	{
		if( blocks[ i ]->y <= 3*width && blocks[ i ]->x > screen_w )
		{
			if( (blocks[ i ]->nr == 1 || blocks[ i ]->nr == 6 || blocks[ i ]->nr == 5 || blocks[ i ]->nr == 0) &&
				blocks[ i ]->y == blocks[ i +2 ]->y )
			{
				if( rand()%100 < chance )
				{
					int nr = 0;
					if( rand()%2 == 0 )
					{
						nr = 1;
					}
					
					this->blocks.push_back( new Pug() );
					this->blocks[ this->blocks.size()-1 ]->positioning( width, nr );
					
					int vel = 1;
					
					if( nr == 1 )
					{
						if( rand()%2 == 1 )	vel = 4;
						else				vel = 3;
					}
					else if( rand()%2 == 1 ) vel = 2;
					
					if( vel > 1 )
					{
						this->blocks[ this->blocks.size()-1 ]->setPosition( blocks[ i ]->x, blocks[ i ]->y -width, vel, width );
					}
					else
					{
						this->blocks[ this->blocks.size()-1 ]->setPosition( blocks[ i ]->x, blocks[ i ]->y -width, vel );
					}
					
					i += 3;
				}
			}
		}
	}
}



void Wall::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		for( auto &it :blocks )
		{
			it->moveX( vel );
		}
	}
	else if( direction == 2 )
	{
		for( auto &it :blocks )
		{
			it->moveX( -vel );
		}
	}
}

void Wall::undoFall( sf::Uint8 add )
{
	for( auto &it :blocks )
	{
		it->moveX( add );
	}
}

void Wall::setColor( sf::Color color )
{
	for( auto &i :sprites )
	{
		i->setColor( color );
	}
}



bool Wall::harm( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &it :blocks )
		{
			if( it->harm( width ) )
			{
				for( unsigned j = 0; j < it->getSize(); j++ )
				{
					if( it->getX(j) > -width*2 && it->getX(j) < screen_w +width*2 )
					{
						if( it->getNr(j) < 10 )
						{
							
							sprites[ it->getNr(j) ]->setPosition( it->getX(j), it->getY(j) );
							if( sprites[ it->getNr(j) ]->checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
							{
								return true;
							}
						}
					}
				}
			}
		}
	}
	
	return false;
}

bool Wall::checkCollision( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &it :blocks )
		{
			for( unsigned j = 0; j < it->getSize(); j++ )
			{
				if( it->getX(j) > -width*2 && it->getX(j) < screen_w +width*2 )
				{
					sprites[ it->getNr(j) ]->setPosition( it->getX(j), it->getY(j) );
					if( sprites[ it->getNr(j) ]->checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
					{
						return true;
					}
				}
			}
		}
	}
	
	return false;
}