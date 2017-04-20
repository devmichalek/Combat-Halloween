#include "scroll.h"

Scroll::Scroll()
{
	free();
}

Scroll::~Scroll()
{
	free();
}

void Scroll::free()
{
	area.free();
	button.free();
	
	info.free();
	info_x = 0;
	
	handled = false;
	vel = 0;
	moved = false;
}

void Scroll::reset()
{
	handled = false;
	moved = false;
	button.setPosition( 0, area.getY() );
	info.setPosition( info_x -button.getX(), info.getY() );
}



void Scroll::load( int screen_w, int screen_h )
{
	free();
	
	area.setName( "scroll-area" );
	area.create( screen_w, 10 );
	area.setColor( sf::Color( 0x84, 0xA4, 0xC1 ) );
	area.setPosition( 0, screen_h -area.getHeight() );
	
	info.setName( "scroll-area" );
	info.load( "data/menu/scroll.png" );
	info_x = 20;
	info.setPosition( info_x, screen_h -info.getHeight() -20 );
	
	button.setName( "scroll-button" );
	button.create( screen_w /2, 10 );
	button.setColor( sf::Color( 0x0E, 0x2A, 0x44 ) );
	
	reset();
	
	vel = 25;
}

void Scroll::Scroll::draw( sf::RenderWindow* &window )
{
	window->draw( area.get() );
	window->draw( button.get() );
	window->draw( info.get() );
	
	if( moved )
	{
		info.setPosition( info_x -button.getX(), info.getY() );
		// printf( "%f\n", info.getX() );
	}
}

void Scroll::handle( sf::Event &event )
{
	moved = false;

	if( area.getAlpha() == 0xFF )
	{
		int x, y;
		
		if( event.type == sf::Event::MouseWheelScrolled )
		{
			if( event.mouseWheelScroll.delta > 0 )
			{
				button.setPosition( button.getX() -vel, button.getY() );
				if( button.getX() < area.getX() )
				{
					button.setPosition( area.getX(), button.getY() );
				}
			}
			else if( event.mouseWheelScroll.delta < 0 )
			{
				button.setPosition( button.getX() +vel, button.getY() );
				if( button.getRight() > area.getRight() )
				{
					button.setPosition( area.getRight() -button.getWidth(), button.getY() );
				}
			}
			
			moved = true;
		}
		
		else if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
			
			if( handled )
			{
				button.setPosition( x -button.getWidth() /2, button.getY() );
				moved = true;
				
				if( x -button.getWidth() /2 < area.getX() )
				{
					button.setPosition( area.getX(), button.getY() );
				}
				else if( x +button.getWidth() /2 > area.getRight() )
				{
					button.setPosition( area.getRight() -button.getWidth(), button.getY() );
				}
			}
		}

		else if( event.type == sf::Event::MouseButtonPressed )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
				
			if( area.checkCollision( x, y ) )
			{
				button.setPosition( x -button.getWidth() /2, button.getY() );
				handled = true;
				moved = true;
				
				if( x -button.getWidth() /2 < area.getX() )
				{
					button.setPosition( area.getX(), button.getY() );
				}
				else if( x +button.getWidth() /2 > area.getRight() )
				{
					button.setPosition( area.getRight() -button.getWidth(), button.getY() );
				}
			}
		}
		
		else if( event.type == sf::Event::MouseButtonReleased )
		{
			handled = false;
		}
	}
}



bool Scroll::isMoved()
{
	return moved;
}

float Scroll::getDistance()
{
	return -button.getX();
}


void Scroll::fadein( int i, int max )
{
	area.fadein( i, max );
	button.fadein( i, max );
	info.fadein( i, max );
}

void Scroll::fadeout( int i, int min )
{
	area.fadeout( i, min );
	button.fadeout( i, min );
	info.fadeout( i, min );
}