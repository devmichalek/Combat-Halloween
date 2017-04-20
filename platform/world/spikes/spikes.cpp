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
	type = 0;
	width = 0;
	screen_w = 0;
	
	damage = 0;
	main_vel = 0;
	
	hit.free();
	sprite.free();
	
	if( !spikes.empty() )
	{
		for( auto &it :spikes )
		{
			it->free();
		}
		
		spikes.clear();
	}
}

void Spikes::reset( int distance )
{
	for( auto &it :spikes )
	{
		it->reset( distance );
	}
}



void Spikes::load( int type, int screen_w, int width )
{
	free();
	
	this->type = type;
	this->width = width;
	this->screen_w = screen_w;
	
	
	sprite.setName( "spikes-sprite" );
	sprite.load( "data/platform/world/" +con::itos( type ) +"/traps/2.png" );
	
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
	hit.setName( "spikes-hit" );
	hit.load( "data/platform/world/sounds/wall/0.wav" );
}

void Spikes::draw( sf::RenderWindow* &window )
{
	for( auto &it :spikes )
	{
		if( it->isAlive() && it->getX() +sprite.getWidth() > 0 && it->getX() < screen_w )
		{
			sprite.setAlpha( it->getAlpha() );
			sprite.setPosition( it->getX(), it->getY() );
			window->draw( sprite.get() );
		}
	}
}

void Spikes::fadein( int v, int max )
{
	sprite.fadein( v, max );
	for( auto &it :spikes )
	{
		if( it->getAlpha() <= max -v )
		{
			it->setAlpha( it->getAlpha() +v );
		}
	}
}

void Spikes::fadeout( int v, int min )
{
	sprite.fadeout( v, min );
	for( auto &it :spikes )
	{
		if( it->getAlpha() >= min +v )
		{
			it->setAlpha( it->getAlpha() -v );
		}
	}
}



void Spikes::positioning( vector <Block*> b1, vector <Block*> b2, int chance )
{
	damage += damage *(static_cast <float> (chance) /100);
	
	int w = 0;
	int h = 0;
	
	if( type == 0 )
	{
		w = 8;
		h = 42;
	}
	else if( type == 1 )
	{
		w = 22;
		h = 50;
	}
	else if( type == 2 )
	{
		w = 22;
		h = 50;
	}
	
	// First brick blocks.
	for( auto &it :b1 )
	{
		if( it->nr == 5 )
		{
			for( auto &jt :b2 )
			{
				if( jt->nr >= 0 && jt->nr <= 7 )
				{
					if( jt->x <= it->x +w &&
						jt->x +width >= it->x +w +sprite.getWidth() &&
						jt->y > it->y &&
						jt->y <= it->y +width*3 )
					{
						spikes.push_back( new Spike() );
						spikes[ spikes.size() -1 ]->setVel( main_vel );
						spikes[ spikes.size() -1 ]->setPosition( it->x +w, it->y +h, jt->y -h );
					}
				}
			}
		}
		else if( it->nr == 7 )
		{
			for( auto &jt :b2 )
			{
				if( jt->nr >= 0 && jt->nr <= 7 )
				{
					if( jt->x <= it->x -w +width -sprite.getWidth() &&
						jt->x +width >= it->x -w +width &&
						jt->y > it->y &&
						jt->y <= it->y +width*3 )
					{
						spikes.push_back( new Spike() );
						spikes[ spikes.size() -1 ]->setVel( main_vel );
						spikes[ spikes.size() -1 ]->setPosition( it->x -w +width -sprite.getWidth(), it->y +h, jt->y -h );
					}
				}
			}
		}
	}
	
	// Second islands blocks.
	for( auto &it :b2 )
	{
		if( it->nr == 5 )
		{
			for( auto &jt :b1 )
			{
				if( jt->nr >= 0 && jt->nr <= 7 )
				{
					if( jt->x <= it->x +w &&
						jt->x +width >= it->x +w +sprite.getWidth() &&
						jt->y > it->y &&
						jt->y <= it->y +width*3 )
					{
						spikes.push_back( new Spike() );
						spikes[ spikes.size() -1 ]->setVel( main_vel );
						spikes[ spikes.size() -1 ]->setPosition( it->x +w, it->y +h, jt->y -h );
					}
				}
			}
		}
		else if( it->nr == 7 )
		{
			for( auto &jt :b1 )
			{
				if( jt->nr >= 0 && jt->nr <= 7 )
				{
					if( jt->x <= it->x -w +width -sprite.getWidth() &&
						jt->x +width >= it->x -w +width &&
						jt->y > it->y &&
						jt->y <= it->y +width*3 )
					{
						spikes.push_back( new Spike() );
						spikes[ spikes.size() -1 ]->setVel( main_vel );
						spikes[ spikes.size() -1 ]->setPosition( it->x -w +width -sprite.getWidth(), it->y +h, jt->y -h );
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
			it->mechanics();
		}
	}
}

void Spikes::setColor( sf::Color color )
{
	sprite.setColor( color );
}



void Spikes::check( Rect* rect )
{
	for( auto &it :spikes )
	{
		if( it->isAlive() && it->getX() +sprite.getWidth() > 0 && it->getX() < screen_w )
		{
			if( rect->getX() +rect->getWidth() >= it->getX() &&
				rect->getX() <= it->getX() +sprite.getWidth() &&
				rect->getY() +rect->getHeight() >= it->getY() &&
				rect->getY() <= it->getEndY() )
			{
				it->doFall();
				break;
			}
		}
	}
}

bool Spikes::harm( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &it :spikes )
		{
			if( it->ableToHarm() )
			{
				sprite.setPosition( it->getX(), it->getY() );
				if( sprite.checkCollision( rect->getX(), rect->getY() +rect->getHeight() /2, rect->getWidth(), rect->getHeight() ) )
				{
					if( hit.isPlayable() )
					{
						hit.play();
					}
					
					it->setAsHarmed();
					
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


void Spikes::turn()
{
	hit.turn();
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