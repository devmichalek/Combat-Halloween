#include "choice.h"
#include <time.h>
#include <cstdlib>

Choice::Choice()
{
	nr = 0;
	world = NULL;
	
	counter = -1;
	result = -1;
	chosen = -1;
	
	range = 0;
}

Choice::~Choice()
{
	button.free();
	text.free();
	
	if( world != NULL )
	{
		for( sf::Uint8 i = 0; i < nr; i ++ )
			world[ i ].free();
		
		delete [] world;
		world = NULL;
		nr = 0;
	}
	
	frame.free();
	
	information.free();
	
	click.free();
	
	counter = -1;
	result = -1;
	chosen = -1;
	
	range = 0;
}


void Choice::load( int screen_w, int screen_h )
{
	button.setName( "choice-button" );
	button.load( "data/sprites/level/random.png", 4 );
	button.setScale( 0.4, 0.4 );
	
	text.setName( "choice-text" );
	text.setFont( "data/fonts/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	text.setText( "Choose world or " );
	text.setPosition( screen_w/2 -text.getWidth()/2 -button.getWidth(), screen_h/4 - text.getHeight()/2 -80 );
	button.setPosition( text.getRight() +10, text.getY() -5 );
	
	
	information.setName( "choice-information" );
	information.setFont( "data/fonts/Jaapokki-Regular.otf", 20, 0xFF, 0xFF, 0xFF );
	information.setText( "Tip: Following worlds will be generated randomly." );
	information.setPosition( 10, screen_h - information.getHeight() - 10 );
	
	
	// worlds
	nr = 4;
	world = new MySprite[ nr ];
	
	for( sf::Uint8 i = 0; i < nr; i ++ )
	{
		world[ i ].setName( "choice-world[ " + to_string( i ) + " ]" );
		world[ i ].load( "data/sprites/level/" + to_string( i ) + ".png" );
		world[ i ].setScale( 0.2, 0.2 );
	}
	
	int w = world[ 0 ].getWidth()*4 + 15*4;
	
	world[ 0 ].setPosition( screen_w/2 - w/2, button.getY() +90 );
	world[ 1 ].setPosition( world[ 0 ].getRight() + 15, button.getY() +90 );
	world[ 2 ].setPosition( world[ 1 ].getRight() + 15, button.getY() +90 );
	world[ 3 ].setPosition( world[ 2 ].getRight() + 15, button.getY() +90 );
	

	
	click.setID( "choice-click" );
	click.load( "data/sounds/click.wav", 50 );
	
	frame.setName( "choice-frame" );
	frame.load( "data/sprites/level/frame.png" );
	frame.setScale( 0.2, 0.2 );
	frame.setPosition( -1000, -1000 );
	
	range = 0;
}

void Choice::handle( sf::Event &event )
{
	chosen = -1;
	
	if( button.getAlpha() == 0xFF && counter == -1 )
	{
		int x, y;
		button.setOffset( 0 );

		if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
				
			if( button.checkCollision( x, y ) )
				button.setOffset( 1 );
			else
				focus = false;
				
			for( sf::Uint8 i = 0; i < nr; i++ )
			{
				if( world[ i ].checkCollision( x, y ) )
					chosen = i;
				else
					frame.setPosition( -1000, -1000 );
			}
		}

		if( event.type == sf::Event::MouseButtonPressed )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
				
			if( button.checkCollision( x, y ) )
			{
				button.setOffset( 2 );
					
				if( play )
					click.play();
						
				focus = true;
				counter = 0;
				
			}
			
			for( int i = 0; i < nr; i++ )
			{
				if( world[ i ].checkCollision( x, y ) )
				{
					if( play )
						click.play();
					
					result = i;
				}
			}
		}
			
		if( event.type == sf::Event::MouseButtonReleased )
			focus = false;
			
		if( focus )
			button.setOffset( 2 );
	}
}

void Choice::draw( sf::RenderWindow &window )
{
	window.draw( text.get() );
	window.draw( button.get() );
	window.draw( information.get() );
	
	for( int i = 0; i < nr; i ++ )
	{
		window.draw( world[ i ].get() );
	}
	
	if( world[ 0 ].getAlpha() > 99 )
	for( int i = 0; i < nr; i ++ )
	{
		if( i != result && i != chosen )
			world[ i ].setAlpha( 100 );
		else
		{
			world[ i ].setAlpha( 255 );
			frame.setPosition( world[ i ].getX(), world[ i ].getY() );
		}
			
	}
	
	if( counter > -1 && counter < 150 )
	{
		if( counter %7 == 0 )
			result = rand()%4;
		counter ++;
	}
		
	window.draw( frame.get() );
}

void Choice::fadein( int j, int max )
{
	frame.fadein( j, max );
	text.fadein( j, max );
	button.fadein( j, max );
	information.fadein( j, max );
	
	for( int i = 0; i < nr; i ++ )
		world[ i ].fadein( j, 100 );
}

void Choice::fadeout( int j, int min )
{
	text.fadeout( j, min );
	button.fadeout( j, min );
	information.fadeout( j, min );
	frame.fadeout( j, min );

	if( result != -1 )
		world[ result ].fadeout( j, min );
		

	if( text.getAlpha() < 100 )
	{
		for( int i = 0; i < nr; i ++ )
			world[ i ].fadeout( j, min );
	}
}

int Choice::getResult()
{
	return result;
}

sf::Uint8 Choice::getAlpha()
{
	return text.getAlpha();
}

bool Choice::isChosen()
{
	if( ( counter == 150 || counter == -1 ) && result != -1 )
		return true;
		
	return false;
}



void Choice::reset()
{
	counter = -1;
	result = -1;
	chosen = -1;
}

bool Choice::move( int vel, int ran )
{
	static bool continue_;
	continue_ = false;
	
	if( vel < 0 )
	{
		if( range > ran )
			continue_ = true;
	}
	else if( vel > 0 )
	{
		if( range < ran )
			continue_ = true;
	}
	
	if( continue_ )
	{
		range += vel;
		button.setPosition( button.getX() +vel, button.getY() );
		text.setPosition( text.getX() +vel, text.getY() );
		information.setPosition( information.getX() +vel, information.getY() );
		frame.setPosition( frame.getX() +vel, frame.getY() );
		for( int i = 0; i < nr; i++ )
			world[ i ].setPosition( world[ i ].getX() +vel, world[ i ].getY() );
	}
	else
		range = ran;
		
	if( range == ran )
		return true;
		
	return false;
}