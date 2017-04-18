#include "initialization.h"
#include "file/file.h"

Initialization::Initialization()
{
	free();
}

Initialization::~Initialization()
{
	free();
}

void Initialization::free()
{
	next = false;
	bg.free();
	nick_setter.free();
	nick_info.free();
}



void Initialization::load( int screen_w, int screen_h )
{
	free();
	
	// Set "next".
	MyFile file;
	file.load( "data/txt/nick/nick_status.txt" );
	if( file.is_good() )
	{
		string line;
		file.get() >> line;
		next = con::stoi( line );
	}
	file.free();
	
	bg.setName( "initialization-bg" );
	bg.create( screen_w, screen_h );
	bg.setColor( sf::Color( 21, 21, 29 ) );
	
	nick_setter.load( screen_w, screen_h );
	nick_info.load( screen_w, screen_h );
}

void Initialization::handle( sf::Event &event )
{
	if( !next )
	{
		nick_setter.handle( event );
		if( nick_setter.nextState() )
		{
			next = true;
		}
	}
}

void Initialization::draw( sf::RenderWindow* &window )
{
	if( !next )
	{
		int value = 3;
		bg.fadein( value );
		nick_setter.fadein( value );
		nick_info.fadein( value );
	}
	else
	{
		int value = 4;
		bg.fadeout( value );
		nick_setter.fadeout( value );
		nick_info.fadeout( value );
	}
	
	// Draw.
	window->draw( bg.get() );
	nick_setter.draw( window );
	nick_info.draw( window );
}


bool Initialization::nextState()
{
	if( next && bg.getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}
