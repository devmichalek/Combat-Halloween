#include "hero/hero.h"
#include <fstream>


Hero::Hero()
{
	sprite = NULL;
	
	which = 0;
	offset = 0;
	delay = 0;
	
	
	vel = 0;
	jVel = 0;
	grav = 0;
	scale = 0;
	
	
	flag = false;
	right = false;
	
	glide = false;
	
	slide = false;
}

Hero::~Hero()
{
	free();
}

void Hero::free()
{
	if( sprite != NULL )
	{
		for( int i = 0; i < nr; i ++ )
		{
			sprite[ i ].free();
		}
		
		delete [] sprite;
		sprite = NULL;
	}
	
	which = 0;
	offset = 0;
	delay = 0;
	
	for( unsigned i = 0; i < keys.size(); i++ )
	{
		if( keys[ i ] != NULL )
		{
			delete [] keys[ i ];
			keys[ i ] = NULL;
		}
	}
	
	keys.clear();
	
	vel = 0;
	jVel = 0;
	grav = 0;
	scale = 0;
	
	flag = false;
	right = false;
	
	glide = false;
	
	slide = false;
	
	a.free();
	ja.free();
}



void Hero::load( int& screen_w, int& posY, string path )
{
	free();
	
	// 	Set scale.
	scale = 0.5;
	
	// Create array.
	sprite = new MySprite [ nr ];
	
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].setName( "hero-sprite[" + to_string( i ) + "]" );
		sprite[ i ].load( path + to_string( i ) + ".png", nr -1 );
		sprite[ i ].setScale( scale, scale );
		sprite[ i ].setPosition( 45, posY -sprite[ i ].getHeight() -500 );
	}
	sprite[ JUMP_ATTACK ].setPosition( sprite[ JUMP_ATTACK ].getX(), sprite[ JUMP_ATTACK ].getY() + ( sprite[ JUMP_ATTACK ].getHeight() - sprite[ IDLE ].getHeight() ) );
	
	// Start values.
	which = IDLE;
	offset = 0;
	delay = 6;
	
	
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
		for( int i = 0; i < nr; i ++ )
		{
			int* arrow;
			keys.push_back( arrow );
			keys[ i ] = new int[ 2 ];
			
			file >> line;	keys[ i ][ 0 ] = strToInt( line );
			file >> line;	keys[ i ][ 1 ] = strToInt( line );
		}
	}
	file.close();
	
	
	
	
	
	// Set other values
	vel = 1;
	jVel = vel*2;
	grav = 1;
	right = true;
	
	

	// Duration
	j.setLine( (nr-1)*delay + 10*delay );
	a.setLine( (nr-1)*delay + 2*delay );
	ja.setLine( j.getLine() );
}

void Hero::draw( sf::RenderWindow* &window )
{
	window->draw( sprite[ which ].get() );
	
	sprite[ which ].setOffset( offset /delay );
	
	offset ++;
	if( offset == (nr-1) *delay )
	{
		offset = 0;
		j.setActive( false );
		a.setActive( false );
		ja.setActive( false );
	}
	
	// printf( "X %d   Y %d  W %d   H %d\n", getX(), getY(), getW(), getH() );
}




void Hero::idle()
{
	if( !glide  && !slide )
	{
		which = IDLE;
	}
}

bool Hero::move()
{
	// move left
	if( checkKeys( keys[ 0 ][ 0 ], keys[ 0 ][ 1 ] ) )
	{
		if( !glide && !slide )
		{
			which = RUN;
		}
		
		flag = true;
		
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setScale( -scale, scale );
			sprite[ i ].setPosition( sprite[ i ].getX() -vel, sprite[ i ].getY() );
		}
		
		if( right )
		{
			for( int i = 0; i < nr; i++ )
			{
				if( i != IDLE )
				{
					sprite[ i ].setPosition( sprite[ IDLE ].getX() + ( sprite[ i ].getWidth()*-1 ), sprite[ i ].getY() );
				}
			}
			
			sprite[ IDLE ].setPosition( sprite[ IDLE ].getX() + ( sprite[ IDLE ].getWidth()*-1 ), sprite[ IDLE ].getY() );
			sprite[ ATTACK ].setPosition( sprite[ IDLE ].getX(), sprite[ IDLE ].getY() );
			sprite[ GLIDE ].center( sprite[ IDLE ].getX(), sprite[ IDLE ].getY(), sprite[ IDLE ].getWidth(), sprite[ IDLE ].getHeight() );
			sprite[ SLIDE ].setPosition( sprite[ IDLE ].getX(), sprite[ SLIDE ].getY() );
			sprite[ JUMP_ATTACK ].setPosition( sprite[ IDLE ].getX(), sprite[ JUMP_ATTACK ].getY() );
			
			right = false;
		}
		
		return true;
	}
	
	// move right
	else if( checkKeys( keys[ 1 ][ 0 ], keys[ 1 ][ 1 ] ) ) 
	{
		if( !glide && !slide )
		{
			which = RUN;
		}
		
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setScale( scale, scale );
			sprite[ i ].setPosition( sprite[ i ].getX() +vel, sprite[ i ].getY() );
		}
		
		if( !right )
		{
			if( flag )
			{
				for( int i = 0; i < nr; i++ )
				{
					sprite[ i ].setPosition( sprite[ i ].getX() - ( sprite[ i ].getWidth() ), sprite[ i ].getY() );
				}
			}
			
			for( int i = 0; i < nr; i++ )
			{
				if( i != IDLE )
				{
					sprite[ i ].setPosition( sprite[ IDLE ].getX() - ( sprite[ i ].getWidth() -sprite[ IDLE ].getWidth() ), sprite[ i ].getY() );
				}
			}
			
			sprite[ ATTACK ].setPosition( sprite[ IDLE ].getX(), sprite[ IDLE ].getY() );
			sprite[ GLIDE ].center( sprite[ IDLE ].getX(), sprite[ IDLE ].getY(), sprite[ IDLE ].getWidth(), sprite[ IDLE ].getHeight() );
			sprite[ SLIDE ].setPosition( sprite[ IDLE ].getX(), sprite[ SLIDE ].getY() );
			sprite[ JUMP_ATTACK ].setPosition( sprite[ IDLE ].getX(), sprite[ JUMP_ATTACK ].getY() );
				
			right = true;
		}
		
		return true;
	}
	
	return false;
}

