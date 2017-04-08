/**
    hero.h
    Purpose: class Hero contains each hero textures, each mechanics.

    @author Adrian Michalek
    @version 2016.09.15
	@email adrmic98@gmail.com
*/

#include "ninja.h"
#include "file/file.h"
#include "04_platform/ninja/kunai/damage.h"

Hero::Hero()
{
	free();
}

Hero::~Hero()
{
	free();
}

void Hero::free()
{
	if( !keys.empty() )
	{
		for( auto &i :keys )
		{
			if( i != NULL )
			{
				delete [] i;
				i = NULL;
			}
		}
		
		keys.clear();
	}
	
	if( !sprites.empty() )
	{
		for( auto &i :sprites )
		{
			i->free();
		}
		
		sprites.clear();
	}
	
	which = 0;
	offset = 0;
	delay = 0;
	
	vel = 0;
	// vel_state = 0;
	jump_vel = 0;
	grav = 0;
	scale = 0;
	
	right = false;
	move = false;
	
	damage = 0;
	
	glide = false;
	
	slide = false;
	
	climb = 0;
	
	dead = 0;
	
	j.free();
	a.free();
	ja.free();
	t.free();
	jt.free();
	
	scope = false;
	
	fallen = false;
	fallenCounter = 0;
	fallenLine = 0;
	fallenY = -1;
	
	if( !x.empty() )
	{
		x.clear();
	}
	
	if( !x2.empty() )
	{
		x2.clear();
	}
	
	if( !y.empty() )
	{
		y.clear();
	}
}

void Hero::reset( int screen_h, int width )
{
	int x_distance = x[ IDLE ] -(width /2);
	int y_distance = y[ IDLE ] -(screen_h -width -width*3/4);
	

	for( auto &i :x )
	{
		i -= x_distance;
	}
	
	for( auto &i :x2 )
	{
		i -= x_distance;
	}
	
	for( auto &i :y )
	{
		i -= y_distance;
	}
	
	dead = 0;
	which = IDLE;
}

/*
void Hero::setFPS( float FPS )
{
	vel = (1000 -FPS) *0.0015;
	jump_vel = 2*vel;
	grav = (1000 -FPS) *0.0012;
	delay = FPS /20;
	
	printf( "%f\n", vel );
}
*/



