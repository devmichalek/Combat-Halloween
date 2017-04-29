/**
    initialazation.h
    Purpose: class Initialization - contains nick stuff.

    @author Adrian Michalek
    @version 2017.04.22
	@email adrmic98@gmail.com
*/

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
	
	nick_setter.free();
	nick_info.free();
}



void Initialization::load( unsigned screen_w, unsigned screen_h )
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
		
		nick_setter.fadein( value );
		nick_info.fadein( value );
	}
	else
	{
		int value = 4;
		
		nick_setter.fadeout( value );
		nick_info.fadeout( value );
	}
	
	// Draw.
	nick_setter.draw( window );
	nick_info.draw( window );
}



bool Initialization::nextState()
{
	if( next && nick_info.getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}