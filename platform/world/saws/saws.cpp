#include "saws.h"
#include "file/file.h"

Saws::Saws()
{
	free();
}

Saws::~Saws()
{
	free();
}

void Saws::free()
{
	type = 0;
	width = 0;
	screen_w = 0;
	
	damage = 0;
	main_vel = 0;
	
	hit.free();
	sprite.free();
	
	if( !saws.empty() )
	{
		for( auto &it :saws )
		{
			it->free();
		}
		
		saws.clear();
	}
}

void Saws::reset( int distance )
{
	for( auto &it :saws )
	{
		it->reset( distance );
	}
}



void Saws::load( int type, int screen_w, int width )
{
	free();
	
	this->type = type;
	this->width = width;
	this->screen_w = screen_w;
	
	
	sprite.setName( "saws-sprite" );
	sprite.load( "data/platform/world/" +con::itos( type ) +"/traps/2.png" );
	sprite.setScale( 0.9, 0.9 );
	
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
	hit.setName( "saws-hit" );
	hit.load( "data/platform/world/sounds/wall/1.wav" );
	
	sprite.setOrigin( sprite.getWidth() /2, sprite.getHeight() /2 );
}

void Saws::draw( sf::RenderWindow* &window )
{
	for( auto &it :saws )
	{
		if( it->isAlive() && it->getX() +sprite.getWidth() > 0 && it->getX() < screen_w )
		{
			sprite.setAngle( it->getAngle() );
			sprite.setAlpha( it->getAlpha() );
			sprite.setPosition( it->getX(), it->getY() );
			window->draw( sprite.get() );
		}
	}
}

void Saws::fadein( int v, int max )
{
	sprite.fadein( v, max );
	for( auto &it :saws )
	{
		if( it->getAlpha() <= max -v )
		{
			it->setAlpha( it->getAlpha() +v );
		}
	}
}

void Saws::fadeout( int v, int min )
{
	sprite.fadeout( v, min );
	for( auto &it :saws )
	{
		if( it->getAlpha() >= min +v )
		{
			it->setAlpha( it->getAlpha() -v );
		}
	}
}



void Saws::positioning( vector <Block*> b1, vector <Block*> b2, int chance )
{
	damage += damage *(static_cast <float> (chance) /100);
	
	int w = 0;
	int h = 0;
	
	if( type == 4 )
	{
		w = 9;
		h = 22;
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
						saws.push_back( new Saw() );
						saws[ saws.size() -1 ]->setVel( main_vel );
						saws[ saws.size() -1 ]->setPosition( it->x +w, it->y +h, jt->y -h );
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
						saws.push_back( new Saw() );
						saws[ saws.size() -1 ]->setVel( main_vel );
						saws[ saws.size() -1 ]->setPosition( it->x -w +width -sprite.getWidth(), it->y +h, jt->y -h );
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
				if( jt->nr >= 0 && jt->nr <= 5 )
				{
					if( jt->x <= it->x +w &&
						jt->x +width >= it->x +w +sprite.getWidth() &&
						jt->y > it->y &&
						jt->y <= it->y +width*3 )
					{
						saws.push_back( new Saw() );
						saws[ saws.size() -1 ]->setVel( main_vel );
						saws[ saws.size() -1 ]->setPosition( it->x +w, it->y +h, jt->y -h );
					}
				}
			}
		}
		else if( it->nr == 7 )
		{
			for( auto &jt :b1 )
			{
				if( jt->nr >= 0 && jt->nr <= 5 )
				{
					if( jt->x <= it->x -w +width -sprite.getWidth() &&
						jt->x +width >= it->x -w +width &&
						jt->y > it->y &&
						jt->y <= it->y +width*3 )
					{
						saws.push_back( new Saw() );
						saws[ saws.size() -1 ]->setVel( main_vel );
						saws[ saws.size() -1 ]->setPosition( it->x -w +width -sprite.getWidth(), it->y +h, jt->y -h );
					}
				}
			}
		}
	}
}



void Saws::moveX( sf::Uint8 direction, float vel )
{
	for( auto &it :saws )
	{
		it->moveX( direction, vel );
	}
}

void Saws::undoFall( sf::Uint8 add )
{
	for( auto &it :saws )
	{
		it->undoFall( add );
	}
}

void Saws::mechanics()
{
	for( auto &it :saws )
	{
		if( it->isAlive() || (it->getX() +sprite.getWidth() > 0 && it->getX() < screen_w) )
		{
			it->mechanics();
		}
	}
}

void Saws::setColor( sf::Color color )
{
	sprite.setColor( color );
}



void Saws::check( Rect* rect )
{
	for( auto &it :saws )
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

bool Saws::harm( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &it :saws )
		{
			if( it->ableToHarm() )
			{
				sprite.setPosition( it->getX() -width/2, it->getY() -width/2 );
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



int Saws::getDamage()
{
	return damage;
}


void Saws::turn()
{
	hit.turn();
}

void Saws::turnOn()
{
	hit.turnOn();
}

void Saws::turnOff()
{
	hit.turnOff();
}

void Saws::setVolume( int v )
{
	hit.setVolume( v );
}