void Hero::load( int type, int screen_w, int screen_h, int width )
{
	free();
	
	// 	Set scale.
	scale = 0.75;
	
	int nr = DEAD +1;
	for( int i = 0; i < nr; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ i ]->setName( "hero-sprite[" + con::itos( i ) + "]" );
		sprites[ i ]->load( "data/04_platform/hero/" + con::itos( type ) + "/" + con::itos( i ) + ".png", nr -1 );
		sprites[ i ]->setScale( scale, scale );
		
		x.push_back( width /2 );
		x2.push_back( width /2 +sprites[ i ]->getWidth() );
		y.push_back( screen_h -sprites[ i ]->getHeight() -(static_cast <float> (width)*1.5) );
	}
	
	// Start values.
	which = IDLE;
	offset = 0;
	
	// Set other values
	vel = 1.25;
	grav = 1;
	if( type == 1 || type == 4 )
	{
		delay = 7;
		vel += 0.25;
		j.setLine( (nr-1)*delay + 7*delay );
	}
	else if( type == 2 || type == 5 )
	{
		delay = 6;
		vel += 0.5;
		grav += 0.5;
		j.setLine( (nr-1)*delay + 2*delay );
	}
	else
	{
		delay = 8;
		j.setLine( (nr-1)*delay + 10*delay );
	}
	
	jump_vel = vel*2;
	
	
	right = true;
	move = false;
	
	// Duration
	a.setLine( (nr-1)*delay + 2*delay );
	ja.setLine( (nr-1)*delay + 2*delay );
	t.setLine( (nr-1)*delay + 2*delay );
	jt.setLine( (nr-1)*delay + 2*delay );
	
	fallenLine = 540;
	
	// corrections
	x[ RUN ] -= sprites[ IDLE ]->getWidth() -20*scale;
	y[ RUN ] += 3;
	if( type > 2 )
		x[ RUN ] += 30 *scale;
	x[ THROW ] -= 21*scale;
	if( type > 2 )
		x[ THROW ] += 8 *scale;
	x2[ THROW ] -= 15*scale;
	if( type > 2 )
		x2[ THROW ] += 5 *scale;
	y[ THROW ] ++;
	x[ ATTACK ] = x[ RUN ];
	x2[ ATTACK ] = x2[ RUN ];
	y[ ATTACK ] += 12*scale;
	x2[ SLIDE ] -= sprites[ IDLE ]->getWidth()/2;
	x[ JUMP ] -= (sprites[ JUMP ]->getWidth() -sprites[ IDLE ]->getWidth() );
	x[ JUMP_ATTACK ] -= (sprites[ JUMP ]->getWidth() -sprites[ IDLE ]->getWidth() );
	y[ JUMP_ATTACK ] += 13*scale;
	x2[ JUMP_ATTACK ] -= (sprites[ JUMP ]->getWidth() -sprites[ IDLE ]->getWidth() );
	x[ JUMP_THROW ] -= (sprites[ JUMP ]->getWidth() -sprites[ IDLE ]->getWidth() );
	y[ JUMP_THROW ] -= 10*scale;
	x2[ DEAD ] -= (sprites[ DEAD ]->getWidth() -sprites[ IDLE ]->getWidth() );
	y[ DEAD ] += 5*scale;
	if( type > 2 )
	{
		y[ DEAD ] += 10*scale;
	}
	x[ GLIDE ] -= (sprites[ GLIDE ]->getWidth() -sprites[ IDLE ]->getWidth() );
	
	// damage
	float val = 0;
	int lev = 0;
	
	MyFile file;
	
	file.load( "data/txt/skill/skill_values.txt" );
	if( file.is_good() )
	{
		string line;
		int counter = 1;
		while( file.get() >> line )
		{
			if( counter == 0 )
			{
				val = stof( line );
				break;
			}
			
			counter --;
		}
	}
	file.free();
	
	
	file.load( "data/txt/skill/level_current.txt" );
	if( file.is_good() )
	{
		string line;
		int counter = 1;
		while( file.get() >> line )
		{
			if( counter == 0 )
			{
				lev = stof( line );
				break;
			}
			counter --;
		}
	}
	file.free();
	
	
	// printf( "%f\n", val );
	Damage DAMAGE;
	string newstr = DAMAGE.multiply( 1, val, lev );
	damage =  stof( newstr );
	// printf( "%f\n", damage );
}

void Hero::setKeys()
{
	if( !keys.empty() )
	{
		for( auto &it :keys )
		{
			delete [] it;
		}
		
		keys.clear();
	}
	
	// Set keys.
	MyFile file;
	
	file.load( "data/txt/keyboard/keyboard_temporary.txt" );
	if( file.is_good() )
	{
		string line;
		for( unsigned i = 0; i < sprites.size(); i ++ )
		{
			int* arrow;
			keys.push_back( arrow );
			keys[ i ] = new int[ 2 ];
			
			file.get() >> line;	keys[ i ][ 0 ] = con::stoi( line );
			file.get() >> line;	keys[ i ][ 1 ] = con::stoi( line );
		}
	}
	file.free();
}

void Hero::draw( sf::RenderWindow* &window )
{
	if( dead != 2 )
	{
		sprites[ which ]->setOffset( offset /delay );
	}
	
	
	if( !fallen )
	{
		for( unsigned i = 0; i < sprites.size(); i++ )
		{
			if( !right )	sprites[ i ]->setPosition( x2[ i ], y[ i ] +1 );
			else			sprites[ i ]->setPosition( x[ i ], y[ i ] +1 );
		}
		
		float scaleY = scale;
		if( scaleY < 0 )	scaleY = -scaleY;
		
		sprites[ which ]->setScale( scale, scaleY );
		window->draw( sprites[ which ]->get() );
	}
}

