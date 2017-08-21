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
	
	loginbg.free();
	signupbg.free();
	loginbutton.free();
	signupbutton.free();
	gobutton.free();
	backbutton.free();
	
	title.free();
	arrow.free();
	username_form.free();
	password_form.free();
	username_written.free();
	password_written.free();
	
	info.free();
	info_status = false;
	
	state = 0;
	username = "";
	password = "";
	max_length_username = 0;
	min_length_username = 0;
	max_length_password = 0;
	min_length_password = 0;
	
	if( myThread != NULL )
	{
		delete myThread;
		myThread = NULL;
	}
	thread_ready = false;
	
	forget_counter = 0;
	forgetbutton.free();
}



void Login::load( int screen_w, int screen_h )
{
	free();
	
	// Set basics.
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	velocity = screen_h /2;
	arrow_line = 0.5;
	
	
	// Background.
	loginbg.setIdentity( "login-loginbg" );
	loginbg.create( screen_w/2, screen_h );
	signupbg.setIdentity( "login-signupbg" );
	signupbg.create( screen_w/2, screen_h );
	signupbg.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	signupbg.move( screen_w/2, 0 );
	
	
	// Rectbuttons.
	loginbutton.setIdentity( "login-loginbutton" );
	signupbutton.setIdentity( "login-signupbutton" );
	gobutton.setIdentity( "login-gobutton" );
	backbutton.setIdentity( "login-backbutton" );
	forgetbutton.setIdentity( "login-forgetbutton" );
	
	loginbutton.setFont( "fonts/Jaapokki-Regular.otf" );
	signupbutton.setFont( "fonts/Jaapokki-Regular.otf" );
	gobutton.setFont( "fonts/Jaapokki-Regular.otf" );
	backbutton.setFont( "fonts/Jaapokki-Regular.otf" );
	forgetbutton.setFont( "fonts/Jaapokki-Regular.otf" );
	
	int size = screen_h /18;
	loginbutton.create( "LOG IN", size, size /30 +2 );
	signupbutton.create( "SIGN UP", size, size /30 +2 );
	gobutton.create( "LOG IN", size /1.5, size /30 +2 );
	backbutton.create( "BACK", size /1.5, size /30 +2 );
	forgetbutton.create( "FORGOT PASSWORD", size /1.5, size /30 +2 );
	
	loginbutton.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	signupbutton.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	gobutton.setColor( sf::Color( 0xD5, 0xE1, 0xDD ) );
	backbutton.setColor( sf::Color( 0xD5, 0xE1, 0xDD ) );
	forgetbutton.setColor( sf::Color( 0xFF, 0xD8, 0x00 ) );
	
	signupbutton.setColorText( sf::Color( 0x21, 0x21, 0x29 ) );
	loginbutton.setColorText( sf::Color( 0x21, 0x21, 0x29 ) );
	gobutton.setColorText( sf::Color( 0x21, 0x21, 0x29 ) );
	backbutton.setColorText( sf::Color( 0x21, 0x21, 0x29 ) );
	forgetbutton.setColorText( sf::Color( 0x21, 0x21, 0x29 ) );
	
	// Set identity.
	title.setIdentity( "login-title" );
	arrow.setIdentity( "login-arrow" );
	username_form.setIdentity( "login-username_form" );
	password_form.setIdentity( "login-password_form" );
	username_written.setIdentity( "login-username_written" );
	password_written.setIdentity( "login-password_written" );
	info.setIdentity( "login-info" );
	
	// Set font.
	title.setFont( "fonts/Jaapokki-Regular.otf" );
	arrow.setFont( "fonts/Jaapokki-Regular.otf" );
	username_form.setFont( "fonts/Jaapokki-Regular.otf" );
	password_form.setFont( "fonts/Jaapokki-Regular.otf" );
	username_written.setFont( "fonts/Jaapokki-Regular.otf" );
	password_written.setFont( "fonts/Jaapokki-Regular.otf" );
	info.setFont( "fonts/Jaapokki-Regular.otf" );
	
	// Set text.
	title.setText( "LOGGING" );
	arrow.setText( "|" );
	username_form.setText( "Username: " );
	password_form.setText( "Password: " );
	username_written.setText( " " );
	password_written.setText( " " );
	info.setText( " " );
	
	// Set size.
	size = screen_h /20;
	title.setSize( screen_h /12 );
	arrow.setSize( size );
	username_form.setSize( size );
	password_form.setSize( size );
	username_written.setSize( size );
	password_written.setSize( size );
	info.setSize( screen_h /28 );
	
	// Set color.
	title.setColor( sf::Color( 0xF7, 0xF3, 0xE8 ) );
	arrow.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	username_form.setColor( sf::Color( 0xD5, 0xE1, 0xDD ) );
	password_form.setColor( sf::Color( 0xD5, 0xE1, 0xDD ) );
	info.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	
	position();
	
	max_length_username = 20;
	min_length_username = 4;
	max_length_password = 20;
	min_length_password = 8;
}

