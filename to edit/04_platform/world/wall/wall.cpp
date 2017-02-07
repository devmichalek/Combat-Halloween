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
	
	for( int i = 0; i < 4; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ i ]->setName( "wall-sprites[" +to_string( i ) +"]" );
	}
	
	sprites[ 0 ]->load( "data/sprites/play/" +to_string( type ) +"/8.png" );
	sprites[ 1 ]->load( "data/sprites/play/" +to_string( type ) +"/9.png" );
	sprites[ 2 ]->load( "data/sprites/play/" +to_string( type ) +"/10.png" );
	sprites[ 3 ]->load( "data/sprites/play/" +to_string( type ) +"/12.png" );
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
				if( it->getNr(j) == 12 )
				{
					sprites[ sprites.size()-1 ]->setPosition( it->getX(j), it->getY(j) );
					window->draw( sprites[ sprites.size()-1 ]->get() );
				}
				else
				{
					sprites[ it->getNr(j) -8 ]->setPosition( it->getX(j), it->getY(j) );
					window->draw( sprites[ it->getNr(j) -8 ]->get() );
				}
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
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->y <= 3*width )
		{
			if( blocks[ i ]->nr == 1 || blocks[ i ]->nr == 6 || blocks[ i ]->nr == 5 )
			{
				if( rand()%100 < chance )
				{
					this->blocks.push_back( new Pug() );
					this->blocks[ this->blocks.size()-1 ]->positioning( width );
					
					if( rand()%2 == 1 )
					{
						this->blocks[ this->blocks.size()-1 ]->setPosition( blocks[ i ]->x, blocks[ i ]->y -width, 2, width );
					}
					else
					{
						this->blocks[ this->blocks.size()-1 ]->setPosition( blocks[ i ]->x, blocks[ i ]->y -width, 1 );
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

void Wall::backToGrass( int add )
{
	for( auto &it :blocks )
	{
		it->moveX( add );
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
							
							sprites[ it->getNr(j) -min ]->setPosition( it->getX(j), it->getY(j) );
							if( sprites[ it->getNr(j) -min ]->checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
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
					if( it->getNr(j) < 12 )
					{
						sprites[ it->getNr(j) -8 ]->setPosition( it->getX(j), it->getY(j) );
						if( sprites[ it->getNr(j) -8 ]->checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
						{
							return true;
						}
					}
					else
					{
						sprites[ sprites.size()-1 ]->setPosition( it->getX(j), it->getY(j) );
						if( sprites[ sprites.size()-1 ]->checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
						{
							return true;
						}
					}
				}
			}
		}
	}
	
	return false;
}