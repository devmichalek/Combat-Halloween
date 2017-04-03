#include "spikes.h"
#include "file/file.h"

Spikes::Spikes()
{
	free();
}

Spikes::~Spikes()
{
	free();
}

void Spikes::free()
{
	screen_w = 0;
	screen_h = 0;
	
	damage = 0;
	main_vel = 0;
	sprite.free();
	
	if( !spikes.empty() )
	{
		for( auto &it :spikes )
		{
			it->free();
		}
		
		spikes.clear();
	}
	
	hit.free();
}

void Spikes::reset( int distance )
{
	for( auto &it :spikes )
	{
		it->reset( distance );
	}
}



void Spikes::load( int type, int screen_w, int screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	sprite.setName( "spikes-sprite" );
	sprite.load( "data/04_platform/world/" +con::itos( type ) +"/traps/2.png" );
	
	// Set damage.
	MyFile file;
	file.load( "data/txt/world/spikes.txt" );
	if( file.is_good() )
	{
		string line;
		int c = type;
		while( file.get() >> line )
		{
			if( c == 0 )
			{
				damage = con::stoi( line );
			}
			
			c --;
		}
	}
	file.free();
	
	// Set vel.
	file.load( "data/txt/world/spikes_vel.txt" );
	if( file.is_good() )
	{
		string line;
		int c = type;
		while( file.get() >> line )
		{
			if( c == 0 )
			{
				main_vel = con::stof( line.c_str() );
			}
			
			c --;
		}
	}
	file.free();
	
	// Set hit.
	hit.setName( "boulder-hit" );
	if( type == 4 )
	{
		hit.load( "data/04_platform/world/sounds/wall/1.wav" );
	}
	else
	{
		hit.load( "data/04_platform/world/sounds/wall/0.wav" );
	}
}

void Spikes::draw( sf::RenderWindow* &window )
{
	for( auto &it :spikes )
	{
		if( it->isAlive() && it->getX() +sprite.getWidth() > 0 && it->getX() < screen_w )
		{
			sprite.setPosition( it->getX(), it->getY() );
			window->draw( sprite.get() );
		}
	}
}

void Spikes::fadein( int v, int max )
{
	sprite.fadein( v, max );
}

void Spikes::fadeout( int v, int min )
{
	sprite.fadeout( v, min );
}



void Spikes::positioning( vector <Block*> blocks, int width, int chance )
{
	for( auto &it :blocks )
	{
		if( it->nr == 12 || it->nr == 2 || it->nr == 7 )
		{
			if( it->y >= screen_h -width )
			{
				if( rand()%100 < chance )
				{
					spikes.push_back( new Spike() );
					spikes[ spikes.size() -1 ]->setLine( 200 );
					if( rand() %2 == 1 )
					{
						spikes[ spikes.size() -1 ]->setPosition( it->x +width/4, it->y +width );
						spikes[ spikes.size() -1 ]->setVel( -main_vel -(static_cast <float> (rand()%100) /100) );
					}
					else
					{
						spikes[ spikes.size() -1 ]->setPosition( it->x +width/4, -sprite.getWidth() );
						spikes[ spikes.size() -1 ]->setVel( main_vel +(static_cast <float> (rand()%100) /100) );
					}
				}
			}
		}
	}
}



void Spikes::moveX( sf::Uint8 direction, float vel )
{
	for( auto &it :spikes )
	{
		it->moveX( direction, vel );
	}
}

void Spikes::undoFall( sf::Uint8 add )
{
	for( auto &it :spikes )
	{
		it->undoFall( add );
	}
}

void Spikes::mechanics()
{
	for( auto &it :spikes )
	{
		if( it->isAlive() || (it->getX() +sprite.getWidth() > 0 && it->getX() < screen_w) )
		{
			it->mechanics( screen_h, sprite.getHeight() );
		}
	}
}

void Spikes::setColor( sf::Color color )
{
	sprite.setColor( color );
}



bool Spikes::harm( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &it :spikes )
		{
			if( it->isAlive() && it->getX() +sprite.getWidth() > 0 && it->getX() < screen_w )
			{
				sprite.setPosition( it->getX(), it->getY() );
				if( sprite.checkRectCollision( *rect ) )
				{
					if( hit.isPlayable() )
					{
						hit.play();
					}
					return true;
				}
			}
		}
	}
	
	return false;
}



int Spikes::getDamage()
{
	return damage;
}



void Spikes::turnOn()
{
	hit.turnOn();
}

void Spikes::turnOff()
{
	hit.turnOff();
}

void Spikes::setVolume( int v )
{
	hit.setVolume( v );
}