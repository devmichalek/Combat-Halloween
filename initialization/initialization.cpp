#include "initialization.h"
#include <iostream>
#include <windows.h>
using namespace std;

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
	ready = false;
	state = 0;
	
	if( !texts.empty() )
	{
		for( auto &it :texts )
		{
			if( it != NULL )
			{
				delete it;
				it = NULL;
			}
		}
		
		texts.clear();
	}
}



void Initialization::load( int screen_width, int screen_height )
{
	free();
	
	for( unsigned i = 0; i < 4; i++ )
	{
		texts.push_back( new MyText );
	}
	
	int size = screen_height /24;

	texts[ adrmic ]->setIdentity( "initialization-adrmic" );
	texts[ adrmic ]->setFont( "fonts/Jaapokki-Regular.otf" );
	texts[ adrmic ]->setTextW( L"Adrian Michałek" );
	texts[ adrmic ]->setSize( size );
	texts[ adrmic ]->center( 0, 0, screen_width, screen_height -screen_height /10 );
	texts[ adrmic ]->setAlpha( 0 );
	
	texts[ pres ]->setIdentity( "initialization-pres" );
	texts[ pres ]->setFont( "fonts/Jaapokki-Regular.otf" );
	texts[ pres ]->setText( "presents" );
	texts[ pres ]->setSize( size );
	texts[ pres ]->setColor( sf::Color( 0xB0, 0xC4, 0xDE ) );
	texts[ pres ]->setPosition( screen_width /2 -texts[ pres ]->getWidth() /2, texts[ adrmic ]->getBot() );
	texts[ pres ]->setAlpha( 0 );
	
	texts[ part ]->setIdentity( "initialization-part" );
	texts[ part ]->setFont( "fonts/Jaapokki-Regular.otf" );
	texts[ part ]->setText( "Halloween" );
	texts[ part ]->setSize( size );
	texts[ part ]->setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	
	texts[ title ]->setIdentity( "initialization-title" );
	texts[ title ]->setFont( "fonts/Jaapokki-Regular.otf" );
	texts[ title ]->setText( "Combat" );
	texts[ title ]->setSize( size );
	texts[ title ]->setColor( sf::Color( 0xD5, 0xE1, 0xDD ) );
	texts[ title ]->center( 0, 0, screen_width -texts[ part ]->getWidth() -screen_height /72, screen_height  -screen_height /10 );
	texts[ title ]->setAlpha( 0 );
	
	texts[ part ]->setPosition( texts[ title ]->getRight() +screen_height /72, texts[ title ]->getBot() -texts[ part ]->getHeight() );
	texts[ part ]->setAlpha( 0 );
}

void Initialization::draw( sf::RenderWindow* &window, double elapsedTime )
{
	if( !ready )
	{
		if( state == 0 )
		{
			texts[ adrmic ]->fadein( elapsedTime *128 );
		}
		else if( state == 1 )
		{
			texts[ pres ]->fadein( elapsedTime *192 );
		}
		else if( state == 2 )
		{
			texts[ adrmic ]->fadeout( elapsedTime *128 );
			texts[ pres ]->fadeout( elapsedTime *128 );
		}
		else if( state == 3 )
		{
			texts[ title ]->fadein( elapsedTime *128 );
		}
		else if( state == 4 )
		{
			texts[ part ]->fadein( elapsedTime *128 );
		}
		else if( state == 5 )
		{
			texts[ title ]->fadeout( elapsedTime *128 );
			texts[ part ]->fadeout( elapsedTime *128 );
		}
		
		window->draw( texts[ adrmic ]->get() );
		window->draw( texts[ pres ]->get() );
		window->draw( texts[ title ]->get() );
		window->draw( texts[ part ]->get() );
		
		// 1
		if( texts[ adrmic ]->getAlpha() == 0xFF && state == 0 )
			state = 1;
		else if( texts[ pres ]->getAlpha() == 0xFF && state == 1 )
			state = 2;
		else if( texts[ pres ]->getAlpha() == 0 && state == 2 )
			state = 3;
		// 2
		else if( texts[ title ]->getAlpha() == 0xFF && state == 3 )
			state = 4;
		else if( texts[ part ]->getAlpha() == 0xFF && state == 4 )
			state = 5;
		else if( texts[ part ]->getAlpha() == 0 && state == 5 )
		{
			ready = true;
		}
	}
}



bool Initialization::isReady()
{
	return ready;
}
