#include "initialization/login.h"
#include <SFML/Network.hpp>
#include "own/file.h"

Login::Login()
{
	myThread = NULL;
	free();
}

Login::~Login()
{
	free();
}

void Login::free()
{
	ready = false;
	screen_w = 0;
	screen_h = 0;
	
	counter = 0;
	velocity = 0;
	
	arrow_counter = 0;
	arrow_line = 0;
	
	login.free();
	signup.free();
	login_bg.free();
	signup_bg.free();
	
	back.free();
	label.free();
	username_form.free();
	password_form.free();
	username_written.free();
	password_written.free();
	arrow.free();
	go.free();
	error.free();
	
	status = 0;
	username = "";
	password = "";
	max_length_username = 0;
	min_length_username = 0;
	max_length_password = 0;
	min_length_password = 0;
	error_status = false;
	
	if( myThread != NULL )
	{
		delete myThread;
		myThread = NULL;
	}
}



void Login::load( int screen_w, int screen_h )
{
	free();
	
	max_length_username = 13;
	min_length_username = 4;
	max_length_password = 20;
	min_length_password = 8;
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	velocity = screen_h /2;
	arrow_line = 0.5;
	
	
	int size = screen_h /18;
	login.setIdentity( "login-login" );
	login.create( "LOG IN", "fonts/Jaapokki-Regular.otf", size, size /30 +2 );
	login.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	login.setColorText( sf::Color( 0x21, 0x21, 0x29 ) );
	
	signup.setIdentity( "login-signup" );
	signup.create( "SIGN UP", "fonts/Jaapokki-Regular.otf", size, size /30 +2 );
	signup.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	signup.setColorText( sf::Color( 0x21, 0x21, 0x29 ) );
	
	login_bg.setIdentity( "login-login_bg" );
	login_bg.create( screen_w/2, screen_h );
	login_bg.setAlpha( 0 );
	
	signup_bg.setIdentity( "login-signup_bg" );
	signup_bg.create( screen_w/2, screen_h );
	signup_bg.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	signup_bg.move( screen_w/2, 0 );
	
	
	
	back.setIdentity( "login-back" );
	back.create( "BACK", "fonts/Jaapokki-Regular.otf", size /1.5, size /30 +2 );
	back.setColor( sf::Color( 0xD5, 0xE1, 0xDD ) );
	back.setColorText( sf::Color( 0x21, 0x21, 0x29 ) );
	
	label.setIdentity( "login-label" );
	label.setFont( "fonts/Jaapokki-Regular.otf" );
	label.setText( "LOGGING" );
	label.setSize( screen_h /12 );
	label.setColor( sf::Color( 0xF7, 0xF3, 0xE8 ) );
	
	username_form.setIdentity( "login-username_form" );
	username_form.setFont( "fonts/Jaapokki-Regular.otf" );
	username_form.setText( "Username: " );
	username_form.setSize( screen_h /20 );
	username_form.setColor( sf::Color( 0xD5, 0xE1, 0xDD ) );
	
	password_form.setIdentity( "login-password_form" );
	password_form.setFont( "fonts/Jaapokki-Regular.otf" );
	password_form.setText( "Password: " );
	password_form.setSize( screen_h /20 );
	password_form.setColor( sf::Color( 0xD5, 0xE1, 0xDD ) );
	
	arrow.setIdentity( "login-arrow" );
	arrow.setFont( "fonts/Jaapokki-Regular.otf" );
	arrow.setText( "|" );
	arrow.setSize( screen_h /20 );
	arrow.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	
	// WRITTEN
	username_written.setIdentity( "login-username_write" );
	username_written.setFont( "fonts/Jaapokki-Regular.otf" );
	username_written.setText( " " );
	username_written.setSize( screen_h /20 );
	username_written.setColor( sf::Color( 0xD5, 0xE1, 0xDD ) );
	
	password_written.setIdentity( "login-password_write" );
	password_written.setFont( "fonts/Jaapokki-Regular.otf" );
	password_written.setText( " " );
	password_written.setSize( screen_h /20 );
	password_written.setColor( sf::Color( 0xD5, 0xE1, 0xDD ) );
	
	go.setIdentity( "login-go" );
	go.create( "LOG IN", "fonts/Jaapokki-Regular.otf", size /1.5, size /30 +2 );
	go.setColor( sf::Color( 0xD5, 0xE1, 0xDD ) );
	go.setColorText( sf::Color( 0x21, 0x21, 0x29 ) );
	
	error.setIdentity( "login-password_write" );
	error.setFont( "fonts/Jaapokki-Regular.otf" );
	error.setText( " " );
	error.setSize( screen_h /20 );
	error.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	
	position();
}

