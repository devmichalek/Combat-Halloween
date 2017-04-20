#include "author_info.h"

Author_info::Author_info()
{
	free();
}

Author_info::~Author_info()
{
	free();
}

void Author_info::free()
{
	text.free();
	email.free();
	
	text_x = 0;
	email_x = 0;
}

void Author_info::reset()
{
	text.setPosition( text_x, text.getY() );
	email.setPosition( email_x, email.getY() );
}



void Author_info::Author_info::load( int screen_w, int screen_h )
{
	free();
	
	int start_x = 50 +screen_w;
	
	text.setName( "author_info-text" );
	text.setFont( "data/initialization/Jaapokki-Regular.otf", 20, 255, 255, 255 );
	text.setText( "Any bugs, suggestions? Contact me:" );
	text.setPosition( start_x, screen_h /4 *3 +60 );
	
	email.setName( "author_info-email" );
	email.setFont( "data/initialization/Jaapokki-Regular.otf", 20, 0xFF, 0xFF, 0xFF );
	email.setText( "adrmic98@gmail.com" );
	email.setPosition( start_x, text.getBot() +5 );
	
	text_x = text.getX();
	email_x = email.getX();
}

void Author_info::draw( sf::RenderWindow* &window )
{
	window->draw( text.get() );
	window->draw( email.get() );
}



void Author_info::fadein( int i, int max )
{
	text.fadein( i, max );
	email.fadein( i, max );
}

void Author_info::fadeout( int i, int min )
{
	text.fadeout( i, min );
	email.fadeout( i, min );
}

void Author_info::move( float distance )
{
	text.setPosition( text_x +distance, text.getY() );
	email.setPosition( email_x +distance, email.getY() );
}