void Login::handle( sf::Event& event )
{
	// If there is no moving and next state.
	if( counter == 0 && !ready && state < 2 )
	{
		loginbutton.handle( event );
		signupbutton.handle( event );
		gobutton.handle( event );
		backbutton.handle( event );
		forgetbutton.handle( event );
		
		if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) )
		{
			int x = event.mouseButton.x;
			int y = event.mouseButton.y;
			
			if( username_form.checkCollision( x, y ) )
			{
				state = 0;
				setArrow();
			}
			else if( password_form.checkCollision( x, y ) )
			{
				state = 1;
				setArrow();
			}
		}
		
		
		// Keyboard stuff.
		if( event.type == sf::Event::KeyPressed )
		{
			// add key
			if( isPossibleKey( event ) )
			{
				if( state == 0 )
				{
					if( username.size() < max_length_username )
					{
						username += getName( event.key.code );
						username_written.setText( username );
						organizeWritten();
					}
				}
				else if( state == 1 )
				{
					if( password.size() < max_length_password )
					{
						password += getName( event.key.code );
						password_written.setText( getPassword() );
						organizeWritten();
					}
				}
			}
			
			// backspace
			else if( event.key.code == 59 )
			{
				if( state == 0 )
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
						}
						
						organizeWritten();
					}
				}
				else if( state == 1 )
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
						}
						
						organizeWritten();
					}
				}
			}
			
			// enter, return
			else if( event.key.code == 58 )
			{
				if( state == 0 )
				{
					state = 1;
					setArrow();
				}
				else if( state == 1 )
				{
					if( !thread_ready && myThread == NULL )
					{
						state = 2;
						gobutton.getFocus() = true;
					
						info.setText( "Loading data..." );
						info.setColor( sf::Color( 0xF7, 0xF3, 0xE8 ) );
						info.setPosition( screen_w /2 -info.getWidth() /2, password_form.getBot() +screen_h/20 );
						info.setAlpha( 0xFF );
						
						myThread = new std::thread( Login::sendRequest, this );
						myThread->detach();
					}
				}
			}
		}
	}
}