void Login::handle( sf::Event& event )
{
	if( counter == 0 )
	{
		login.handle( event );
		signup.handle( event );
		back.handle( event );
		
		if( !ready )
		{
			go.handle( event );
		}
		
		if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) && status < 2 )
		{
			int x = event.mouseButton.x;
			int y = event.mouseButton.y;
			
			if( username_form.checkCollision( x, y ) )
			{
				status = 0;
				setArrow();
			}
			else if( password_form.checkCollision( x, y ) )
			{
				status = 1;
				setArrow();
			}
		}
		
		
		// keyboard stuff
		if( event.type == sf::Event::KeyPressed )
		{
			// add key
			if( isPossibleKey( event ) )
			{
				if( status == 0 )
				{
					if( username.size() < max_length_username )
					{
						username += getName( event.key.code );
						username_written.setText( username );
						username_written.setSize( username_form.getSize() );
						organizeWritten();
					}
				}
				else if( status == 1 )
				{
					if( password.size() < max_length_password )
					{
						password += getName( event.key.code );
						password_written.setText( getPassword() );
						password_written.setSize( password_form.getSize() );
						organizeWritten();
					}
				}
			}
			else if( event.key.code == 59 )	// backspace
			{
				if( status == 0 )
				{
					if( username.size() >= 1 )
					{
						string new_username = "";
						for( unsigned i = 0; i < username.size() -1; i++ )
						{
							new_username += username[ i ];
						}
						
						username = new_username;
						if( username.size() == 0 )
						{
							username_written.setText( " " );
						}
						else
						{
							username_written.setText( username );
							username_written.setSize( username_form.getSize() );
						}
						
						organizeWritten();
					}
				}
				else if( status == 1 )
				{
					if( password.size() >= 1 )
					{
						string new_password = "";
						for( unsigned i = 0; i < password.size() -1; i++ )
						{
							new_password += password[ i ];
						}
						
						password = new_password;
						if( password.size() == 0 )
						{
							password_written.setText( " " );
						}
						else
						{
							password_written.setText( getPassword() );
							password_written.setSize( password_form.getSize() );
						}
						
						organizeWritten();
					}
				}
			}
			else if( event.key.code == 58 )	// enter, return
			{
				if( status == 0 )
				{
					status = 1;
					setArrow();
				}
				else if( status == 1 && !ready )
				{
					go.getFocus() = true;
					
					error.setText( "Loading data..." );
					error.setColor( sf::Color( 0xF7, 0xF3, 0xE8 ) );
					error.setPosition( screen_w /2 -error.getWidth() /2, password_form.getBot() +screen_h/36 );
					error.setAlpha( 0xFF );
					
					myThread = new std::thread( Login::sendRequest, this );
					myThread->detach();
				}
			}
		}
	}
}

