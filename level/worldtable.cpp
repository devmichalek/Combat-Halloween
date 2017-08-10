#include "worldtable.h"

Worldtable::Worldtable()
{
	myThread = NULL;
	free();
}

Worldtable::~Worldtable()
{
	free();
}

void Worldtable::free()
{
	screen_w = 0;
	screen_h = 0;
	
	ready = false;
	chosen = -1;
	button.free();
	
	if( !locks.empty() )
	{
		locks.clear();
	}
	
	if( !xs.empty() )
	{
		xs.clear();
	}
	
	if( !ys.empty() )
	{
		ys.clear();
	}
	
	if( !texts.empty() )
	{
		for( auto &it :texts )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		texts.clear();
	}
	
	if( myThread != NULL )
	{
		delete myThread;
		myThread = NULL;
	}
	thread_ready = false;
	
	reloadButton.free();
	information.free();
	
	click.free();
}



void Worldtable::load( float screen_w, float screen_h )
{
	free();
	
	button.setIdentity( "worldtable-button" );
	button.load( "level/level.png", 3 );
	
	reloadButton.setIdentity( "worldtable-reloadButton" );
	reloadButton.load( "menu/reload.png", 3 );
	
	information.setIdentity( "worldtable-information" );
	information.setFont( "fonts/jcandlestickextracond.ttf" );
}

void Worldtable::handle( sf::Event& event )
{
	
}

void Worldtable::draw( sf::RenderWindow* &window )
{
	
}



void Worldtable::fadein( float v, int max )
{
	
}

void Worldtable::fadeout( float v, int min )
{
	
}



bool Worldtable::isChosen()
{
	
}

string Worldtable::getName()
{
	if( chosen != -1 )
	{
		
	}
}



void Worldtable::setThread()
{
	if( !ready )
	{
		if( !thread_ready )
		{
			// Setting loading text.
			information.setText( "loading..." );
			information.setSize( screen_h /20 );
			information.setPosition( screen_w/2 -information.getWidth()/2 -reloadButton.getWidth()/2 -screen_w/256, screen_h/2 -information.getHeight() );
			reloadButton.setPosition( information.getRight() +screen_w/128, information.getY() );
			
			myThread = new std::thread( Knight_specs::setValues, this );
			myThread->detach();
		}
	}
}

void Worldtable::setValues()
{
	// if exists
	if( success != 0 )
	{
		file.get() >> line;
		
		// prepare the request
		sf::Http::Request request( "/combathalloween/values.php", sf::Http::Request::Post );
		
		// send the request
		sf::Http http( "http://adrianmichalek.pl/" );
		sf::Http::Response response = http.sendRequest( request );
		
		// check the status
		if( response.getStatus() != sf::Http::Response::Ok )
		{
			success = 0;
		}
		else
		{
			string echostring = response.getBody();
			
			if( echostring == "0" )	// error
			{
				success = 0;
			}
			else
			{
				
				ready = true;
			}
		}
	}
	
	// error
	if( success != 1 )
	{
		it->setText( "error" );
		it->setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
		it->setSize( screen_h /28 );
	}
	
	
	thread_ready = true;
}

void Worldtable::reload()
{
	
}



void Worldtable::setPlayable( bool playable )
{
	
}

void Worldtable::setVolume( float volume )
{
	
}
