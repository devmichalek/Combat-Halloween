#include "information.h"
#include "own/file.h"
#include <ctime>
#include <SFML/Network.hpp>

Information::Information()
{
	myThread = NULL;
	free();
}

Information::~Information()
{
	free();
}

void Information::free()
{
	screen_w = 0;
	screen_h = 0;
	
	username.free();
	money_form.free();
	money.free();
	
	if( myThread != NULL )
	{
		delete myThread;
		myThread = NULL;
	}
	thread_ready = false;
	ready = false;
}



void Information::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	// Set identity.
	username.setIdentity( "information-username" );
	money_form.setIdentity( "information-money_form" );
	money.setIdentity( "information-money" );
	
	// Set font.
	username.setFont( "fonts/jcandlestickextracond.ttf" );
	money_form.setFont( "fonts/jcandlestickextracond.ttf" );
	money.setFont( "fonts/jcandlestickextracond.ttf" );
	
	// Set text.
	username.setText( "Logged as error" );
	money_form.setText( "Money: " );
	money.setText( "error" );
	
	// Set color.
	username.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	money_form.setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
	money.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	
	// Set size.
	username.setSize( screen_h /32 );
	money_form.setSize( screen_h /32 );
	money.setSize( screen_h /32 );
	
	// Set position.
	username.setPosition( screen_w /1.22, screen_h /144 );
	money_form.setPosition( screen_w /1.22, username.getBot() +screen_h /144 );
	money.setPosition( money_form.getRight() +screen_w /128, money_form.getY() );
}

void Information::draw( sf::RenderWindow* &window )
{
	window->draw( username.get() );
	window->draw( money_form.get() );
	window->draw( money.get() );
	
	// Delete thread if is ready
	if( thread_ready )
	{
		delete myThread;
		myThread = NULL;
		thread_ready = false;
	}
}



void Information::fadein( float v, int max )
{
	username.fadein( v, max );
	money_form.fadein( v, max );
	money.fadein( v, max );
}

void Information::fadeout( float v, int min )
{
	username.fadeout( v, min );
	money_form.fadeout( v, min );
	money.fadeout( v, min );
}



void Information::setUsername( string line )
{
	username_str = line;
	
	// load username
	username.setText( "Logged as  " +username_str );
	username.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	username.setPosition( screen_w /1.22, screen_h /144 );
}

void Information::setThread()
{
	if( !ready )
	{
		if( !thread_ready )
		{
			// Money.
			money.setText( "loading..." );
			money.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
			money.setPosition( money_form.getRight() +screen_w /128, money_form.getY() );
			
			
			myThread = new std::thread( Information::setMoney, this );
			myThread->detach();
		}
	}
}

void Information::setMoney()
{
	// prepare message
	string message = "username=" +username_str;
	
	// prepare the request
	sf::Http::Request request( "/combathalloween/getmoney.php", sf::Http::Request::Post );
	
	// encode the parameters in the request body
	request.setBody( message );
	
	// send the request
	sf::Http http( "http://adrianmichalek.pl/" );
	sf::Http::Response response = http.sendRequest( request );
	
	bool success = true;
	// check the status
	if( response.getStatus() != sf::Http::Response::Ok )
	{
		success = false;
	}
	else
	{
		string echostring = response.getBody();
		
		if( echostring == "0" )	// error
		{
			success = false;
		}
		else
		{
			money.setText( echostring );
			money.setColor( sf::Color( 0xFF, 0xDE, 0x00 ) );
			ready = true;
		}
	}
	
	// error
	if( !success )
	{
		money.setText( "error" );
		money.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	}
	
	money.setPosition( money_form.getRight() +screen_w /128, money_form.getY() );
	
	thread_ready = true;
}

bool Information::isReady()
{
	return ready;
}