void Login::draw( sf::RenderWindow* &window, double elapsedTime )
{
	// First scene.
	window->draw( login_bg.get() );
	login.draw( window, elapsedTime );
	window->draw( signup_bg.get() );
	signup.draw( window, elapsedTime );
	
	// Second scene.
	back.draw( window, elapsedTime );
	window->draw( label.get() );
	window->draw( username_form.get() );
	window->draw( password_form.get() );
	window->draw( username_written.get() );
	window->draw( password_written.get() );
	window->draw( error.get() );
	
	// Draw button "go"
	if( username.size() >= 4 && password.size() >= 8 )
	{
		go.draw( window, elapsedTime );
	}
	
	// Draw arrow.
	if( arrow_counter < arrow_line )
	{
		window->draw( arrow.get() );
	}
	
	// Background
	if( login.getFocus() && login.getState() == 1 && counter == 0 )		login_bg.fadein( elapsedTime *0xFF *3, 0xFF );
	else																login_bg.fadeout( elapsedTime *0xFF *3, 0 );
	if( signup.getFocus() && signup.getState() == 1 && counter == 0 )	signup_bg.fadein( elapsedTime *0xFF *3, 0xFF );
	else																signup_bg.fadeout( elapsedTime *0xFF *3, 0 );
	
	login.fadeinGlobal( elapsedTime *0xFF );
	signup.fadeinGlobal( elapsedTime *0xFF );
	
	arrow_counter += elapsedTime;
	if( arrow_counter > arrow_line *2 )
	{
		arrow_counter = 0;
	}
	
	back.fadeinGlobal( elapsedTime *0xFF );
	label.fadein( elapsedTime *0xFF );
	username_form.fadein( elapsedTime *0xFF );
	password_form.fadein( elapsedTime *0xFF );
	username_written.fadein( elapsedTime *0xFF );
	password_written.fadein( elapsedTime *0xFF );
	arrow.fadein( elapsedTime *0xFF );
	go.fadeinGlobal( elapsedTime *0xFF );
	error.fadeout( elapsedTime*64 );
	
	if( login.getClicked() )
	{
		login.getClicked() = false;
		login.getFocus() = false;
		counter = -1;
	}
	else if( back.getClicked() )
	{
		back.getClicked() = false;
		back.getFocus() = false;
		counter = 1;
	}
	else if( go.getClicked() && username.size() >= 4 && password.size() >= 8 )
	{
		go.getClicked() = false;
		go.getFocus() = false;
		sendRequest();
	}
	
	if( error_status )
	{
		error_status = false;
		go.getFocus() = false;
	}
	
	if( counter != 0 )
	{
		if( counter < 0 )
		{
			float add = elapsedTime *velocity *2;
			back.move( 0, add );
			login.move( 0, add );
			signup.move( 0, add );
			login_bg.move( 0, add );
			signup_bg.move( 0, add );
			label.move( 0, add );
			username_form.move( 0, add );
			password_form.move( 0, add );
			username_written.move( 0, add );
			password_written.move( 0, add );
			arrow.move( 0, add );
			go.move( 0, add );
			error.move( 0, add );
			counter -= add;
		}
		else
		{
			float add = -elapsedTime *velocity *3;
			back.move( 0, add );
			login.move( 0, add );
			signup.move( 0, add );
			login_bg.move( 0, add );
			signup_bg.move( 0, add );
			label.move( 0, add );
			username_form.move( 0, add );
			password_form.move( 0, add );
			username_written.move( 0, add );
			password_written.move( 0, add );
			arrow.move( 0, add );
			go.move( 0, add );
			error.move( 0, add );
			counter += -add;
		}
	}
	
	
	if( counter > screen_h/4*3 )
	{
		counter = 0;
		position();
	}
	else if( counter < -screen_h/4*3 )
	{
		counter = 0;
		position( 0, screen_h/4*3 );
	}
}



