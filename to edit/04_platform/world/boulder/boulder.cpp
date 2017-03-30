#include "boulder.h"
#include <time.h>
#include <cstdlib>
#include "file/file.h"


Boulder::Boulder()
{
	free();
}

Boulder::~Boulder()
{
	free();
}

void Boulder::free()
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

void Boulder::reset( int distance )
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


void Boulder::load( int type, int width, int screen_w )
{
	free();

	this->width = width;
	this->screen_w = screen_w;
	
	string path = "/boulder/0.png";
	if( type == 4 )
	{
		path = "/saw/0.png";
	}
	
	for( int i = 0; i < 2; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ i ]->setName( "boulder-sprite nr" +con::itos( i ) );
		sprites[ i ]->load( "data/04_platform/world/" +con::itos( type ) +path );
	}
	
	sprites.push_back( new MySprite() );
	sprites[ sprites.size() -1 ]->setName( "boulder-sprite nr" +con::itos( sprites.size() -1 ) );
	hit.setName( "boulder-hit" );
	
	if( type == 4 )
	{
		hit.load( "data/04_platform/world/sounds/wall/1.wav" );
		sprites[ sprites.size() -1 ]->load( "data/04_platform/world/4/saw/1.png" );
	}
	else
	{
		hit.load( "data/04_platform/world/sounds/wall/0.wav" );
		sprites[ sprites.size() -1 ]->load( "data/04_platform/world/0/boulder/1.png" );
	}
	
	MyFile file;
	file.load( "data/txt/world/boulder.txt" );
	if( file.is_good() )
	{
		string line;
		int c = type;
		while( file.get() >> line )
		{
			if( c == 0 )
			{
				damage = con::stoi( line );
				// printf( "%d\n", damage );
			}
			c--;
		}
	}
	file.free();
	
	sprites[ sprites.size() -1 ]->setOrigin( sprites[ sprites.size() -1 ]->getWidth() /2, sprites[ sprites.size() -1 ]->getHeight() /2 );
}

void Boulder::draw( sf::RenderWindow* &window )
{
	for( auto &it :blocks )
	{
		for( unsigned j = 0; j < it->getSize(); j++ )
		{
			if( it->getX(j) > -width && it->getX(j) < screen_w )
			{
				sprites[ it->getNr(j) ]->setPosition( it->getX(j), it->getY(j) );
				window->draw( sprites[ it->getNr(j) ]->get() );
			}
		}
		
		if( it->getBoulderX() > -width*2 && it->getBoulderX() < screen_w +width && it->renderBoulder() )
		{
			sprites[ sprites.size() -1 ]->setPosition( it->getBoulderX(), it->getBoulderY() );
			sprites[ sprites.size() -1 ]->setAlpha( it->getBoulderAlpha() );
			sprites[ sprites.size() -1 ]->setAngle( it->getBoulderAngle() );
			window->draw( sprites[ sprites.size() -1 ]->get() );
		}
	}
}


void Boulder::fadein( int v, int max )
{
	if( sprites[ 0 ]->getAlpha() < max )
	{
		for( auto &i :sprites )
		{
			i->fadein( v, max );
		}
		
		for( auto &it :blocks )
		{
			it->setBoulderAlpha( sprites[ 0 ]->getAlpha() );
		}
	}
}

void Boulder::fadeout( int v, int min )
{
	if( sprites[ 0 ]->getAlpha() > min )
	{
		for( auto &i :sprites )
		{
			i->fadeout( v, min );
		}
		
		for( auto &it :blocks )
		{
			it->setBoulderAlpha( sprites[ 0 ]->getAlpha() );
		}
	}
}




void Boulder::positioning( vector <Block*> blocks, vector <int> xs, int chance )
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->y <= 3*width && blocks[ i ]->x > screen_w )
		{
			if( blocks[ i ]->nr == 0 || blocks[ i ]->nr == 1 || blocks[ i ]->nr == 4
			 || blocks[ i ]->nr == 5 || blocks[ i ]->nr == 6 )
			{
				bool success = true;
				for( auto &it :xs )
				{
					if( it >= blocks[ i ]->x && it <= blocks[ i ]->x +width*3 )
					{
						success = false;
						break;
					}
				}
				
				if( success )
				{
					this->blocks.push_back( new Boulder_part() );
					this->blocks[ this->blocks.size()-1 ]->positioning( width );
					
					float vel = 2 +(static_cast <float> (rand()%150) /100);
					
					double angle_vel = 3 +rand()%3;
					if( rand()%2 == 1 )	angle_vel = -angle_vel;
					
					this->blocks[ this->blocks.size()-1 ]->setPosition( blocks[ i ]->x, blocks[ i ]->y +width, vel, angle_vel );
					if( i +5 < blocks.size() )
					{
						i += 5;
					}
					else
					{
						break;
					}
				}
			}
		}
	}
}



void Boulder::moveX( sf::Uint8 direction, float vel )
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

void Boulder::undoFall( sf::Uint8 add )
{
	for( auto &it :blocks )
	{
		it->moveX( add );
	}
}

void Boulder::mechanics( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &it :blocks )
		{
			it->moving( rect, width );
		}
	}
}

void Boulder::setColor( sf::Color color )
{
	for( auto &i :sprites )
	{
		i->setColor( color );
	}
}



bool Boulder::harm( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &it :blocks )
		{
			if( it->harm( width ) )
			{
				for( unsigned j = 0; j < it->getSize(); j++ )
				{
					if( it->getX(j) > 0 && it->getX(j) < screen_w )
					{
						if( hit.isPlayable() )
						{
							hit.play();
						}
						
						sprites[ sprites.size() -1 ]->setPosition( it->getBoulderX() -width/2, it->getBoulderY() -width/2 );
						if( sprites[ sprites.size() -1 ]->checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
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


int Boulder::getDamage()
{
	return damage;
}



void Boulder::turnOn()
{
	hit.turnOn();
}

void Boulder::turnOff()
{
	hit.turnOff();
}

void Boulder::setVolume( int v )
{
	hit.setVolume( v );
}