#include "mine_factory.h"
#include <cstdlib>
#include "file/file.h"

Mine_factory::Mine_factory()
{
	width = 0;
	screen_w = 0;
	screen_h = 0;
	damage = 0;
}

Mine_factory::~Mine_factory()
{
	free();
}

void Mine_factory::free()
{
	width = 0;
	screen_w = 0;
	screen_h = 0;
	damage = 0;
	type = 0;
	
	if( !mines.empty() )
	{
		for( auto &i :mines )
		{
			i->free();
		}
		
		mines.clear();
	}
	
	if( !sprites.empty() )
	{
		for( auto &i :sprites )
		{
			i->free();
		}
		
		sprites.clear();
	}
	
	ticktock.free();
	explosion.free();
}

void Mine_factory::reset( int distance )
{
	while( true )
	{
		if( distance > 0 )
		{
			for( auto &it :mines )
			{
				it->moveX( 1.0 );
			}
			
			distance --;
		}
		else
		{
			break;
		}
	}
	
	for( auto &it :mines )
	{
		it->reset();
	}
}



void Mine_factory::load( int type, int width, int screen_w, int screen_h )
{
	free();
	this->type = type;
	
	// Set damage.
	MyFile file;
	file.load( "data/txt/enemy/mine.txt" );
	if( file.is_good() )
	{
		string line;
		int c = type;
		while( file.get() >> line )
		{
			if( c == 0 )
			{
				damage = con::stoi( line );
				break;
			}
			
			c --;
		}
	}
	file.free();
	
	sprites.push_back( new MySprite() );
	sprites[ sprites.size() -1 ]->setName( "mine_factory-sprites[ 0 ]" );
	sprites[ sprites.size() -1 ]->load( "data/04_platform/enemy/mine/" +con::itos(type) +"/0.png", 2 );
	sprites[ sprites.size() -1 ]->setScale( 0.5, 0.5 );
	
	sprites.push_back( new MySprite() );
	sprites[ sprites.size() -1 ]->setName( "mine_factory-sprites[ 1 ]" );
	sprites[ sprites.size() -1 ]->load( "data/04_platform/enemy/mine/" +con::itos(type) +"/1.png", 7 );
	sprites[ sprites.size() -1 ]->setScale( 0.5, 0.5 );
	
	this->width = width;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	ticktock.setName( "mine_factory-ticktock" );
	ticktock.load( "data/04_platform/enemy/mine/sounds/ticktock.wav" );
	
	explosion.setName( "mine_factory-explosion" );
	explosion.load( "data/04_platform/enemy/mine/sounds/explosion.wav" );
}

void Mine_factory::draw( sf::RenderWindow* &window )
{
	for( auto &i :mines )
	{
		if( i->ableToDraw() )
		{
			if( i->getX() > -width && i->getX() < screen_w + width )
			{
				if( i->explosion() && explosion.isPlayable() )
				{
					explosion.play();
				}
				
				sprites[ i->getNr() ]->setOffset( i->getOffset() );
				sprites[ i->getNr() ]->setPosition( i->getX(), i->getY() );
				window->draw( sprites[ i->getNr() ]->get() );
			}
		}
	}
}



void Mine_factory::fadein( int v, int max )
{
	for( auto &i :sprites )
	{
		i->fadein( v, max );
	}
}

void Mine_factory::fadeout( int v, int min )
{
	for( auto &i :sprites )
	{
		i->fadeout( v, min );
	}
}



void Mine_factory::addMine( int x1, int x2, int y )
{
	mines.push_back( new Mine() );
	mines[ mines.size() -1 ]->positioning( x1, x2, y );
}

void Mine_factory::positioning( vector <Block*> blocks, int chance )
{
	damage +=  damage*(static_cast <float> (chance) /100);
	for( auto &i :blocks )
	{
		if( i->nr >= 0 && i->nr <= 7 )
		{
			if( rand()%100 < chance *0.60 )
			{
				int x1 = i->x +width/2 -sprites[ 0 ]->getWidth()/2;
				int x2 = i->x +width/2 -sprites[ 1 ]->getWidth()/2;
				int y = i->y -sprites[ 0 ]->getHeight();
				addMine( x1, x2, y +3 );
			}
		}
	}
}



void Mine_factory::checkCollision( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &i :mines )
		{
			if( i->ableToDraw() )
			{
				if( i->getX() > -width && i->getX() < screen_w +width )
				{
					sprites[ i->getNr() ]->setPosition( i->getX(), i->getY() );
					if( sprites[ i->getNr() ]->checkCollision( rect->getX(), rect->getY() -50, rect->getWidth(), rect->getHeight()/2 ) )
					{
						if( i->ticktock() && ticktock.isPlayable() )
						{
							ticktock.play();
						}
							
						i->setActive();
						break;
					}
				}
			}
		}
	}
}

bool Mine_factory::harm( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &i :mines )
		{
			if( i->ableToDraw() )
			{
				if( i->getX() > -width && i->getX() < screen_w +width && i->harm() )
				{
					sprites[ i->getNr() ]->setPosition( i->getX(), i->getY() );
					if( sprites[ i->getNr() ]->checkCollision( rect->getX(), rect->getY() -50, rect->getWidth(), rect->getHeight()/2 ) )
					{
						return true;
					}
				}
			}
		}
	}
	
	return false;
}



void Mine_factory::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		for( auto &it :mines )
		{
			it->moveX( vel );
		}
	}
	else if( direction == 2 )
	{
		for( auto &it :mines )
		{
			it->moveX( -vel );
		}
	}
}

void Mine_factory::undoFall( sf::Uint8 add )
{
	for( auto &it :mines )
	{
		it->moveX( add );
	}
}

void Mine_factory::mechanics()
{
	for( auto &i :mines )
	{
		i->mechanics();
	}
}

void Mine_factory::setColor( sf::Color color )
{
	for( auto &i :sprites )
	{
		i->setColor( color );
	}
}

int Mine_factory::getDamage()
{
	return damage;
}

void Mine_factory::turnOn()
{
	ticktock.turnOn();
	explosion.turnOn();
}

void Mine_factory::turnOff()
{
	ticktock.turnOff();
	explosion.turnOff();
}

void Mine_factory::setVolume( int v )
{
	ticktock.setVolume( v );
	explosion.setVolume( v );
}
