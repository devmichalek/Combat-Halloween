#include "hero.h"
#include <fstream>


Hero::Hero()
{
	which = 0;
	offset = 0;
	delay = 0;
	
	vel = 0;
	jump_vel = 0;
	grav = 0;
	scale = 0;
	
	damage = 0;

	right = false;
	move = false;
	
	glide = false;
	
	slide = false;
	
	climb = 0;
	
	dead = 0;
	
	scope = false;
	
	fallen = false;
	fallenCounter = 0;
	fallenLine = 0;
	fallenY = -1;
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
	
	if( !sprite.empty() )
	{
		for( auto &i :sprite )
		{
			i->free();
		}
		
		sprite.clear();
	}
	
	which = 0;
	offset = 0;
	delay = 0;
	
	vel = 0;
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
	
	// box.free();
	// jumpBox.free();
	
	scope = false;
	
	fallen = false;
	fallenCounter = 0;
	fallenLine = 0;
	fallenY = -1;
}




void Hero::load( int type, int screen_w, int screen_h )
{
	free();
	
	// 	Set scale.
	scale = 0.75;
	
	int nr = DEAD +1;
	for( int i = 0; i < nr; i++ )
	{
		sprite.push_back( new MySprite() );
		sprite[ i ]->setName( "hero-sprite[" + to_string( i ) + "]" );
		sprite[ i ]->load( "data/sprites/hero/" + to_string( type ) + "/" + to_string( i ) + ".png", nr -1 );
		sprite[ i ]->setScale( scale, scale );
		sprite[ i ]->setPosition( 70, screen_h -sprite[ i ]->getHeight() -200 );
		sprite[ i ]->setColor( sf::Color( 0xFF, 0x9C, 0 ) );
	}
	sprite[ JUMP_ATTACK ]->setPosition( sprite[ JUMP_ATTACK ]->getX(), sprite[ JUMP_ATTACK ]->getY() + ( sprite[ JUMP_ATTACK ]->getHeight() - sprite[ IDLE ]->getHeight() ) );
	sprite[ THROW ]->setPosition( sprite[ THROW ]->getX() +5, sprite[ THROW ]->getY() );
	sprite[ RUN ]->setPosition( sprite[ RUN ]->getX(), sprite[ RUN ]->getY() +5 );
	
	// Start values.
	which = IDLE;
	offset = 0;
	delay = 6;
	
	
	
	// Set other values
	vel = 1;
	jump_vel = vel*2 +1;
	grav = 1;
	
	damage = 0.07;
	
	right = true;
	move = false;
	
	// Duration
	j.setLine( (nr-1)*delay + 10*delay );
	a.setLine( (nr-1)*delay + 2*delay );
	ja.setLine( (nr-1)*delay + 2*delay );
	t.setLine( (nr-1)*delay + 2*delay );
	jt.setLine( (nr-1)*delay + 2*delay );
	
	/*
	box.setName( "hero-box" );
	box.create( 30, sprite[ ATTACK ]->getHeight() );
	box.setColor( sf::Color( 0xFF, 0x00, 0x00 ) );
	box.setAlpha( 100 );
	
	jumpBox.setName( "hero-box" );
	jumpBox.create( 35, sprite[ JUMP_ATTACK ]->getHeight() );
	jumpBox.setColor( sf::Color( 0xFF, 0x00, 0x00 ) );
	jumpBox.setAlpha( 100 );
	*/

	for( auto &i :sprite )
	{
		i->setPosition( i->getX() - ( i->getWidth() ), i->getY() );
		i->setPosition( sprite[ IDLE ]->getX() - ( i->getWidth() -sprite[ IDLE ]->getWidth() ), i->getY() );
	}
	
	sprite[ ATTACK ]->setPosition( sprite[ IDLE ]->getX(), sprite[ IDLE ]->getY() );
	sprite[ SLIDE ]->setPosition( sprite[ IDLE ]->getX(), sprite[ SLIDE ]->getY() );
	sprite[ JUMP_ATTACK ]->setPosition( sprite[ JUMP ]->getX(), sprite[ JUMP ]->getY() );
	sprite[ JUMP_THROW ]->setPosition( sprite[ JUMP ]->getX(), sprite[ JUMP ]->getY() );
	sprite[ THROW ]->setPosition( sprite[ THROW ]->getX() +11, sprite[ IDLE ]->getY() -1 );
	sprite[ DEAD ]->setPosition( sprite[ IDLE ]->getX(), sprite[ IDLE ]->getY() -5 );

	fallenLine = 540;
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
	fstream file;
	file.open( "data/txt/menu/keyboard_temporary.txt" );
	if( file.bad() )
	{
		printf( "Cannot open file! (hero)\n" );
	}
	else
	{
		string line;
		for( unsigned i = 0; i < sprite.size(); i ++ )
		{
			int* arrow;
			keys.push_back( arrow );
			keys[ i ] = new int[ 2 ];
			
			file >> line;	keys[ i ][ 0 ] = strToInt( line );
			file >> line;	keys[ i ][ 1 ] = strToInt( line );
		}
	}
	file.close();
}

