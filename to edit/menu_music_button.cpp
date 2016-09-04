#include "menu_music_button.h"
#include <stdlib.h>

Menu_music_button::Menu_music_button( bool play )
{
    state = 0;
	focus = false;
	this->play = play;
}

Menu_music_button::~Menu_music_button()
{
    button.free();
	scratch.free();
	click.free();
	
	focus = false;
	state = 0;
	play = true;
}

bool Menu_music_button::load( string path, int bot )
{
    if( !button.load( path, 4 ) )
    {
        return false;
    }
    else
    {
        button.setPosition( 10, bot );
    }
	
	if( !scratch.load( "menu/scratch.png" ) )
	{
		return false;
	}
	else
	{
		scratch.setPosition( 10, bot );
	}
	
	if( !click.load( "menu/click.wav", 50 ) )
	{
		return false;
	}
	

    return true;
}

void Menu_music_button::draw( sf::RenderWindow* &window )
{
    window->draw( button.get() );
	
	if( state == 2 )
		window->draw( scratch.get() );
}

void Menu_music_button::handle( sf::Event &event )
{
	if( button.getAlpha() == 255 )
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
				focus = false;
		}
		
		
		if( event.type == sf::Event::MouseButtonPressed && !focus )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
					
			if( button.checkCollision( x, y ) )
			{
				focus = true;
				
				if( play )
					click.play();
					
				if( state == 0 )
					state = 1;
				if( state == 2 )
					state = 3;
			}
		}
		
		if( event.type == sf::Event::MouseButtonReleased )
		{
			focus = false;
		}
		
		if( focus )
			button.setOffset( 2 );
	}
}

int Menu_music_button::getBot()
{
	return button.getBot();
}

bool Menu_music_button::change()
{
	// printf("%d\n", state );
	if( state == 1 )
	{
		state = 2;
		return true;
	}
	
	if( state == 3 )
	{
		state = 0;
		return true;
	}
		
	return false;
}

void Menu_music_button::turn()
{
	play = !play;
}



void Menu_music_button::fadein( int i, int max )
{
	button.fadein( i, max );
	scratch.fadein( i, max );
}

void Menu_music_button::fadeout( int i, int min )
{
	button.fadeout( i, min );
	scratch.fadeout( i, min );
}