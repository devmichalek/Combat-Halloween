#include "editor_buttons.h"

Editor_buttons::Editor_buttons()
{
	free();
}

Editor_buttons::~Editor_buttons()
{
	free();
}

void Editor_buttons::free()
{
	screen_w = 0;
	screen_h = 0;
	
	saveState = false;
	loadState = false;
	focus = false;
	released = true;
	path = "world_";
	
	savebutton.free();
	loadbutton.free();
	saveText.free();
	loadText.free();
	
	form.free();
	info.free();
}

void Editor_buttons::reset()
{
	saveState = false;
	loadState = false;
	focus = false;
	released = true;
	path = "world_";
	organizeWritten();
	setColorWritten();
}



void Editor_buttons::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	float scale_x = screen_w /2560;
	float scale_y = screen_h /1440;
	
	savebutton.setIdentity( "editor_buttons-savebutton" );
	savebutton.load( "images/play/save.png", 3 );
	savebutton.setScale( scale_x, scale_y );
	savebutton.setPosition( screen_w -savebutton.getWidth() -screen_w /256, screen_h /144 );
	
	loadbutton.setIdentity( "editor_buttons-loadbutton" );
	loadbutton.load( "images/play/load.png", 3 );
	loadbutton.setScale( scale_x, scale_y );
	loadbutton.setPosition( screen_w -(loadbutton.getWidth() +screen_w /256) *2, screen_h /144 );
	
	saveText.setIdentity( "editor_buttons-saveText" );
	saveText.setFont( "fonts/Jaapokki-Regular.otf" );
	saveText.setText( "save" );
	saveText.setSize( screen_h /48 );
	saveText.setAlpha( 0xFF );
	saveText.setPosition( savebutton.getX() +savebutton.getWidth()/2 -saveText.getWidth()/2, savebutton.getBot() );
	
	loadText.setIdentity( "editor_buttons-loadText" );
	loadText.setFont( "fonts/Jaapokki-Regular.otf" );
	loadText.setText( "load" );
	loadText.setSize( screen_h /48 );
	loadText.setAlpha( 0xFF );
	loadText.setPosition( loadbutton.getX() +loadbutton.getWidth()/2 -loadText.getWidth()/2, loadbutton.getBot() );
	
	rubbishTextdelete.setIdentity( "editor-rubbishTextdelete" );
	rubbishTextdelete.setFont( "fonts/Jaapokki-Regular.otf" );
	rubbishTextdelete.setText( "delete" );
	rubbishTextdelete.setSize( screen_h /48 );
	rubbishTextdelete.setAlpha( 0xFF );
	rubbishTextdelete.setPosition( loadbutton.getLeft() -loadbutton.getWidth()/2 -rubbishTextdelete.getWidth()/2 -screen_w /256, loadbutton.getBot() );
	
	rubbishTextmode.setIdentity( "editor-rubbishTextmode" );
	rubbishTextmode.setFont( "fonts/Jaapokki-Regular.otf" );
	rubbishTextmode.setText( "mode" );
	rubbishTextmode.setSize( screen_h /48 );
	rubbishTextmode.setAlpha( 0xFF );
	rubbishTextmode.setPosition( loadbutton.getLeft() -loadbutton.getWidth()/2 -rubbishTextmode.getWidth()/2 -screen_w /256, rubbishTextdelete.getBot() );
	
	form.setIdentity( "editor_buttons-form" );
	form.setFont( "fonts/Jaapokki-Regular.otf" );
	form.setText( "Click 'Tab' to turn focus | File name: " );
	form.setSize( screen_h /32 );
	form.setAlpha( 0xFF );
	
	info.setIdentity( "editor_buttons-info" );
	info.setFont( "fonts/Jaapokki-Regular.otf" );
	info.setText( path );
	info.setSize( screen_h /32 );
	info.setAlpha( 0xFF );
	
	organizeWritten();
}

void Editor_buttons::handle( sf::Event& event )
{
	// Mouse stuff.
	if( event.type == sf::Event::MouseButtonPressed )
	{
		if( event.mouseButton.button == sf::Mouse::Left )
		{
			if( savebutton.checkCollision( event.mouseButton.x, event.mouseButton.y ) )
			{
				saveState = true;
				savebutton.setOffset( 1 );
			}
			else if( loadbutton.checkCollision( event.mouseButton.x, event.mouseButton.y ) )
			{
				loadState = true;
				loadbutton.setOffset( 1 );
			}
		}
	}
	
	// Keyboard stuff.
	if( event.type == sf::Event::KeyPressed && released )
	{
		if( focus )
		{
			// add key
			if( isPossibleKey( event ) )
			{
				if( path.size() < 20 )	// max
				{
					path += getName( event.key.code );
					organizeWritten();
				}
			}
			
			else if( event.key.code == sf::Keyboard::BackSpace )
			{
				// world_ = 6 chars
				if( path.size() > 6 )	// min
				{
					path.pop_back();
					organizeWritten();
				}
			}
		}
		
		if( event.key.code == sf::Keyboard::Tab )
		{
			released = false;
			focus = !focus;
			setColorWritten();
		}
	}
	
	else if( event.type == sf::Event::KeyReleased )
	{
		if( event.key.code == sf::Keyboard::Tab )
		{
			released = true;
		}
	}
}

void Editor_buttons::draw( sf::RenderWindow* &window )
{
	window->draw( savebutton.get() );
	window->draw( loadbutton.get() );
	window->draw( saveText.get() );
	window->draw( loadText.get() );
	window->draw( rubbishTextdelete.get() );
	window->draw( rubbishTextmode.get() );
	window->draw( form.get() );
	window->draw( info.get() );
}

bool Editor_buttons::isSave()
{
	if( saveState )
	{
		saveState = false;
		savebutton.setOffset( 0 );
		return true;
	}
	
	return false;
}

bool Editor_buttons::isLoad()
{
	if( loadState )
	{
		loadState = false;
		loadbutton.setOffset( 0 );
		return true;
	}
	
	return false;
}

bool Editor_buttons::isFocus()
{
	return focus;
}

string Editor_buttons::getPath()
{
	return path;
}



void Editor_buttons::setSave()
{
	saveState = true;
	savebutton.setOffset( 1 );
}

void Editor_buttons::setLoad()
{
	loadState = true;
	loadbutton.setOffset( 1 );
}

void Editor_buttons::setFocus( bool f )
{
	focus = f;
	setColorWritten();
}



bool Editor_buttons::isPossibleKey( sf::Event &event )
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

string Editor_buttons::getName( int n )
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

void Editor_buttons::organizeWritten()
{
	info.setText( path );
	form.setPosition( screen_w /2 -(form.getWidth()/2 +info.getWidth()/2), screen_h /144 );
	info.setPosition( form.getRight() +screen_w /256, form.getY() );
}

void Editor_buttons::setColorWritten()
{
	if( focus )
	{
		form.setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	}
	else
	{
		form.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
	}
}