void Hero::draw( sf::RenderWindow* &window )
{
	if( dead == 0 )
	{
		makeFall();
	}
	
	if( dead != 2 )
	{
		sprite[ which ]->setOffset( offset /delay );
	}
	
	
	if( !fallen )
	{
		window->draw( sprite[ which ]->get() );
	}
	
	if( dead != 2 )
	{
		if( climb == 1 || ( climb == 0 && which != CLIMB ) )
		{
			offset ++;
		}
		//printf( "%d\n", offset );
		if( offset == (sprite.size()-1) *delay || ( dead == 1 && offset == (sprite.size()-1) *delay-1 ) )
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
	
	
	
	
	/*
	if( which == ATTACK )
	{
		if( right )
			box.setPosition( ( sprite[ ATTACK ].getWidth() -box.getWidth() ) + sprite[ ATTACK ].getX(), sprite[ ATTACK ].getY() );
		else
			box.setPosition( sprite[ ATTACK ].getX() -sprite[ ATTACK ].getWidth(), sprite[ ATTACK ].getY() );
		window->draw( box.get() );
	}
	
	if( which == JUMP_ATTACK )
	{
		if( right )
			jumpBox.setPosition( ( sprite[ JUMP_ATTACK ].getWidth() -box.getWidth() ) + sprite[ JUMP_ATTACK ].getX(), sprite[ JUMP_ATTACK ].getY() );
		else
			jumpBox.setPosition( sprite[ JUMP_ATTACK ].getX() -sprite[ JUMP_ATTACK ].getWidth(), sprite[ JUMP_ATTACK ].getY() );
		window->draw( jumpBox.get() );
	}
	*/
}



void Hero::fadein( int v, int max )
{
	for( auto &i :sprite )
	{
		i->fadein( v, max );
	}
}

void Hero::fadeout( int v, int min )
{
	for( auto &i :sprite )
	{
		i->fadeout( v, min );
	}
}


int Hero::strToInt( string s )
{
    bool m = false;
    int tmp = 0;
    unsigned i = 0;
	
    if (s[ 0 ] == '-' )
    {
          i++;
          m = true;
    }
	
    while( i < s.size() )
    {
      tmp = 10*tmp+s[ i ] -48;
      i++;
    }
	
    return m ? -tmp : tmp;   
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


const int Hero::getX()
{
	int x = 0;
	
	x = sprite[ IDLE ]->getX();
	
	if( !right )
	{
		x -= getW();
	}
	
	return x;
}

const int Hero::getY()
{
	if( which == SLIDE )
		return sprite[ SLIDE ]->getY();
	
	return sprite[ IDLE ]->getY();
}

const int Hero::getW()
{
	return sprite[ IDLE ]->getWidth();
}

const int Hero::getH()
{
	if( which == SLIDE )
		return sprite[ SLIDE ]->getHeight();
	
	return sprite[ IDLE ]->getHeight();
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

bool Hero::checkFall( int screen_h )
{
	if( getY() > screen_h +getH()/2 && !fallen )
	{
		fallen = true;
		return true;
	}
	
	return false;
}

void Hero::setFallenY( int y )
{
	fallenY = y -sprite[ IDLE ]->getHeight() -40;
}

bool Hero::isFallen()
{
	return fallen;
}

void Hero::undoFallX( sf::Uint8 add )
{
	for( auto &i :sprite )
	{
		i->setPosition( i->getX() -add, i->getY() );
	}
}

void Hero::undoFallY()
{
	if( fallenY < sprite[ IDLE ]->getY() && fallenY != -1 )
	{
		for( auto &i :sprite )
		{
			i->setPosition( i->getX(), i->getY() -10 );
		}
	}
	else
	{
		fallenY = -1;
	}
}

void Hero::runFallenCounter()
{
	if( fallen )
	{
		fallen = !fallen;
		fallenCounter = 1;
	}
}



void Hero::makeFall()
{
	if( fallenCounter > 0 && !fallen )
	{
		fallenCounter ++;
		
		if( fallenCounter%60 == 0 )	// 1 sec
		{
			if( sprite[ IDLE ]->getAlpha() == 100 )
			{
				for( auto &i :sprite )
				{
					i->setAlpha( 0xFF );
				}
			}
			else
			{
				for( auto &i :sprite )
				{
					i->setAlpha( 100 );
				}
			}
		}
	}
	
	if( fallenCounter == fallenLine )
	{
		fallenCounter = 0;
		for( auto &i :sprite )
		{
			i->setAlpha( 0xFF );
		}
	}
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
			offset = (sprite.size()-1)*delay -1;
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
	int t_x = sprite[ IDLE ]->getX();
	if( !right )	t_x -= sprite[ IDLE ]->getWidth();
	
	int t_y = sprite[ IDLE ]->getY();
	int t_w = sprite[ IDLE ]->getWidth();
	int t_h = sprite[ IDLE ]->getHeight();
	
	
	Rect* rect = new Rect;
	rect->set( t_x, t_y, t_w, t_h );
	return rect;
}

void Hero::reset( int posY )
{
	int startX = 100;
	int startY = posY -sprite[ IDLE ]->getHeight() -400;
	
	while( true )
	{
		if( sprite[ IDLE ]->getX() > startX )
		{
			for( auto &i :sprite )
			{
				i->setPosition( i->getX() -1, i->getY() );
			}
		}
		else
		{
			break;
		}
	}
	
	while( true )
	{
		if( sprite[ IDLE ]->getY() > startY )
		{
			for( auto &i :sprite )
			{
				i->setPosition( i->getX(), i->getY() -1 );
			}
		}
		else
		{
			break;
		}
	}
	
	which = IDLE;
	dead = 0;
}