bool Hero::jump()
{
	if( checkKeys( keys[ 2 ][ 0 ], keys[ 2 ][ 1 ] ) && j.Do() && !glide )
	{
		offset = 0;
		j.start();
		j.setActive( true );
		which = JUMP;
	}
	
	if( j.isActive() )
	{
		which = JUMP;
		
		if( right )
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setPosition( sprite[ i ].getX() +jVel, sprite[ i ].getY() );
			}
		}
		else
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setPosition( sprite[ i ].getX() -jVel, sprite[ i ].getY() );
			}
		}
	}
	
	j.check();
	
	return j.isActive();	
}

bool Hero::attack()
{
	if( checkKeys( keys[ 5 ][ 0 ], keys[ 5 ][ 1 ] ) && a.Do() && !glide && !j.isActive() )
	{
		offset = 0;
		a.start();
		a.setActive( true );
		which = ATTACK;
		sprite[ ATTACK ].setPosition( sprite[ RUN ].getX(), sprite[ RUN ].getY() +2 );
	}
	
	if( a.isActive() )
	{
		which = ATTACK;
	}
	
	a.check();
	
	return a.isActive();
}

void Hero::gliding()
{
	which = GLIDE;
}

void Hero::sliding()
{
	if( checkKeys( keys[ 3 ][ 0 ], keys[ 3 ][ 1 ] ) )
	{
		if( !glide )
		{
			slide = true;
			which = SLIDE;
		}
	}
	else
	{
		slide = false;
	}
}

bool Hero::jumpAttack()
{
	if( checkKeys( keys[ 7 ][ 0 ], keys[ 7 ][ 1 ] ) && ja.Do() && !glide && !j.isActive() && !a.isActive() )
	{
		offset = 0;
		ja.start();
		ja.setActive( true );
		which = JUMP_ATTACK;
	}
	
	if( ja.isActive() )
	{
		which = JUMP_ATTACK;
		
		if( right )
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setPosition( sprite[ i ].getX() +jVel, sprite[ i ].getY() );
			}
		}
		else
		{
			for( int i = 0; i < nr; i++ )
			{
				sprite[ i ].setPosition( sprite[ i ].getX() -jVel, sprite[ i ].getY() );
			}
		}
	}
	
	ja.check();
	
	return ja.isActive();
}



void Hero::undoMove()
{
	// undo move right
	if( right )
	{
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setPosition( sprite[ i ].getX() -vel, sprite[ i ].getY() );
		}
	}
	
	// undo move left
	else
	{
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setPosition( sprite[ i ].getX() +vel, sprite[ i ].getY() );
		}
	}
}

void Hero::undoJump()
{
	if( right )
	{
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setPosition( sprite[ i ].getX() -jVel, sprite[ i ].getY() );
		}
	}
	else
	{
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setPosition( sprite[ i ].getX() +jVel, sprite[ i ].getY() );
		}
	}
}



void Hero::gravitation()
{
	if( !j.isActive() )
	{
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setPosition( sprite[ i ].getX(), sprite[ i ].getY() +grav );
		}
		
		glide = true;
	}
	else
	{
		glide = false;
	}
}

void Hero::weightlessness()
{
	glide = false;
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].setPosition( sprite[ i ].getX(), sprite[ i ].getY() -grav );
	}
}




const int Hero::getX()
{
	int x = 0;
	
	x = sprite[ IDLE ].getX();
	
	if( which == GLIDE )
	{
		x = sprite[ GLIDE ].getX();
	}
	
	if( !right )
	{
		x -= getW();
	}
	
	return x;
}

const int Hero::getY()
{
	int y = 0;
	
	y = sprite[ IDLE ].getY();
	
	return y;
}

const int Hero::getW()
{
	int w = 0;
	
	w = sprite[ IDLE ].getWidth();
	
	if( which == GLIDE )
	{
		w = sprite[ GLIDE ].getWidth();
	}
	
	if( w < 0 )
	{
		w = -w;
	}
	
	return w;
}

const int Hero::getH()
{
	int h = 0;
	
	h = sprite[ IDLE ].getHeight();
	
	return h;
}


void Hero::fadein( int v, int max )
{
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].fadein( v, max );
	}
}

void Hero::fadeout( int v, int min )
{
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].fadeout( v, min );
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