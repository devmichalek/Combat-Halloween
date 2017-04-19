#include "member.h"

Member::Member()
{
	free();
}

Member::~Member()
{
	free();
}

void Member::free()
{
	url_state = false;
	url = "";
	focus = false;
	offset = 0;
	
	button_x_c = x_c = 0;
	button_x = button_y = 0;
	
	text.free();
}

void Member::reset()
{
	focus = false;
	offset = 0;
	text.setPosition( x_c, text.getY() );
	button_x = button_x_c;
}



void Member::load( string text, bool s, string url )
{
	this->text.setName( "member-text" );
	this->text.setFont( "data/00_loading/Jaapokki-Regular.otf", 28, 0xFF, 0xFF, 0xFF );
	this->text.setText( text );
	
	if( s )
	{
		url_state = true;
		this->url = url;
	}
}

void Member::setPosition( float x, float y )
{
	x_c = x;
	text.setPosition( x_c, y );
	
	button_x_c = x +250;
	button_x = button_x_c;
	button_y = y -8;
}

void Member::draw( sf::RenderWindow* &window )
{
	window->draw( text.get() );
}



void Member::fadein( int i, int max )
{
	text.fadein( i, max );
}

void Member::fadeout( int i, int min )
{
	text.fadeout( i, min );
}



void Member::move( float distance )
{
	text.setPosition( x_c +distance, text.getY() );
	button_x = button_x_c +distance;
}



bool Member::isButton()
{
	return url_state;
}

float Member::getButtonX()
{
	return button_x;
}

float Member::getButtonY()
{
	return button_y;
}

string Member::getURL()
{
	return url;
}

float Member::getY()
{
	return text.getY();
}

sf::Uint8& Member::getOffset()
{
	return offset;
}

bool& Member::getFocus()
{
	return focus;
}