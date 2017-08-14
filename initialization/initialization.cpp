#include "initialization.h"

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
	
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		texts.push_back( new MyText );
	}
	
	// Set identity.
	texts[ AUTHOR ]->setIdentity( "initialization-adrmic" );
	texts[ PRESENTS ]->setIdentity( "initialization-pres" );
	texts[ HALLOWEEN ]->setIdentity( "initialization-part" );
	texts[ COMBAT ]->setIdentity( "initialization-title" );
	
	// Set font.
	texts[ AUTHOR ]->setFont( "fonts/Jaapokki-Regular.otf" );
	texts[ PRESENTS ]->setFont( "fonts/Jaapokki-Regular.otf" );
	texts[ HALLOWEEN ]->setFont( "fonts/Jaapokki-Regular.otf" );
	texts[ COMBAT ]->setFont( "fonts/Jaapokki-Regular.otf" );
	
	// Set text.
	texts[ AUTHOR ]->setTextW( L"Adrian Michałek" );
	texts[ PRESENTS ]->setText( "presents" );
	texts[ HALLOWEEN ]->setText( "Halloween" );
	texts[ COMBAT ]->setText( "Combat" );
	
	// Set size.
	int size = screen_height /24;
	texts[ AUTHOR ]->setSize( size );
	texts[ PRESENTS ]->setSize( size );
	texts[ HALLOWEEN ]->setSize( size );
	texts[ COMBAT ]->setSize( size );
	
	// Set color.
	texts[ AUTHOR ]->setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	texts[ PRESENTS ]->setColor( sf::Color( 0xB0, 0xC4, 0xDE ) );
	texts[ HALLOWEEN ]->setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	texts[ COMBAT ]->setColor( sf::Color( 0xD5, 0xE1, 0xDD ) );
	
	// Set position.
	texts[ AUTHOR ]->center( 0, 0, screen_width, screen_height -screen_height /10 );
	texts[ PRESENTS ]->setPosition( screen_width /2 -texts[ PRESENTS ]->getWidth() /2, texts[ AUTHOR ]->getBot() );
	texts[ COMBAT ]->center( 0, 0, screen_width -texts[ HALLOWEEN ]->getWidth() -screen_height /72, screen_height  -screen_height /10 );
	texts[ HALLOWEEN ]->setPosition( texts[ COMBAT ]->getRight() +screen_height /72, texts[ COMBAT ]->getBot() -texts[ HALLOWEEN ]->getHeight() );
}

void Initialization::draw( sf::RenderWindow* &window, double elapsedTime )
{
	if( !ready )
	{
		float velocity = elapsedTime *0xFF;
		if( state == 0 )
		{
			texts[ AUTHOR ]->fadein( velocity );
		}
		else if( state == 1 )
		{
			texts[ PRESENTS ]->fadein( velocity *1.5 );
		}
		else if( state == 2 )
		{
			texts[ AUTHOR ]->fadeout( velocity );
			texts[ PRESENTS ]->fadeout( velocity );
		}
		else if( state == 3 )
		{
			texts[ COMBAT ]->fadein( velocity );
		}
		else if( state == 4 )
		{
			texts[ HALLOWEEN ]->fadein( velocity );
		}
		else if( state == 5 )
		{
			texts[ COMBAT ]->fadeout( velocity *1.5 );
			texts[ HALLOWEEN ]->fadeout( velocity *1.5 );
		}
		
		window->draw( texts[ AUTHOR ]->get() );
		window->draw( texts[ PRESENTS ]->get() );
		window->draw( texts[ COMBAT ]->get() );
		window->draw( texts[ HALLOWEEN ]->get() );
		
		// 1
		if( texts[ AUTHOR ]->getAlpha() == 0xFF && state == 0 )
		{
			state = 1;
		}
		else if( texts[ PRESENTS ]->getAlpha() == 0xFF && state == 1 )
		{
			state = 2;
		}
		else if( texts[ PRESENTS ]->getAlpha() == 0 && state == 2 )
		{
			state = 3;
		}
		
		// 2
		else if( texts[ COMBAT ]->getAlpha() == 0xFF && state == 3 )
		{
			state = 4;
		}
		else if( texts[ HALLOWEEN ]->getAlpha() == 0xFF && state == 4 )
		{
			state = 5;
		}
		else if( texts[ HALLOWEEN ]->getAlpha() == 0 && state == 5 )
		{
			ready = true;
		}
	}
}



bool Initialization::isReady()
{
	return ready;
}
