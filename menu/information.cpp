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
	earned_form.free();
	earned.free();
	logout.free();
	
	if( myThread != NULL )
	{
		delete myThread;
		myThread = NULL;
	}
	thread_ready = false;
	ready = false;
	open = true;
	
	click.free();
}



void Information::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	float main_x = screen_w /1.22;
	
	click.setIdentity( "information-chunk" );
	click.load( "sounds/click.wav" );
	
	// load username
	MyFile file;
	file.load( "txt/player.txt" );
	if( file.is_good() )
	{
		string line;
		file.get() >> line;
		file.get() >> line;
		
		username.setIdentity( "information-username" );
		username.setFont( "fonts/jcandlestickextracond.ttf" );
		username.setText( "Logged as  " +line );
		username.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
		username.setSize( screen_h /32 );
		username.setPosition( main_x, screen_h /144 );
	}
	file.free();
	
	// Money form.
	money_form.setIdentity( "information-money_form" );
	money_form.setFont( "fonts/jcandlestickextracond.ttf" );
	money_form.setText( "Money: " );
	money_form.setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
	money_form.setSize( screen_h /32 );
	money_form.setPosition( main_x, username.getBot() +screen_h /144 );
	
	// Earned form.
	earned_form.setIdentity( "information-earned_form" );
	earned_form.setFont( "fonts/jcandlestickextracond.ttf" );
	earned_form.setText( "Earned: " );
	earned_form.setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
	earned_form.setSize( screen_h /32 );
	earned_form.setPosition( main_x, money_form.getBot() +screen_h /144 );
	
	// Logout button.
	logout.setIdentity( "information-logout" );
	logout.setFont( "fonts/jcandlestickextracond.ttf" );
	logout.setText( "logout" );
	logout.setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
	logout.setSize( screen_h /32 );
	logout.setPosition( screen_w /1.13, screen_h /4 );
	
	
	
	
	// Earned money.
	earned.setIdentity( "information-earned" );
	earned.setFont( "fonts/jcandlestickextracond.ttf" );
	
	// current date/time based on current system
	time_t now = time( 0 );
	tm* ltm = localtime( &now );
	
	string date = con::itos( ltm->tm_mday );
	date += '.';
	date += con::itos( ltm->tm_mon +1 );
	date += '.';
	date += con::itos( 1900 + ltm->tm_year );
	// printf( "%s\n", date.c_str() );
	// check if date is different
	bool diffrent = false;
	file.load( "txt/earned.txt" );
	if( file.is_good() )
	{
		string line = "";
		file.get() >> line;
		if( line != date )
		{
			earned.setText( "0" );
			diffrent = true;
		}
		else
		{
			file.get() >> line;
			earned.setText( line );
		}
	}
	file.free();
	
	if( diffrent )
	{
		file.load( "txt/earned.txt" );
		if( file.is_good() )
		{
			file.get() << date;
			date = "0";
			file.get() << date;
		}
		file.free();
	}
	
	earned.setColor( sf::Color( 0xFF, 0xDE, 0x00 ) );
	earned.setSize( screen_h /32 );
	earned.setPosition( earned_form.getRight() +screen_w /128, earned_form.getY() );
	
	
	// Money.
	money.setIdentity( "information-money" );
	money.setFont( "fonts/jcandlestickextracond.ttf" );
}

void Information::handle( sf::Event& event )
{
	if( open )
	{
		if( event.type == sf::Event::MouseButtonPressed )
		{
			if( event.mouseButton.button == sf::Mouse::Left )
			{
				if( logout.checkCollision( event.mouseButton.x, event.mouseButton.y ) )
				{
					click.play();
					saveUsername();
					open = false;
				}
			}
		}
	}
}

void Information::draw( sf::RenderWindow* &window )
{
	window->draw( username.get() );
	window->draw( money_form.get() );
	window->draw( money.get() );
	window->draw( earned_form.get() );
	window->draw( earned.get() );
	window->draw( logout.get() );
	
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
	earned_form.fadein( v, max );
	earned.fadein( v, max );
	logout.fadein( v, max );
}

void Information::fadeout( float v, int min )
{
	username.fadeout( v, min );
	money_form.fadeout( v, min );
	money.fadeout( v, min );
	earned_form.fadeout( v, min );
	earned.fadeout( v, min );
	logout.fadeout( v, min );
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
			money.setSize( screen_h /32 );
			money.setPosition( earned.getX(), money_form.getY() );
			
			
			myThread = new std::thread( Information::setMoney, this );
			myThread->detach();
		}
	}
}

void Information::saveUsername()
{
	MyFile file;
	file.load( "txt/player.txt" );
	if( file.is_good() )
	{
		file.get() << 0;
	}
	file.free();
}

bool Information::close()
{
	return !open;
}

void Information::setMoney()
{
	// We need to know the username if it exists.
	MyFile file;
	file.load( "txt/player.txt" );
	string line;
	file.get() >> line;
	int success = con::stoi( line );
	
	// if exists
	if( success != 0 )
	{
		file.get() >> line;
		
		// prepare message
		string message = "username=" +line;
		
		// prepare the request
		sf::Http::Request request( "/combathalloween/money.php", sf::Http::Request::Post );
		
		// encode the parameters in the request body
		request.setBody( message );
		
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
				money.setText( echostring );
				money.setColor( sf::Color( 0xFF, 0xDE, 0x00 ) );
				ready = true;
			}
		}
	}
	
	// error
	if( success != 1 )
	{
		money.setText( "error" );
		money.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	}
	
	money.setSize( screen_h /32 );
	money.setPosition( earned.getX(), money_form.getY() );
	
	thread_ready = true;
}

bool Information::isReady()
{
	return ready;
}



void Information::setPlayable( bool playable )
{
	click.setPlayable( playable );
}

void Information::setVolume( float volume )
{
	click.setVolume( volume );
}
