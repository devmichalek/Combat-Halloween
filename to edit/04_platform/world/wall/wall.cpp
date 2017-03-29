#include "wall.h"
#include <time.h>
#include <cstdlib>
#include "file/file.h"


Wall::Wall()
{
	free();
}

Wall::~Wall()
{
	free();
}

void Wall::free()
{
	width = 0;
	screen_w = 0;
	damage = 0;
	
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
	
	hit.free();
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
	
	this->width = width;
	this->screen_w = screen_w;
	
	for( int i = 0; i < 7; i++ )
	{
		sprites.push_back( new MySprite() );
	}
	
	sprites[ 0 ]->load( "data/04_platform/world/" +con::itos( type ) +"/pug/" +con::itos( 0 ) +".png" );
	sprites[ 1 ]->load( "data/04_platform/world/" +con::itos( type ) +"/pug/" +con::itos( 1 ) +".png" );
	sprites[ 2 ]->load( "data/04_platform/world/" +con::itos( type ) +"/" +con::itos( 10 ) +".png" );
	sprites[ 3 ]->load( "data/04_platform/world/" +con::itos( type ) +"/pug/" +con::itos( 4 ) +".png" );
	sprites[ 4 ]->load( "data/04_platform/world/" +con::itos( type ) +"/" +con::itos( 12 ) +".png" );
	sprites[ 5 ]->load( "data/04_platform/world/" +con::itos( type ) +"/pug/" +con::itos( 2 ) +".png" );
	sprites[ 6 ]->load( "data/04_platform/world/" +con::itos( type ) +"/pug/" +con::itos( 3 ) +".png" );
	
	int n = 0;
	if( type == 4 )
	{
		n = 1;
	}
	
	hit.setName( "wall-hit" );
	hit.load( "data/04_platform/world/sounds/wall/" +con::itos( n ) +".wav" );
}

void Wall::draw( sf::RenderWindow* &window )
{
	for( auto &it :blocks )
	{
		for( unsigned j = 0; j < it->getSize(); j++ )
		{
			if( it->getX(j) > -width*2 && it->getX(j) < screen_w )
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
	damage = chance;
	
	for( unsigned i = 0; i < blocks.size() -2; i++ )
	{
		if( blocks[ i ]->y <= 3*width && blocks[ i ]->x > screen_w )
		{
			if( (blocks[ i ]->nr == 5 || blocks[ i ]->nr == 0 || blocks[ i ]->nr == 1 || blocks[ i ]->nr == 6) &&
				(blocks[ i +2 ]->nr == 2 || blocks[ i +2 ]->nr == 7))
			{
				int nr = 0;
				
				if( rand()%100 < chance )
				{
					this->blocks.push_back( new Pug() );
					this->blocks[ this->blocks.size()-1 ]->positioning( width, nr );
					
					float vel = 0.5 +(static_cast <float> (rand()%150) /100);
					
					if( vel > 1 )
					{
						this->blocks[ this->blocks.size()-1 ]->setPosition( blocks[ i ]->x +width/2, blocks[ i ]->y -width, vel, width );
					}
					else
					{
						this->blocks[ this->blocks.size()-1 ]->setPosition( blocks[ i ]->x +width/2, blocks[ i ]->y -width, vel );
					}
					
					i += 3;
				}
			}
				
			else if( blocks[ i ]->nr == 1 || blocks[ i ]->nr == 6 )
			{
				int nr = 1;
				
				if( rand()%100 < chance )
				{
					this->blocks.push_back( new Pug() );
					this->blocks[ this->blocks.size()-1 ]->positioning( width, nr );
					
					float vel = 2 +(static_cast <float> (rand()%200) /100);
					
					this->blocks[ this->blocks.size()-1 ]->setPosition( blocks[ i ]->x, blocks[ i ]->y -width, vel, width );
					
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

void Wall::mechanics()
{
	for( auto &it :blocks )
	{
		it->moving( width );
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
					if( it->getX(j) > -width*2 && it->getX(j) < screen_w )
					{
						if( hit.isPlayable() )
						{
							hit.play();
						}
						
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
				if( it->getX(j) > -width*2 && it->getX(j) < screen_w )
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

int Wall::getDamage()
{
	return damage;
}

int Wall::getFallDamage()
{
	return damage *2;
}



void Wall::turnOn()
{
	hit.turnOn();
}

void Wall::turnOff()
{
	hit.turnOff();
}

void Wall::setVolume( int v )
{
	hit.setVolume( v );
}

vector <int> Wall::getXs()
{
	// We want to send only x position to know that we have free space.
	vector <int> temporary;
	int temporary_x = -1;
	
	for( auto &it :blocks )
	{
		for( unsigned i = 0; i < it->getSize(); i++ )
		{
			if( it->getX( i ) != temporary_x )
			{
				temporary_x = it->getX( i );
				temporary.push_back( temporary_x );
				// printf( "%d\n", temporary_x );
			}
		}
	}
	
	return temporary;
}