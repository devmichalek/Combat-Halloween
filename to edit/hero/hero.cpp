#include "hero/hero.h"
#include <fstream>

Activity::Activity()
{
	line = 0;
	counter = 0;
	active = false;
}

Activity::~Activity()
{
	free();
}

void Activity::free()
{
	line = 0;
	counter = 0;
	active = false;
}

void Activity::summarize()
{
	if( counter >= line )	counter = 0;
	else if( counter > 0 )	counter++;
}




void Hero::fadein( int v, int max )
{
	for( int i = 0; i < nr; i++ )
		sprite[ i ].fadein( v, max );
}

void Hero::fadeout( int v, int min )
{
	for( int i = 0; i < nr; i++ )
		sprite[ i ].fadeout( v, min );
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

bool Hero::checkKey( int a )
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( a ) ) )
		return true;
	
	return false;
}

bool Hero::checkKeys( int a, int b )
{
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( a ) ) && b == -1 )
		return true;
	else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( a ) ) )
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( b ) ) )
			return true;
	return false;
}




Hero::Hero()
{
	nr = 0;
	sprite = NULL;
	
	vel = 0;
	which = 0;
	offset = 0;
	delay = 0;
	right = true;
	gravity = 0;
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
		nr = 0;
	}
	
	vel = 0;
	which = 0;
	offset = 0;
	delay = 0;
	right = true;
	gravity = 0;
	
	for( unsigned i = 0; i < keys.size(); i++ )
	{
		if( keys[ i ] != NULL )
		{
			delete [] keys[ i ];
			keys[ i ] = NULL;
		}
	}
	keys.clear();
	
	j.free();
	a.free();
}



	
void Hero::load( int& screen_w, int& y, string path )
{
	free();
	
	
	nr = STRENGTH +1;
	sprite = new MySprite [ nr ];
	for( int i = 0; i < nr; i++ )
	{
		sprite[ i ].setName( "hero-sprite nr " + to_string( i ) );
		sprite[ i ].load( path + to_string( i ) + ".png", STRENGTH );
		sprite[ i ].setScale( 0.25, 0.25 );
		sprite[ i ].setPosition( 10, y -sprite[ i ].getHeight() -124 );
	}
	sprite[ ATTACK ].setPosition( sprite[ ATTACK ].getX(), sprite[ ATTACK ].getY() + 10 );
	
	
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
	
	
	vel = 1;
	which = IDLE;
	offset = 0;
	delay = 6;
	right = true;
	gravity = 1;
	
	
	j.line = STRENGTH*delay + 10*delay;
	a.line = STRENGTH*delay + 2*delay;
}

void Hero::draw( sf::RenderWindow* &window )
{
	window->draw( sprite[ which ].get() );
	
	sprite[ which ].setOffset( offset /delay );
	
	offset ++;
	if( offset == STRENGTH *delay )
	{
		offset = 0;
		
		j.active = false;
		a.active = false;
	}
}




void Hero::idle()
{
	which = IDLE;
}

bool Hero::moveLeft()
{
	if( checkKeys( keys[ 0 ][ 0 ], keys[ 0 ][ 1 ] ) )
	{
		which = RUN;
		
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setScale( -0.25, 0.25 );
			sprite[ i ].setPosition( sprite[ i ].getX() -vel, sprite[ i ].getY() );
		}
		
		if( right )
		{
			for( int i = 0; i < nr; i++ )
				sprite[ i ].setPosition( sprite[ i ].getX() + (sprite[ i ].getWidth()*-1), sprite[ i ].getY() );
				
			right = false;
		}
		
		return true;
	}
	
	return false;
}

bool Hero::moveRight()
{
	if( checkKeys( keys[ 1 ][ 0 ], keys[ 1 ][ 1 ] ) )
	{
		which = RUN;
		
		for( int i = 0; i < nr; i++ )
		{
			sprite[ i ].setScale( 0.25, 0.25 );
			sprite[ i ].setPosition( sprite[ i ].getX() +vel, sprite[ i ].getY() );
		}
		
		if( !right )
		{
			for( int i = 0; i < nr; i++ )
				sprite[ i ].setPosition( sprite[ i ].getX() - sprite[ i ].getWidth(), sprite[ i ].getY() );
				
			right = true;
		}
		
		return true;
	}
	
	return false;
}



bool Hero::jump()
{
	if( j.counter == 0 && checkKeys( keys[ 2 ][ 0 ], keys[ 2 ][ 1 ] ) )
	{
			offset = 0;
			j.counter = 1;
			j.active = true;
	}
	else if( j.active )
	{
		which = JUMP;
		
		if( right )
		{
			for( int i = 0; i < nr; i++ )
				sprite[ i ].setPosition( sprite[ i ].getX() +vel*2, sprite[ i ].getY() );
		}
		else
		{
			for( int i = 0; i < nr; i++ )
				sprite[ i ].setPosition( sprite[ i ].getX() -vel*2, sprite[ i ].getY() );
		}
	}
	
	j.summarize();
	
	return j.active;	
}

bool Hero::attack()
{
	if( a.counter == 0 && checkKeys( keys[ 7 ][ 0 ], keys[ 7 ][ 1 ] ) )
	{
		offset = 0;
		a.counter = 1;
		a.active = true;
		
		if( !right )
			sprite[ ATTACK ].setPosition( sprite[ RUN ].getX(), sprite[ ATTACK ].getY() );
	}
	else if( a.active )
	{
		which = ATTACK;
	}
	else
	{
		if( !right )
			sprite[ ATTACK ].setPosition( sprite[ RUN ].getX() + 44, sprite[ ATTACK ].getY() );
	}
	
	a.summarize();
	
	return a.active;
}