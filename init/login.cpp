#include "login.h"
#include "own/file.h"

Login::Login()
{
	free();
}

Login::~Login()
{
	free();
}

void Login::free()
{
	screen_w = 0;
	screen_h = 0;
	
	counter = 0;
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
	
	state = 0;
	username = "";
	password = "";
	max_length_username = 0;
	min_length_username = 0;
	max_length_password = 0;
	min_length_password = 0;
	
	thread.free();
	
	forget_counter = 0;
	forgetbutton.free();
}



void Login::load( float screen_w, float screen_h )
{
	free();
	
	// Set basics.
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	arrow_line = 0.5;	// 0.5 sec.
	
	
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
	
	string path = "fonts/Jaapokki-Regular.otf";
	loginbutton.setFont( path );
	signupbutton.setFont( path );
	gobutton.setFont( path );
	backbutton.setFont( path );
	forgetbutton.setFont( path );
	
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
	
	sf::Color color( 0x21, 0x21, 0x29 );
	signupbutton.setColorText( color );
	loginbutton.setColorText( color );
	gobutton.setColorText( color );
	backbutton.setColorText( color );
	forgetbutton.setColorText( color );
	
	// Set identity.
	title.setIdentity( "login-title" );
	arrow.setIdentity( "login-arrow" );
	username_form.setIdentity( "login-username_form" );
	password_form.setIdentity( "login-password_form" );
	username_written.setIdentity( "login-username_written" );
	password_written.setIdentity( "login-password_written" );
	info.setIdentity( "login-info" );
	
	// Set font.
	title.setFont( path );
	arrow.setFont( path );
	username_form.setFont( path );
	password_form.setFont( path );
	username_written.setFont( path );
	password_written.setFont( path );
	info.setFont( path );
	
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
	if( counter == 0 && !thread.s && state < 2 )
	{
		loginbutton.handle( event );
		signupbutton.handle( event );
		gobutton.handle( event );
		backbutton.handle( event );
		forgetbutton.handle( event );
		
		if( event.type == sf::Event::MouseButtonPressed )
		{
			if( event.mouseButton.button == sf::Mouse::Left )
			{
				float mouse_x = event.mouseButton.x;
				float mouse_y = event.mouseButton.y;
				
				if( username_form.checkCollision( mouse_x, mouse_y ) )
				{
					state = 0;
					setArrow();
				}
				else if( password_form.checkCollision( mouse_x, mouse_y ) )
				{
					state = 1;
					setArrow();
				}
			}
		}
		else
		{
			if( event.type == sf::Event::TextEntered )
			{
				if( isPossibleKey( event.text.unicode ) )
				{
					if( state == 0 && username.size() < max_length_username )
					{
						username += event.text.unicode;
						username_written.setText( username );
						organizeWritten();
					}
					else if( state == 1 && password.size() < max_length_password )
					{
						password += event.text.unicode;
						password_written.setText( getPassword() );
						organizeWritten();
					}
				}
			}
			
			if( event.type == sf::Event::KeyPressed )
			{
				if( event.key.code == sf::Keyboard::BackSpace )	// Delete last one.
				{
					if( state == 0 && username.size() >= 1 )
					{
						username.pop_back();	
						if( username.empty() )	username_written.setText( " " );
						else					username_written.setText( username );
						organizeWritten();
					}
					else if( state == 1 && password.size() >= 1 )
					{
						password.pop_back();
						if( password.empty() )	password_written.setText( " " );
						else					password_written.setText( getPassword() );
						organizeWritten();
					}
				}
				else if( event.key.code == sf::Keyboard::Return )
				{
					if( state == 0 )
					{
						state = 1;
						setArrow();
					}
					else if( state == 1 )
					{
						if( username.size() >= min_length_username && password.size() >= min_length_password )
						{
							gobutton.getFocus() = true;
							gobutton.getClicked() = true;
						}
					}
				}
			}
		}
	}
}

void Login::draw( sf::RenderWindow* &window )
{
	// First scene.
	window->draw( loginbg.get() );
	loginbutton.draw( window );
	window->draw( signupbg.get() );
	signupbutton.draw( window );
	
	
	// Second scene.
	backbutton.draw( window );
	window->draw( title.get() );
	window->draw( username_form.get() );
	window->draw( password_form.get() );
	window->draw( username_written.get() );
	window->draw( password_written.get() );
	window->draw( info.get() );
	if( forget_counter > 2 )	forgetbutton.draw( window );
	
	
	// Draw gobutton.
	if( username.size() >= min_length_username && password.size() >= min_length_password )
	{
		gobutton.draw( window );
	}
	
	
	// Draw arrow.
	if( arrow_counter < arrow_line && state < 2 )
	{
		window->draw( arrow.get() );
	}
}

