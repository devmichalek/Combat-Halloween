/**
    reset_button.h
    Purpose: class Reset_button after click reset each txt file, all settings, all money getted etc.

    @author Adrian Michalek
    @version 2017.03.07
	@email adrmic98@gmail.com
*/

#include "reset_button.h"
#include <fstream>
#include <vector>

Reset_button::Reset_button()
{
	free();
}

Reset_button::~Reset_button()
{
	free();
}

void Reset_button::free()
{
	state = 0;
	
	mySprite.free();
	myText.free();
	
	play = true;
	click.free();
	
	button.free();
	reset = false;
}



void Reset_button::load( int screen_w, int screen_h )
{
	button.setName( "reset_button-button" );
    button.load( "data/02_menu/reset.png", 4 );
	button.setPosition( 10, screen_h -10 -button.getHeight()*2 );
	
	mySprite.setName( "reset_button-mySprite" );
    mySprite.load( "data/02_menu/exit.png" );
	mySprite.setAlpha( 0xFF );
	mySprite.center( 0, 0, screen_w, screen_h );

	myText.setName( "reset_button-myText" );
	myText.setFont( "data/02_menu/BADABB__.TTF", 33, 0xFF, 0xFF, 0xFF );
	myText.setText( "r-reset all data       b-back" );
	myText.setAlpha( 0xFF );
	myText.center( screen_w, screen_h, 0, -6 );

	click.setID( "exit_log-click" );
	click.load( "data/02_menu/click.wav", 50 );
}

void Reset_button::handle( sf::Event &event )
{
	static bool rel = false;
	
	if( event.type == sf::Event::KeyPressed && state > 0 )
	{
		if( !rel )
		{
			rel = true;
			if( event.key.code == sf::Keyboard::R )
			{
				if( play )
				{
					click.play();
				}
				
				reset = true;
			}
			else if( event.key.code == sf::Keyboard::B )
			{
				state = 0;
			}
		}
	}
	else if( event.type == sf::Event::KeyReleased )
	{
		rel = false;
	}
	
	if( button.getAlpha() == 0xFF )
	{
		int x, y;
		button.setOffset( 0 );

		if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
				
			if( button.checkCollision( x, y ) )
			{
				button.setOffset( 1 );
			}
			else
			{
				focus = false;
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
				{
					click.play();
				}
						
				focus = true;
				state = 1;
			}
		}
			
		if( event.type == sf::Event::MouseButtonReleased )
		{
			focus = false;
		}
			
		if( focus )
		{
			button.setOffset( 2 );
		}
	}
}

void Reset_button::draw( sf::RenderWindow* &window )
{
	if( state > 0 )
	{
		window->draw( mySprite.get() );
		window->draw( myText.get() );
	}
}

void Reset_button::drawButton( sf::RenderWindow* &window )
{
	window->draw( button.get() );
}



void Reset_button::fadein( int i, int max )
{
	mySprite.fadein( i, max );
	myText.fadein( i, max );
	button.fadein( i, max );
}

void Reset_button::fadeout( int i, int min )
{
	button.fadeout( i, min );
}



bool Reset_button::doReset()
{
	
	if( reset )
	{
		reset = false;
		state = 0;
		button.setOffset( 0 );
		// printf( "happened\n" );
		
		fstream file;
		string path;
		vector <string> lines;
		
		path = "data/txt/skill/level_reset.txt";
		file.open( path );
		if( file.bad() )
		{
			printf( "Cannot open file %s\n", path.c_str() );
		}
		else
		{
			string line;
			while( file >> line )
			{
				lines.push_back( line );
			}
		}
		file.close();
		
		// reset
		path = "data/txt/skill/level_current.txt";
		file.open( path, std::ios::out );
		if( file.bad() )
		{
			printf( "Cannot open file %s\n", path.c_str() );
		}
		else
		{
			for( auto &it :lines )
			{
				file << it << '\n';
			}
		}
		file.close();
		lines.clear();
		
		
		path = "data/txt/money/bank.txt";
		file.open( path, std::ios::out );
		if( file.bad() )
		{
			printf( "Cannot open file %s\n", path.c_str() );
		}
		else
		{
			file << "0\n";
		}
		file.close();
		
		return true;
	}
	
	return false;
}

const sf::Uint8& Reset_button::getState() const
{
	// printf( "%d\n", state );
	return state;
}