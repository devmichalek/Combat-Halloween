/**
    nick_info.h
    Purpose: class Nick_info - responsible for drawing information about nick.

    @author Adrian Michalek
    @version 2017.04.22
	@email adrmic98@gmail.com
*/


#include "nick_info.h"

Nick_info::Nick_info()
{
	free();
}

Nick_info::~Nick_info()
{
	free();
}

void Nick_info::free()
{
	if( !texts.empty() )
	{
		for( auto it: texts )
		{
			it->free();
		}
		
		texts.clear();
	}
}



void Nick_info::load( unsigned screen_w, unsigned screen_h )
{
	free();
	
	for( unsigned i = 0; i < 3; i ++ )
	{
		texts.push_back( new MyText() );
		texts[ texts.size() -1 ]->setName( "nick_info.cpp -texts" );
	}
	
	texts[ 0 ]->setFont( "data/initialization/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	texts[ 0 ]->setText( "Before we get started, set your nick"  );
	
	texts[ 1 ]->setFont( "data/initialization/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	texts[ 1 ]->setText( "then press enter to continue"  );
	
	texts[ 2 ]->setFont( "data/initialization/Jaapokki-Regular.otf", 20, 0xFF, 0xFF, 0xFF );
	texts[ 2 ]->setText( "a-z, 1-9, no space, 3-11 small characters" );
	
	texts[ 0 ]->setPosition( screen_w /2 -texts[ 0 ]->getWidth() /2, screen_h /3.5 );
	texts[ 1 ]->setPosition( screen_w /2 -texts[ 1 ]->getWidth() /2, screen_h /1.6 );
	texts[ 2 ]->setPosition( 5, screen_h -texts[ 2 ]->getHeight() -8 );
}

void Nick_info::draw( sf::RenderWindow* &window )
{
	for( auto it: texts )
	{
		window->draw( it->get() );
	}
}



void Nick_info::fadein( int i, int max )
{
	for( auto it: texts )
	{
		it->fadein( i, max );
	}
}

void Nick_info::fadeout( int i, int min )
{
	for( auto it: texts )
	{
		it->fadeout( i, min );
	}
}



sf::Uint8 Nick_info::getAlpha()
{
	if( !texts.empty() )
	{
		return texts[ 0 ]->getAlpha();
	}
	
	return 0;
}