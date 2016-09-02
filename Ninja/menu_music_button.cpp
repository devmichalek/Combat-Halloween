#include "menu_music_button.h"
#include <stdlib.h>

Menu_music_button::Menu_music_button( int scratch_state )
{
    this->scratch_state = scratch_state;
	focus = false;
}

Menu_music_button::~Menu_music_button()
{
    music_button.free();
	scratch.free();
	
	focus = false;
	scratch_state = 0;
}

bool Menu_music_button::load( string path, int bot )
{
    if( !music_button.load( path, 4 ) )
    {
        return false;
    }
    else
    {
        music_button.setPosition( 10, bot );
    }
	
	if( !scratch.load( "menu/scratch.png" ) )
	{
		return false;
	}
	else
	{
		scratch.setPosition( 10, bot );
	}
	

    return true;
}

void Menu_music_button::draw( RenderWindow* &window )
{
    window->draw( music_button.get() );
	
	if( scratch_state == 1 )
		window->draw( scratch.get() );
}

void Menu_music_button::handle( Event &event )
{
	int x, y;
	music_button.setOffset( 0 );
	
	if( event.type == Event::MouseMoved )
	{
		x = event.mouseMove.x;
		y = event.mouseMove.y;
				
		if( music_button.checkCollision( x, y ) )
		{
			music_button.setOffset( 1 );
		}
		else
			focus = false;
	}
	
	
	if( event.type == Event::MouseButtonPressed )
	{
		x = event.mouseButton.x;
		y = event.mouseButton.y;
				
		if( music_button.checkCollision( x, y ) )
		{
			focus = true;
			if( scratch_state == 0 )
				scratch_state = 1;
			else scratch_state = 0;
		}
	}
	
	if( event.type == Event::MouseButtonReleased )
	{
		focus = false;
	}
	
	if( focus )
		music_button.setOffset( 2 );
}

int Menu_music_button::getBot()
{
	return music_button.getBot();
}

int Menu_music_button::getState()
{
	return scratch_state;
}



void Menu_music_button::fadein( int i, int max )
{
	music_button.fadein( i, max );
	scratch.fadein( i, max );
}

void Menu_music_button::fadeout( int i, int min )
{
	music_button.fadeout( i, min );
	scratch.fadeout( i, min );
}