void Login::draw( sf::RenderWindow* &window, double elapsedTime )
{
	// Delete thread.
	if( thread_ready )
	{
		thread_ready = false;
		
		if( myThread != NULL )
		{
			delete myThread;
			myThread = NULL;
		}
	}
	
	// First scene.
	window->draw( loginbg.get() );
	loginbutton.draw( window, elapsedTime );
	window->draw( signupbg.get() );
	signupbutton.draw( window, elapsedTime );
	
	
	// Second scene.
	backbutton.draw( window, elapsedTime );
	window->draw( title.get() );
	window->draw( username_form.get() );
	window->draw( password_form.get() );
	window->draw( username_written.get() );
	window->draw( password_written.get() );
	window->draw( info.get() );
	
	if( forget_counter > 2 )
	{
		forgetbutton.draw( window, elapsedTime );
	}
	
	
	// Draw button "go".
	if( username.size() >= min_length_username && password.size() >= min_length_password )
	{
		gobutton.draw( window, elapsedTime );
	}
	
	
	// Draw arrow.
	if( arrow_counter < arrow_line && state < 2 )
	{
		window->draw( arrow.get() );
	}
	
	
	// Background
	if( loginbutton.getFocus() && loginbutton.getState() == 1 && counter == 0 )
	{
		loginbg.fadein( elapsedTime *0xFF *3, 0xFF );
	}
	else
	{
		loginbg.fadeout( elapsedTime *0xFF *3, 0 );
	}
	
	if( signupbutton.getFocus() && signupbutton.getState() == 1 && counter == 0 )
	{
		signupbg.fadein( elapsedTime *0xFF *3, 0xFF );
	}
	else
	{
		signupbg.fadeout( elapsedTime *0xFF *3, 0 );
	}
		
	
	loginbutton.fadeinGlobal( elapsedTime *0xFF );
	signupbutton.fadeinGlobal( elapsedTime *0xFF );
	
	arrow_counter += elapsedTime;
	if( arrow_counter > arrow_line *2 )
	{
		arrow_counter = 0;
	}
	
	backbutton.fadeinGlobal( elapsedTime *0xFF );
	title.fadein( elapsedTime *0xFF );
	username_form.fadein( elapsedTime *0xFF );
	password_form.fadein( elapsedTime *0xFF );
	username_written.fadein( elapsedTime *0xFF );
	password_written.fadein( elapsedTime *0xFF );
	arrow.fadein( elapsedTime *0xFF );
	gobutton.fadeinGlobal( elapsedTime *0xFF );
	info.fadeout( elapsedTime*0xFF /2 );
	forgetbutton.fadeinGlobal( elapsedTime *0xFF );
	
	if( signupbutton.getClicked() )
	{
		string command = "start http://www.adrianmichalek.pl/combathalloween/registration_form.php";
		system( command.c_str() );
		signupbutton.getClicked() = false;
	}
	
	if( forgetbutton.getClicked() )
	{
		string command = "start http://www.adrianmichalek.pl/combathalloween/registration_form.php";
		system( command.c_str() );
		forgetbutton.getClicked() = false;
	}
	
	if( loginbutton.getClicked() )
	{
		loginbutton.getClicked() = false;
		loginbutton.getFocus() = false;
		counter = -1;
	}
	else if( backbutton.getClicked() )
	{
		backbutton.getClicked() = false;
		backbutton.getFocus() = false;
		counter = 1;
	}
	else if( gobutton.getClicked() && username.size() >= min_length_username && password.size() >= min_length_password )
	{
		if( !thread_ready )
		{
			gobutton.getClicked() = false;
			gobutton.getFocus() = false;
			
			myThread = new std::thread( Login::sendRequest, this );
			myThread->detach();
		}
	}
	
	if( info_status )
	{
		info_status = false;
		gobutton.getFocus() = false;
	}
	
	if( counter != 0 )
	{
		if( counter < 0 )
		{
			float add = elapsedTime *velocity *2;
			loginbg.move( 0, add );
			signupbg.move( 0, add );
			loginbutton.move( 0, add );
			signupbutton.move( 0, add );
			
			gobutton.move( 0, add );
			backbutton.move( 0, add );
			title.move( 0, add );
			arrow.move( 0, add );
			username_form.move( 0, add );
			password_form.move( 0, add );
			username_written.move( 0, add );
			password_written.move( 0, add );
			info.move( 0, add );
			forgetbutton.move( 0, add );
			counter -= add;
		}
		else
		{
			float add = -elapsedTime *velocity *3;
			loginbg.move( 0, add );
			signupbg.move( 0, add );
			loginbutton.move( 0, add );
			signupbutton.move( 0, add );
			
			gobutton.move( 0, add );
			backbutton.move( 0, add );
			title.move( 0, add );
			arrow.move( 0, add );
			username_form.move( 0, add );
			password_form.move( 0, add );
			username_written.move( 0, add );
			password_written.move( 0, add );
			info.move( 0, add );
			forgetbutton.move( 0, add );
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
	if( ready && info.getAlpha() == 0 )
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

string Login::getUsername()
{
	return username;
}

void Login::setArrow()
{
	if( state == 0 )
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
	else if( state == 1 )
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
	loginbutton.setPosition( screen_w /4 -loginbutton.getWidth() /2 +x_add, screen_h /2 -loginbutton.getHeight() /2 +y_add );
	signupbutton.setPosition( screen_w /4 *3 -signupbutton.getWidth() /2 +x_add, screen_h /2 -signupbutton.getHeight() /2 +y_add );
	backbutton.setPosition( screen_w /128 +x_add, screen_h /72 -screen_h/4*3 +y_add );
	title.setPosition( screen_w /2 -title.getWidth() /2 +x_add, screen_h /4 -screen_h/4*3 +y_add );
	username_form.setPosition( screen_w /3 -username_form.getWidth() /2 +x_add, screen_h /2 -screen_h/4*3 +y_add );
	password_form.setPosition( screen_w /3 -password_form.getWidth() /2 +x_add, username_form.getBot() +password_form.getHeight()*2 );
	info.setPosition( screen_w /4 -info.getWidth() /2 +x_add, password_form.getBot() +screen_h/20 );
	gobutton.setPosition( screen_w/2 -gobutton.getWidth()/2, info.getBot() +screen_h /9 +y_add -screen_h/4*3 );
	forgetbutton.setPosition( screen_w -forgetbutton.getWidth() -screen_w /128 +x_add, screen_h /72 +y_add -screen_h/4*3 );
	organizeWritten();
}

void Login::sendRequest()
{
	string message = "username=" +username +"&password=" +password;
	
	// prepare the request
	sf::Http::Request request( "/combathalloween/request.php", sf::Http::Request::Post );
	
	// encode the parameters in the request body
    request.setBody( message );
	
	// send the request
    sf::Http http( "http://adrianmichalek.pl/" );
    sf::Http::Response response = http.sendRequest( request );
	
	// check the status
    if( response.getStatus() != sf::Http::Response::Ok )
    {
        // printf( "request failed \n" );
		info.setText( "No internet connection." );
		info.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
		info.setPosition( screen_w /2 -info.getWidth() /2, password_form.getBot() +screen_h/20 );
		info.setAlpha( 0xFF );
    }
	else // Error
	{
		info_status = true;
		string error_code = response.getBody();
		
		if( error_code == "success" )
		{
			ready = true;
			info.setText( "You are logged!" );
			info.setColor( sf::Color( 0x58, 0x70, 0x58 ) );
		}
		else
		{
			state = 1;
			forget_counter ++;
			info.setText( error_code );
			info.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
		}
		
		info.setPosition( screen_w /2 -info.getWidth() /2, password_form.getBot() +screen_h/20 );
		info.setAlpha( 0xFF );
	}
	
	thread_ready = true;
}