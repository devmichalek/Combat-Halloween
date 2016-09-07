#include "game_timer.h"

Game_timer::Game_timer()
{
	max = 0;
	counter = 0;
	flag = false;
	paused = false;
}

Game_timer::~Game_timer()
{
	free();
}

void Game_timer::free()
{
	one.free();
	two.free();
	
	text.free();
	max = 0;
	counter = 0.0000;
	flag = false;
	paused = false;
}
	
bool Game_timer::load( int screen_w )
{
	free();
	
	text.setFont( "intro/Jaapokki-Regular.otf", 20, 0xFF, 0xFF, 0xFF );

	text.setText( to_string( counter ) );

	text.setPosition( screen_w - text.getWidth() -10, 10 );
	
	max = 30.0;
	
	one.load( "pause/0.png" );
	one.setPosition( 10, 10 );
		
	two.load( "pause/1.png" );
	two.setPosition( 10, 10 );
	
	return true;
}

void Game_timer::count( int screen_w )
{
	if( !paused )
	{
		text.setText( to_string( counter ) );
		text.setPosition( screen_w - text.getWidth() -10, 10 );
		
		counter += 0.02;
		if( counter >= max )
		{
			counter = 0.0;
			flag = true;
		}
		else
			flag = false;
	}
}

void Game_timer::draw( sf::RenderWindow &window )
{
	window.draw( text.get() );
	
	if( paused )
		window.draw( two.get() );
	else
		window.draw( one.get() );
}

void Game_timer::handle( sf::Event &event )
{
	static bool rel = false;
	if( event.type == sf::Event::KeyPressed && !rel )
	{
		if( event.key.code == sf::Keyboard::P )
		{
			rel = true;
			paused = !paused;
		}
	}
	else if( event.type == sf::Event::KeyReleased )
	{
		if( event.key.code == sf::Keyboard::P )
		{
			rel = false;
		}
	}
}

	
bool Game_timer::isPaused()
{
	return paused;
}

bool Game_timer::newWall()
{
	return flag;
}

void Game_timer::fadein( int i, int max )
{
	text.fadein( i, max );
	one.fadein( i, max );
	two.fadein( i, max );
}

void Game_timer::fadeout( int i, int min )
{
	text.fadeout( i, min );
	one.fadeout( i, min );
	two.fadeout( i, min );
}
