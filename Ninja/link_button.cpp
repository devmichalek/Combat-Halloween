#include "link_button.h"
#include <stdlib.h>

Link_button::Link_button( string url, bool locked )
{
    this->locked = locked;
    this->url = url;
}

Link_button::~Link_button()
{
    mySprite.free();
}

bool Link_button::load( string path, int screen_w, int bot )
{
    if( !mySprite.load( path, 4 ) )
    {
        return false;
    }
    else
    {
		if( locked )
			mySprite.setOffset( 3 );    // locked offset = 3
		
        int border = 10;
        mySprite.setPosition( screen_w - mySprite.getWidth() - border, bot );
    }

    return true;
}

void Link_button::draw( RenderWindow &window )
{
    window.draw( mySprite.get() );
}

void Link_button::handle( Event &event )
{
    int x, y;

    if( !locked )
    {
        mySprite.setOffset( 0 );

        if( event.type == Event::MouseMoved )
        {
            x = event.mouseMove.x;
            y = event.mouseMove.y;
			
			if( mySprite.checkCollision( x, y ) )
				mySprite.setOffset( 1 );
        }

        if( event.type == Event::MouseButtonPressed )
        {
            x = event.mouseButton.x;
            y = event.mouseButton.y;
			
			if( mySprite.checkCollision( x, y ) )
			{
				mySprite.setOffset( 2 );

				string command = "xdg-open ";
				command += url.c_str();
				system( command.c_str() );
			}
        }
    }
}

int Link_button::getBot()
{
	return mySprite.getBot();
}
