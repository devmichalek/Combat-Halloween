#include "select.h"
#include <stdio.h>

Select::Select()
{
	money = 0;
	open = NULL;
	level = NULL;
	nr = 0;
	
	counter = 0;
}

Select::~Select()
{
	money = 0;
	counter = 0;
	
	if( open != NULL )
	{
		delete [] open;
	}
	
	if( level != NULL )
	{
		delete [] level;
		level = NULL;
		
		nr = 0;
	}
}

void Select::load( int screen_w, int screen_h )
{
	nr = 16;
	level = new Level [ nr ];
	
	level[ 0 ].load( 0, 25 );
	level[ 1 ].load( 1, 35 );
	level[ 2 ].load( 2, 50 );
	level[ 3 ].load( 3, 90 );
	
	level[ 4 ].load( 4, 220 );
	level[ 5 ].load( 5, 320 );
	level[ 6 ].load( 6, 480 );
	level[ 7 ].load( 7, 800 );
	
	level[ 8 ].load( 8, 1600 );
	level[ 9 ].load( 9, 3400 );
	level[ 10 ].load( 10, 5700 );
	level[ 11 ].load( 11, 9000 );
	
	level[ 12 ].load( 12, 21000 );
	level[ 13 ].load( 13, 62000 );
	level[ 14 ].load( 14, 73200 );
	level[ 15 ].load( 15, 240000 );
	
	
	int wPos = ( screen_w - ( level[ 0 ].getWidth()*4 ) -80*3 ) / 2;
	int hei = 2;
	level[ 0 ].setXY( wPos, 240 );
	
	for( int i = 1; i < nr; i++ )
	{
		if( i%4 == 0 )
		{
			hei = i/4 +2;
			level[ i ].setXY( wPos, 120*hei );
		}
		else if( i < 4 )
			level[ i ].setXY( level[ i -1 ].getX() + level[ i -1 ].getWidth() + 80, 240*(hei-1) );
		else
			level[ i ].setXY( level[ i -1 ].getX() + level[ i -1 ].getWidth() + 80, 120*hei );	
	}
}

void Select::draw( sf::RenderWindow* &window )
{
	for( int i = 0; i < nr; i++ )
	{
		level[ i ].draw( window );
	}
}

void Select::handle( sf::Event &event )
{
	for( int i = 0; i < nr; i++ )
	{
		level[ i ].handle( event, money );
	}
}

	
void Select::fadein( int i, int max )
{
	level[ counter ].fadein( i +10, max );
	
	if( level[ counter ].getAlpha() == 255 && counter <= nr -1 )
		counter ++;
}

void Select::fadeout( int i, int min )
{
	for( int j = 0; j < nr; j++ )
	{
		level[ j ].fadeout( i, min );
	}
}

	
void Select::turn()
{
	for( int j = 0; j < nr; j++ )
	{
		level[ j ].turn();
	}
}

void Select::setVolume( sf::Uint8 volume )
{
	for( int j = 0; j < nr; j++ )
	{
		level[ j ].setVolume( volume );
	}
}