void Hero::doOffset()
{
	if( dead != 2 )
	{
		if( climb == 1 || ( climb == 0 && which != CLIMB ) )
		{
			offset ++;
		}
		//printf( "%d\n", offset );
		if( offset == (sprites.size()-1) *delay || ( dead == 1 && offset == (sprites.size()-1) *delay-1 ) )
		{
			offset = 0;
			j.setActive( false );
			a.setActive( false );
			ja.setActive( false );
			t.setActive( false );
			jt.setActive( false );
			
			if( dead == 1 )
			{
				dead = 2;
			}
		}
	}
}



void Hero::fadein( int v, int max )
{
	for( auto &i :sprites )
	{
		i->fadein( v, max );
	}
}

void Hero::fadeout( int v, int min )
{
	for( auto &i :sprites )
	{
		i->fadeout( v, min );
	}
}

void Hero::setColor( sf::Color color )
{
	for( auto &i :sprites )
	{
		i->setColor( color );
	}
}




int Hero::getX()
{
	return static_cast <int> ( x[ IDLE ] );
}

int Hero::getY()
{
	if( which == SLIDE )
	{
		return y[ SLIDE ];
	}
	
	return y[ IDLE ];
}

int Hero::getW()
{
	return sprites[ IDLE ]->getWidth();
}

int Hero::getH()
{
	if( which == SLIDE )
	{
		return sprites[ SLIDE ]->getHeight();
	}
	
	return sprites[ IDLE ]->getHeight();
}




bool Hero::checkKeys( int a, int b )
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( a ) ) && b == -1 )
	{
		return true;
	}
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( a ) ) )
	{
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( b ) ) )
		{
			return true;
		}
	}

	return false;
}

sf::Uint8 Hero::getDirection()
{
	if( move )
	{
		if( right )
		{
			return 2;
		}
		else
		{
			return 1;
		}
	}

	return 0;
}

bool Hero::getSide()
{
	return right;
}

Rect* Hero::getRect()
{
	Rect* rect = new Rect;
	rect->set( x[ IDLE ], y[ IDLE ], sprites[ IDLE ]->getWidth(), sprites[ IDLE ]->getHeight() );
	return rect;
}




float Hero::getVel()
{
	return vel;
}

float Hero::getJump_vel()
{
	return jump_vel;
}

void Hero::setScope( bool scope )
{
	this->scope = scope;
}




void Hero::die()
{
	if( dead == 0 )
	{
		dead = 1;
		
		if( which <= SLIDE )
		{
			offset = 0;
			j.setActive( false );
			a.setActive( false );
			ja.setActive( false );
			t.setActive( false );
			jt.setActive( false );
			which = DEAD;
		}
		else
		{
			offset = (sprites.size()-1)*delay -1;
		}
	}
}

bool Hero::isDead()
{
	if( dead == 2 )
	{
		return true;
	}
	
	return false;
}


bool Hero::resume()
{
	if( dead == 0 )
	{
		if( fallenCounter == fallenLine )
		{
			fallenCounter = 0;
			for( auto &i :sprites )
			{
				i->setAlpha( 0xFF );
			}
		}
		else if( fallenCounter > 0 && !fallen )
		{
			sf::Uint8 alpha_line = 100;
			fallenCounter ++;
			
			if( fallenCounter%60 == 0 )
			{
				if( sprites[ IDLE ]->getAlpha() == alpha_line )
				{
					for( auto &i :sprites )
					{
						i->setAlpha( 0xFF );
					}
				}
				else
				{
					for( auto &i :sprites )
					{
						i->setAlpha( alpha_line );
					}
				}
			}
			
			return true;
		}
	}
	
	if( fallenY != -1 )
	{
		return true;
	}
	
	return false;
}

int Hero::getOffset()
{
	return offset /delay;
}