void Login::mechanics( double elapsedTime )
{
	// Delete thread if is done.
	if( thread.r )
	{
		thread.reset();
	}
	
	// Arrow.
	arrow_counter += elapsedTime;
	if( arrow_counter > arrow_line *2 )
	{
		arrow_counter = 0;
	}
	
	loginbutton.mechanics( elapsedTime );
	signupbutton.mechanics( elapsedTime );
	backbutton.mechanics( elapsedTime );
	
	if( forget_counter > 2 )
	{
		forgetbutton.mechanics( elapsedTime );
	}
	
	if( username.size() >= min_length_username && password.size() >= min_length_password )
	{
		gobutton.mechanics( elapsedTime );
	}
	
	
	// Background
	float value = elapsedTime *0xFF;
	if( loginbutton.getFocus() && loginbutton.getState() == 1 && counter == 0 )
	{
		loginbg.fadein( value *3, 0xFF );
	}
	else
	{
		loginbg.fadeout( value *3, 0 );
	}
	if( signupbutton.getFocus() && signupbutton.getState() == 1 && counter == 0 )
	{
		signupbg.fadein( value *3, 0xFF );
	}
	else
	{
		signupbg.fadeout( value *3, 0 );
	}
	
	loginbutton.fadeinGlobal( value );
	signupbutton.fadeinGlobal( value );
	backbutton.fadeinGlobal( value );
	title.fadein( value );
	username_form.fadein( value );
	password_form.fadein( value );
	username_written.fadein( value );
	password_written.fadein( value );
	arrow.fadein( value );
	gobutton.fadeinGlobal( value );
	info.fadeout( value /2 );
	forgetbutton.fadeinGlobal( value );
	
	if( signupbutton.getClicked() )
	{
		string command = "start http://www.adrianmichalek.pl/combathalloween/registration_form.php";
		system( command.c_str() );
		signupbutton.getClicked() = false;
	}
	else if( forgetbutton.getClicked() )
	{
		string command = "start http://www.adrianmichalek.pl/combathalloween/registration_form.php";
		system( command.c_str() );
		forgetbutton.getClicked() = false;
	}
	else if( loginbutton.getClicked() )
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
	
	if( gobutton.getClicked() && username.size() >= min_length_username && password.size() >= min_length_password )
	{
		gobutton.getClicked() = false;
		gobutton.getFocus() = false;
		
		if( !thread.r && thread.t == NULL )
		{
			state = 2;
			
			info.setText( "Loading data..." );
			info.setColor( sf::Color( 0xF7, 0xF3, 0xE8 ) );
			info.setPosition( screen_w /2 -info.getWidth() /2, password_form.getBot() +screen_h/20 );
			info.setAlpha( 0xFF );
			
			thread.t = new std::thread( Login::setThread, this );
			thread.t->detach();
		}
	}
	
	if( counter < 0 )
	{
		float add = elapsedTime *screen_h;
		move( 0, add );
		counter -= add;
	}
	else if( counter > 0 )
	{
		float add = -elapsedTime *screen_h /2 *3;
		move( 0, add );
		counter += -add;
	}
	
	// In case...
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
	if( thread.s && info.getAlpha() == 0 )
	{
		return true;
	}
	
	return false;
}

string Login::getUsername()
{
	return username;
}






void Login::setArrow()
{
	if( state == 0 )
	{
		if( username.empty() )	arrow.setPosition( username_written.getX(), username_form.getY() );
		else					arrow.setPosition( username_written.getRight(), username_form.getY() );
	}
	else if( state == 1 )
	{
		if( password.empty() )	arrow.setPosition( password_written.getX(), password_form.getY() );
		else					arrow.setPosition( password_written.getRight(), password_form.getY() );
	}
}

void Login::setThread()
{
	MyRequest request;
	request.setMessage( "username=" +username +"&password=" +password );
	request.setHttp( "http://adrianmichalek.pl/" );
	request.setRequest( "/combathalloween/request.php", sf::Http::Request::Post );

    if( !request.sendRequest() )
    {
		info.setText( "No internet connection." );
		info.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
    }
	else if( request.getResult() == "success" )
	{
		thread.s = true;
		info.setText( "You are logged!" );
		info.setColor( sf::Color( 0x58, 0x70, 0x58 ) );
	}
	else
	{
		forget_counter ++;
		info.setText( request.getResult() );
		info.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	}
	
	
	// Set alpha and position of info.
	info.setAlpha( 0xFF );
	info.setPosition( screen_w /2 -info.getWidth() /2, password_form.getBot() +screen_h/20 );
	
	// Set Arrow - state.
	state = 1;
	
	// Thread is done.
	thread.r = true;
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

void Login::organizeWritten()
{
	username_written.setPosition( username_form.getRight() +screen_w/256, username_form.getY() );
	password_written.setPosition( password_form.getRight() +screen_w/256, password_form.getY() +screen_h/72 );
	setArrow();
}

bool Login::isPossibleKey( sf::Uint8 code )
{
	if( code >= 48 && code <= 57 )	// 0 .. 9
	{
		return true;
	}
	else if( code >= 65 && code <= 90 )	// A .. Z
	{
		return true;
	}
	else if( code >= 97 && code <= 122 ) // a .. z
	{
		return true;
	}

	return false;
}

void Login::move( float y_add, float x_add )
{
	loginbg.move( y_add, x_add );
	signupbg.move( y_add, x_add );
	loginbutton.move( y_add, x_add );
	signupbutton.move( y_add, x_add );
	
	gobutton.move( y_add, x_add );
	backbutton.move( y_add, x_add );
	title.move( y_add, x_add );
	arrow.move( y_add, x_add );
	username_form.move( y_add, x_add );
	password_form.move( y_add, x_add );
	username_written.move( y_add, x_add );
	password_written.move( y_add, x_add );
	info.move( y_add, x_add );
	forgetbutton.move( y_add, x_add );
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