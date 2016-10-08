#include "choice.h"
#include <time.h>
#include <cstdlib>

Choice::Choice()
{
	// empty
	counter = 0;
}

Choice::~Choice()
{
	sprite.free();
	text.free();
	number.free();
	counter = 0;
	click.free();
}


void Choice::load( int screen_w, int screen_h )
{
	text.setID( "choice-text" );
	text.setFont( "data/fonts/Jaapokki-Regular.otf", 50, 0xFF, 0xFF, 0xFF );
	text.setText( "Click to random world!" );
	text.setPosition( screen_w/2 -text.getWidth()/2, screen_h/2 - text.getHeight()/2 - 40 );
	
	sprite.setName( "choice-sprite" );
	sprite.load( "data/sprites/level/random.png", 4 );
	sprite.setScale( 0.4, 0.4 );
	sprite.setPosition( screen_w/2 -sprite.getWidth()/2 -100, screen_h/2 - sprite.getHeight()/2 );
	
	number.setID( "choice-number" );
	number.setFont( "data/fonts/Jaapokki-Regular.otf", 37, 0xFF, 0xFF, 0xFF );
	number.setText( "number" );
	number.setPosition( screen_w/2 -number.getWidth()/2, screen_h/2 - number.getHeight()/2 );
	
	click.setID( "choice-click" );
	click.load( "data/sounds/click.wav", 50 );
	
	srand( time( NULL ) );
}

void Choice::handle( sf::Event &event )
{
	if( sprite.getAlpha() == 255 && counter == 0 )
	{
		int x, y;
		sprite.setOffset( 0 );

		if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
				
			if( sprite.checkCollision( x, y ) )
				sprite.setOffset( 1 );
			else
				focus = false;
		}

		if( event.type == sf::Event::MouseButtonPressed )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
				
			if( sprite.checkCollision( x, y ) )
			{
				sprite.setOffset( 2 );
					
				if( play )
					click.play();
						
				focus = true;
				counter = 1;
				
			}
		}
			
		if( event.type == sf::Event::MouseButtonReleased )
			focus = false;
			
		if( focus )
			sprite.setOffset( 2 );
	}
}

void Choice::draw( sf::RenderWindow &window )
{
	window.draw( text.get() );
	window.draw( sprite.get() );
	window.draw( number.get() );
	
	if( counter > 0 && counter < 250 )
	{
		result = rand()%100000 +1;
		number.setText( to_string( result ) );
		number.reloadPosition();
		counter ++;
	}
}

void Choice::fadein( int i, int max )
{
	text.fadein( i, max );
	sprite.fadein( i, max );
	number.fadein( i, max );
}

void Choice::fadeout( int i, int min )
{
	text.fadeout( i, min );
	sprite.fadeout( i, min );
	number.fadeout( i, min );
}

bool Choice::isReady()
{
	if( counter > 250 )
		return true;
		
	return false;
}

int Choice::getResult()
{
	return result;
}
