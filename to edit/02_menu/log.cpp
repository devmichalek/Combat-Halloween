#include "log.h"
#include <stdlib.h>
#include <fstream>
#include <stdio.h>

Log::Log( bool locked, bool win )
{
    state = 0;
	nr = 0;
	myText = NULL;
	play = true;
	
	this->locked = locked;
	this->win = win;
}

Log::~Log()
{
	button.free();

	log.free();
	
	if( myText != NULL )
	{
		for( int i = 0; i < nr; i++ )
		{
			myText[ i ].free();
		}
		
		delete [] myText;
	}
	
	state = 0;
	play = true;
	click.free();
	
	locked = false;
}

void Log::load( string path, int left, int y, int screen_w )
{
	button.setName( "log-button" );
    button.load( "data/sprites/menu/" + path + ".png", 4 );
	button.setPosition( left, y );
	
	// if is locked we don't have reason to load futher
	if( locked )
	{
		button.setOffset( 3 );
	}
	else if( !win )
	{
		click.setID( "log-click" );
		click.load( "data/sounds/click.wav", 50 );
	}
	else
	{
		log.setName( "log-log" );
		log.load( "data/sprites/menu/window.png" );
		log.setPosition( screen_w/2 - log.getWidth()/2, y-300 );
			
		click.setID( "log-click" );
		click.load( "data/sounds/click.wav", 50 );
		
		// file
		fstream file;
		
		file.open( "data/txt/menu/" + path + ".txt", ios::in );
		if( !file.good() )
		{
			printf( "Can not load %s.txt\n", path.c_str() );
		}
		else
		{
			// line
			string line;
			
			// how many lines
			int line_counter = 0;
			
			//printf( "test1" );
			while( getline( file, line ) )
			{
				line_counter ++;
			}
			
			nr = line_counter;
			//printf( "%d\n", nr );
		}
		file.close();
		
		
		file.open( "data/txt/menu/" + path + ".txt", ios::in );
		if( file.bad() )
		{
			printf( "Can not load %s.txt\n", path.c_str() );
		}
		else
		{
			// create array
			myText = new MyText[ nr ];
			
			// line
			string line;
			
			// counter
			int c = 0;
			
			int height = log.getTop() +52;
			int border = 0;
			
			//printf( "%d\n", nr );
			
			while( getline( file, line ) )
			{
				// printf( "%d\n", line.length() );
				// printf( "%s\n", line.c_str() );
				
				if( c < 5 )
					border += 5;
				else if( c > 6 )
					border -= 5;
				
				myText[ c ].setName( "log-myText" );
				myText[ c ].setFont( "data/fonts/BADABB__.TTF", 33, 0xd5, 0xad, 0x51 );
				myText[ c ].setText( line );
				myText[ c ].setPosition( log.getX() +80 - border, height );
				
				// printf( "x:%d  y:%d\n", myText[ c ].getX(), myText[ c ].getY() );
				
				height += myText[ c ].getHeight();
				c ++;
			}
			 
			
			
		}
		
		file.close();
	}
}

void Log::draw( sf::RenderWindow* &window )
{
	if( state < 2 )
		window->draw( button.get() );
	else if( !locked && win )
	{
		window->draw( log.get() );
		for( int i = 0; i < nr; i ++ )
		{
			window->draw( myText[ i ].get() );
		}
	}
	
	// printf( "%d\n", nr );
}

void Log::handle( sf::Event &event )
{
	static bool rel = false;
	
	if( button.getAlpha() == 255 && !locked )
	{
		if( state != 2 )
		{
			int x, y;
			button.setOffset( 0 );
			
			if( event.type == sf::Event::MouseMoved )
			{
				x = event.mouseMove.x;
				y = event.mouseMove.y;
					
				if( button.checkCollision( x, y ) && state != 2 )
				{
					button.setOffset( 1 );
					state = 1;
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
					
					state = 2;
				}
			}
		}
		else
		{
			
			if( sf::Keyboard::isKeyPressed( sf::Keyboard::Escape ) && !rel )
			{
				if( play )
					click.play();
				state = 0;
				
				rel = true;
			}
		}
		
		if( event.type == sf::Event::KeyReleased )
		{
			rel = false;
		}
	}
}

int Log::getRight()
{
	return button.getRight();
}

const int& Log::getState() const
{
	return state;
}


void Log::fadein( int i, int max )
{
	button.fadein( i, max );
	
	if( !locked && win )
	{
		log.fadein( i, max );
		for( int j = 0; j < nr; j ++ )
		{
			myText[ j ].fadein( i, max );
		}
	}
}

void Log::fadeout( int i, int min )
{
	button.fadeout( i, min );
	
	if( !locked && win )
	{
		log.fadeout( i, min );
		for( int j = 0; j < nr; j ++ )
		{
			myText[ j ].fadeout( i, min );
		}
	}
}