bool Login::isReady()
{
	if( ready && error.getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}



bool Login::isPossibleKey( sf::Event &event )
{
	sf::Uint8 code = event.key.code;
	
	if( code > -1 && code <= 35 )
	{
		return true;
	}
	else if( code >= 75 && code <= 84 )
	{
		return true;
	}

	return false;
}

string Login::getName( int n )
{
	string name = "";
	
	if( n > -1 && n <= 25 )	// from a to z
	{
		// in ASCII 97 means letter 'a'
		name = static_cast <char> ( n + 97 );
	}
	else if( n >= 26 && n <= 35 )
	{
		// 26 + 22 = 48
		// in ASCII 48 means character 0
		name = static_cast <char> ( n + 22 );
	}
	else if( n >= 75 && n <= 84 )
	{
		// 75 - 27 = 48
		// in ASCII 48 means character 0
		name = static_cast <char> ( n - 27 );
	}
	
	return name;
}

void Login::organizeWritten()
{
	username_written.setPosition( username_form.getRight() +screen_w/256, username_form.getY() );
	password_written.setPosition( password_form.getRight() +screen_w/256, password_form.getY() +screen_h/72 );
	setArrow();
}

string Login::getPassword()
{
	string new_password = "";
	for( unsigned i = 0; i < password.size(); i++ )
	{
		new_password += '*';
	}
	
	return new_password;
}

void Login::setArrow()
{
	if( status == 0 )
	{
		if( username.size() == 0 )
		{
			arrow.setPosition( username_written.getX(), username_form.getY() );
		}
		else
		{
			arrow.setPosition( username_written.getRight(), username_form.getY() );
		}
	}
	else if( status == 1 )
	{
		if( password.size() == 0 )
		{
			arrow.setPosition( password_written.getX(), password_form.getY() );
		}
		else
		{
			arrow.setPosition( password_written.getRight(), password_form.getY() );
		}
	}
}

void Login::position( float x_add, float y_add )
{
	login.setPosition( screen_w /4 -login.getWidth() /2 +x_add, screen_h /2 -login.getHeight() /2 +y_add );
	signup.setPosition( screen_w /4 *3 -signup.getWidth() /2 +x_add, screen_h /2 -signup.getHeight() /2 +y_add );
	back.setPosition( screen_w /128 +x_add, screen_h /72 -screen_h/4*3 +y_add );
	label.setPosition( screen_w /2 -label.getWidth() /2 +x_add, screen_h /4 -screen_h/4*3 +y_add );
	username_form.setPosition( screen_w /3 -username_form.getWidth() /2 +x_add, screen_h /2 -screen_h/4*3 +y_add );
	password_form.setPosition( screen_w /3 -password_form.getWidth() /2 +x_add, username_form.getBot() +password_form.getHeight()*2 );
	go.setPosition( password_form.getRight() +password_form.getWidth()*2.5, username_form.getBot() +screen_h/72 );
	error.setPosition( screen_w /4 -error.getWidth() /2 +x_add, password_form.getBot() +screen_h/36 );
	organizeWritten();
}

void Login::sendRequest()
{
	string message = "username=" +username +"&password=" +password +"&secret=gabrysia2017";
	
	// prepare the request
	sf::Http::Request request( "/request.php", sf::Http::Request::Post );
	
	// encode the parameters in the request body
    request.setBody( message );
	
	// send the request
    sf::Http http( "http://englishseries.netne.net/" );
    sf::Http::Response response = http.sendRequest( request );
	
	// check the status
    if( response.getStatus() != sf::Http::Response::Ok )
    {
        // printf( "request failed\n" );
		error.setText( "No internet connection." );
		error.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
		error.setPosition( screen_w /2 -error.getWidth() /2, password_form.getBot() +screen_h/36 );
		error.setAlpha( 0xFF );
    }
	else // Error
	{
		error_status = true;
		int error_code = con::stoi( response.getBody() );
		
		if( error_code == 0 )
		{
			ready = true;
			error.setText( "You are logged!" );
			error.setColor( sf::Color( 0x58, 0x70, 0x58 ) );
		}
		else
		{
			if( error_code == 1 || error_code == 2 )
			{
				error.setText( "Username or password seems to be wrong." );
			}
			else if( error_code == 3 )
			{
				error.setText( "Cannot find connection." );
			}
			else
			{
				error.setText( "Different unexpected error." );
			}
			error.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
		}
		
		error.setPosition( screen_w /2 -error.getWidth() /2, password_form.getBot() +screen_h/36 );
		error.setAlpha( 0xFF );
	}
}