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
	
	a = r = g = b = 0xFF;
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
	
	a = r = g = b = 0xFF;
}

void Day::reset()
{
	change = false;
	count = false;
	
	state = 0;
	counter = 0;
	sec = 0;
	
	a = r = g = b = 0xFF;
}



void Day::set( unsigned FPS )
{
	colors.push_back( sf::Color() );
	colors[ colors.size() -1 ].r = 0xFF;
	colors[ colors.size() -1 ].g = 0xFF;
	colors[ colors.size() -1 ].b = 0xFF;
	colors[ colors.size() -1 ].a = 0xFF;
	
	colors.push_back( sf::Color() );
	colors[ colors.size() -1 ].r = 0xFF;
	colors[ colors.size() -1 ].g = 0xF6;
	colors[ colors.size() -1 ].b = 0x6C;
	colors[ colors.size() -1 ].a = 0xBB;
	
	colors.push_back( sf::Color() );
	colors[ colors.size() -1 ].r = 0xFF;
	colors[ colors.size() -1 ].g = 0x9C;
	colors[ colors.size() -1 ].b = 0x00;
	colors[ colors.size() -1 ].a = 0x99;
	
	colors.push_back( sf::Color() );
	colors[ colors.size() -1 ].r = 0x19;
	colors[ colors.size() -1 ].g = 0x18;
	colors[ colors.size() -1 ].b = 0x18;
	colors[ colors.size() -1 ].a = 0x33;
	
	line = FPS;
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
	else if( state == 1 && sec == F && count )
	{
		counter = 0;
		sec = 0;
		state = 2;
		setInTime();
	}
	else if( state == 2 && sec == S && count )
	{
		counter = 0;
		sec = 0;
		state = 3;
		setInTime();
	}
	else if( state == 3 && sec == N && count )
	{
		counter = 0;
		sec = 0;
		state = 0;
		setInTime();
	}
	
	// printf( "%d %d %d | counter %d  sec %d  state %d\n", r, g, b, counter, sec, state );
	// printf( "%d %d %d\n", colors[ state ].r, colors[ state ].g, colors[ state ].b );
}


bool Day::isChange()
{
	if( change )
	{
		change = false;
		return true;
	}
	
	return false;
}

sf::Color Day::getColor()
{
	return sf::Color( r, g, b, a );
}

int Day::getAlpha()
{
	return a;
}

bool Day::isNight()
{
	if( state == 3 )
	{
		return true;
	}
	
	return false;
}