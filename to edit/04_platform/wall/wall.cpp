#include "wall.h"
#include <time.h>
#include <cstdlib>


Wall::Wall()
{
	// empty
}

Wall::~Wall()
{
	free();
}

void Wall::free()
{
	if( !sprites.empty() )
	{
		for( auto &i :sprites )
		{
			i->free();
		}
		
		sprites.clear();
	}
	
	if( !blocks.empty() )
	{
		for( auto &i :blocks )
		{
			i->free();
		}
		
		blocks.clear();
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


void Wall::load( int type )
{
	free();
	
	for( int i = 0; i < 4; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ i ]->setName( "Wall-block[" +to_string( i ) +"]" );
	}
	
	sprites[ 0 ]->load( "data/sprites/play/" +to_string( type ) +"/8.png" );
	sprites[ 1 ]->load( "data/sprites/play/" +to_string( type ) +"/9.png" );
	sprites[ 2 ]->load( "data/sprites/play/" +to_string( type ) +"/10.png" );
	sprites[ 3 ]->load( "data/sprites/play/" +to_string( type ) +"/12.png" );
}

void Wall::draw( sf::RenderWindow* &window, int screen_w )
{
	for( auto &it :blocks )
	{
		it->moving();
		
		for( unsigned j = 0; j < it->getSize(); j++ )
		{
			if( it->getX(j) > -screen_w/2 && it->getX(j) < screen_w +it->getMainR() )
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




void Wall::positioning( vector <Block*> blocks, int l, int r )
{
	int width = 128;
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->y <= 3*width && blocks[ i ]->x > l && blocks[ i ]->x < r )
		{
			if( blocks[ i ]->nr == 1 || blocks[ i ]->nr == 6 || blocks[ i ]->nr == 5 )
			{
				if( rand()%100 < 30 )
				{
					this->blocks.push_back( new WallBlock() );
					this->blocks[ this->blocks.size()-1 ]->positioning();
					
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

bool Wall::allowHarm( int x1, int x2 )
{
	for( auto &it :blocks )
	{
		if( x1 > it->getMainX() && x2 < it->getMainR() )
		{
			return true;
		}
	}
	
	return false;
}

bool Wall::harm( Rect* rect, int screen_w )
{
	if( rect != NULL )
	{
		for( auto &it :blocks )
		{
			if( it->harm() )
			{
				for( unsigned j = 0; j < it->getSize(); j++ )
				{
					if( it->getX(j) > -screen_w/2 && it->getX(j) < screen_w +it->getMainR() )
					{
						if( it->getNr(j) < 10 )
						{
							
							sprites[ it->getNr(j) -8 ]->setPosition( it->getX(j), it->getY(j) );
							if( sprites[ it->getNr(j) -8 ]->checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
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

bool Wall::checkCollision( Rect* rect, int screen_w )
{
	if( rect != NULL )
	{
		for( auto &it :blocks )
		{
			for( unsigned j = 0; j < it->getSize(); j++ )
			{
				if( it->getX(j) > -screen_w/2 && it->getX(j) < screen_w +200 )
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