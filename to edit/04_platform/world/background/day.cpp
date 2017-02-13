#include "04_platform/world/background/day.h"
#include <stdio.h>

Day::Day()
{
	change = false;
	count = false;
	
	state = 0;
	counter = 0;
	sec = 0;
	line = 0;
	
	r = g = b = 0xFF;
	a = 0;
}

Day::~Day()
{
	free();
}

void Day::free()
{
	change = false;
	count = false;
	
	state = 0;
	counter = 0;
	sec = 0;
	line = 0;
	
	if( !colors.empty() )
	{
		colors.clear();
	}
	
	r = g = b = 0xFF;
	a = 0;
	
	overlay.free();
}

void Day::reset( Rect* rect )
{
	change = false;
	count = false;
	
	state = 0;
	counter = 0;
	sec = 0;
	
	r = g = b = 0xFF;
	a = 0;
	
	overlay.setColor( colors[ 0 ] );
	overlay.setAlpha( colors[ 0 ].a );
}



void Day::load( int screen_w, int screen_h )
{
	colors.push_back( sf::Color() );
	colors[ colors.size() -1 ].r = 0x00;
	colors[ colors.size() -1 ].g = 0x00;
	colors[ colors.size() -1 ].b = 0x00;
	colors[ colors.size() -1 ].a = 0x00;
	
	colors.push_back( sf::Color() );
	colors[ colors.size() -1 ].r = 0xA9;
	colors[ colors.size() -1 ].g = 0x38;
	colors[ colors.size() -1 ].b = 0x00;
	colors[ colors.size() -1 ].a = 170;
	
	colors.push_back( sf::Color() );
	colors[ colors.size() -1 ].r = 0x19;
	colors[ colors.size() -1 ].g = 0x18;
	colors[ colors.size() -1 ].b = 0x18;
	colors[ colors.size() -1 ].a = 235;
	
	overlay.setName( "day-overlay" );
	overlay.create( screen_w, screen_h );
	overlay.setColor( colors[ 0 ] );
	overlay.setAlpha( colors[ 0 ].a );

	line = 120;
}

void Day::draw( sf::RenderWindow* &window )
{
	window->draw( overlay.get() );
}

void Day::setInTime()
{
	count = false;
	int which = 0;

	if( state != colors.size()-1 )
	{
		which = state +1;
	}
	
	
	if( r < colors[ which ].r )
	{
		r++;
		change = true;
	}
	else if( r > colors[ which ].r )
	{
		r--;
		change = true;
	}
	
	if( g < colors[ which ].g )
	{
		g++;
		change = true;
	}
	else if( g > colors[ which ].g )
	{
		g--;
		change = true;
	}
	
	if( b < colors[ which ].b )
	{
		b++;
		change = true;
	}
	else if( b > colors[ which ].b )
	{
		b--;
		change = true;
	}
	
	
	if( !change || state != 1 )
	{
		if( a < colors[ which ].a )
		{
			a++;
			change = true;
		}
		else if( a > colors[ which ].a )
		{
			a--;
			change = true;
		}
	}
}

void Day::mechanics()
{
	counter ++;
	
	if( counter == line )
	{
		counter = 0;
		sec ++;
		
		int which = 0;

		if( state != colors.size()-1 )
		{
			which = state +1;
		}
		
		if( r == colors[ which ].r &&
			g == colors[ which ].g &&
			b == colors[ which ].b &&
			a == colors[ which ].a )
		{
			if( !count )
			{
				counter = 0;
				sec = 0;
				count = true;
			}
		}
		else if( !count )
		{
			setInTime();
		}
	}
	
	if( state == 0 && sec == I && count )
	{
		counter = 0;
		sec = 0;
		state = 1;
		setInTime();
	}
	else if( state == 1 && sec == S && count )
	{
		counter = 0;
		sec = 0;
		state = 2;
		setInTime();
	}
	else if( state == 2 && sec == N && count )
	{
		counter = 0;
		sec = 0;
		state = 0;
		setInTime();
	}
	
	if( change )
	{
		change = false;
		overlay.setColor( sf::Color( r, g, b ) );
		overlay.setAlpha( a );
	}
	
	// printf( "%d %d %d | counter %d  sec %d  state %d\n", r, g, b, counter, sec, state );
}