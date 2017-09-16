#include "editor/editor_details.h"

Editor_details::Editor_details()
{
	free();
}

Editor_details::~Editor_details()
{
	free();
}

void Editor_details::free()
{
	screen_w = 0;
	screen_h = 0;
	
	if( !arrows.empty() )
	{
		for( auto &it :arrows )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		arrows.clear();
	}
	
	additional_x = 0;
	additional_y = 0;
	
	grid = true;
	gridText.free();
	gridStatusText.free();
	
	typeText.free();
	chosenText.free();
	
	nameStatus = 0;
	nameStr = "world";
	nameForm.free();
	name.free();
	line = 1;
	counter = 0;
	arrow.free();
	table.free();
	agreebutton.free();
}



void Editor_details::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		arrows.push_back( new MySprite() );
		arrows[ arrows.size() -1 ]->setIdentity( "editor_details-arrows" );
	}
	
	arrows[ LEFT ]->load( "images/level/left.png", 3 );
	arrows[ RIGHT ]->load( "images/level/right.png", 3 );
	arrows[ TOP ]->load( "images/editor/top.png", 3 );
	arrows[ BOT ]->load( "images/editor/bot.png", 3 );
	arrows[ MIDDLE ]->load( "images/editor/disagree.png", 3 );
	
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		arrows[ i ]->setScale( 0.25, 0.25 );
	}
	
	float width = arrows[ LEFT ]->getWidth();
	float border = screen_w /256;
	
	arrows[ LEFT ]->setPosition( screen_w -border*3 -width*3, screen_h -border*2 -width*2 );
	arrows[ RIGHT ]->setPosition( screen_w -border -width, screen_h -border*2 -width*2 );
	arrows[ TOP ]->setPosition( screen_w -border*2 -width*2, screen_h -border*3 -width*3 );
	arrows[ BOT ]->setPosition( screen_w -border*2 -width*2, screen_h -border -width );
	arrows[ MIDDLE ]->setPosition( arrows[ TOP ]->getX(), arrows[ TOP ]->getY() +width +border );
	
	// Text.
	gridText.setIdentity( "editor_details-gridText" );
	gridStatusText.setIdentity( "editor_details-gridStatusText" );
	typeText.setIdentity( "editor_details-typeText" );
	chosenText.setIdentity( "editor_details-chosenText" );
	
	gridText.setFont( "fonts/Jaapokki-Regular.otf" );
	gridStatusText.setFont( "fonts/Jaapokki-Regular.otf" );
	typeText.setFont( "fonts/Jaapokki-Regular.otf" );
	chosenText.setFont( "fonts/Jaapokki-Regular.otf" );
	
	gridText.setText( "Grid: " );
	gridText.setPosition( 160, 10 );
	gridStatusText.setText( "Off" );
	typeText.setText( "Type: None" );
	chosenText.setText( "Chosen: 0" );
	
	gridText.setSize( 22 );
	gridStatusText.setSize( 22 );
	typeText.setSize( 22 );
	chosenText.setSize( 22 );
	
	gridText.setAlpha( 0xFF );
	gridStatusText.setAlpha( 0xFF );
	typeText.setAlpha( 0xFF );
	chosenText.setAlpha( 0xFF );
	
	// Set stuff for name.
	nameForm.setIdentity( "editor_details-chosenText" );
	name.setIdentity( "editor_details-chosenText" );
	arrow.setIdentity( "editor_details-chosenText" );
	table.setIdentity( "editor_details-chosenText" );
	agreebutton.setIdentity( "editor_details-chosenText" );
	nameForm.setFont( "fonts/Jaapokki-Regular.otf" );
	name.setFont( "fonts/Jaapokki-Regular.otf" );
	arrow.setFont( "fonts/Jaapokki-Regular.otf" );
	table.load( "images/menu/table_second.png" );
	agreebutton.load( "images/editor/agree.png", 3 );
	
	agreebutton.setScale( 0.4, 0.4 );
	table.setScale( 0.6, 0.6 );
	table.setPosition( screen_w/2 -table.getWidth()/2, screen_h /2 -table.getHeight()/2 );
	agreebutton.setPosition( screen_w/2 -agreebutton.getWidth()/2, table.getBot() -agreebutton.getHeight() *1.1 );
	
	nameForm.setText( "Current world name: " );
	nameForm.setSize( 22 );
	nameForm.setAlpha( 0xFF );
	
	name.setText( nameStr );
	name.setSize( 22 );
	name.setAlpha( 0xFF );
	
	arrow.setText( "|" );
	arrow.setSize( 22 );
	arrow.setAlpha( 0xFF );
	
	nameForm.setPosition( screen_w /2 -nameForm.getWidth() /2, table.getY() +screen_h /54 );
	setWritten();
}

void Editor_details::handle( sf::Event& event )
{
	if( event.type == sf::Event::MouseButtonPressed )
	{
		float mouse_x = event.mouseButton.x;
		float mouse_y = event.mouseButton.y;
		
		if( event.mouseButton.button == sf::Mouse::Left )
		{
			if( nameStatus > 0 )
			{
				if( agreebutton.checkCollision( mouse_x, mouse_y ) )
				{
					nameStatus = 2;
					agreebutton.setOffset( 1 );
				}
			}
			else
			{
				for( auto &it :arrows )
				{
					it->setOffset( 0 );
				}
				
				if( arrows[ LEFT ]->checkCollision( mouse_x, mouse_y ) && additional_x < 0 )
				{
					additional_x += 320;
					arrows[ LEFT ]->setOffset( 1 );
				}
				else if( arrows[ RIGHT ]->checkCollision( mouse_x, mouse_y ) )
				{
					additional_x -= 320;
					arrows[ RIGHT ]->setOffset( 1 );
				}
				else if( arrows[ TOP ]->checkCollision( mouse_x, mouse_y ) )
				{
					additional_y += 180;
					arrows[ TOP ]->setOffset( 1 );
				}
				else if( arrows[ BOT ]->checkCollision( mouse_x, mouse_y ) && additional_y > 0 )
				{
					additional_y -= 180;
					arrows[ BOT ]->setOffset( 1 );
				}
				else if( arrows[ MIDDLE ]->checkCollision( mouse_x, mouse_y ) )
				{
					additional_x = 0;
					additional_y = 0;
				}
			}
		}
	}
	
	if( event.type == sf::Event::MouseButtonReleased )
	{
		for( auto &it :arrows )
		{
			it->setOffset( 0 );
		}
	}
	
	if( nameStatus > 0 )
	{
		if( event.type == sf::Event::TextEntered )
		{
			int c = event.text.unicode;
			if( (c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122) || c == 32 )
			{
				if( nameStr.size() < 16 )
				{
					nameStr += event.text.unicode;
					setWritten();
				}
			}
		}
		
		if( event.type == sf::Event::KeyPressed )
		{
			// BackSpace
			if( event.key.code == sf::Keyboard::BackSpace )
			{
				if( nameStr.size() > 0 )
				{
					nameStr.pop_back();
					setWritten();
				}
			}
			
			// Enter, return.
			else if( event.key.code == sf::Keyboard::Return )
			{
				nameStatus = 2;
			}
		}
	}
}

void Editor_details::draw( sf::RenderWindow* &window )
{
	// Draw direction buttons.
	if( additional_x >= 0 )
	{
		arrows[ LEFT ]->setOffset( 2 );
	}
	
	if( additional_y <= 0 )
	{
		arrows[ BOT ]->setOffset( 2 );
	}
	
	for( auto &it :arrows )
	{
		window->draw( it->get() );
	}
	
	window->draw( gridText.get() );
	window->draw( gridStatusText.get() );
	window->draw( typeText.get() );
	window->draw( chosenText.get() );
}

void Editor_details::drawName( sf::RenderWindow* &window )
{
	if( nameStatus > 0 )
	{
		window->draw( table.get() );
		window->draw( nameForm.get() );
		window->draw( name.get() );
		
		// draw arrow.
		if( counter < line /2 )
		{
			window->draw( arrow.get() );
		}
	
		window->draw( agreebutton.get() );
	}
}

void Editor_details::mechanics( double elapsedTime )
{
	counter += elapsedTime;
	if( counter > line )
	{
		counter = 0;
	}
}




float Editor_details::getAdditionalX()
{
	return additional_x;
}

float Editor_details::getAdditionalY()
{
	return additional_y;
}



void Editor_details::setGrid( bool grid )
{
	if( this->grid != grid )
	{
		this->grid = grid;
		
		if( grid )
		{
			gridStatusText.setText( "On" );
			gridStatusText.setColor( sf::Color::Green );
		}
		else
		{
			gridStatusText.setText( "Off" );
			gridStatusText.setColor( sf::Color::Red );
		}
		
		gridStatusText.setPosition( gridText.getRight() +4, gridText.getY() );
	}
}

void Editor_details::setType( string type )
{
	typeText.setText( "Type: " +type );
	typeText.setPosition( gridText.getX(), 32 );
}

void Editor_details::setChosen( string chosen )
{
	chosenText.setText( "Chosen: " +chosen );
	chosenText.setPosition( gridText.getX(), 64 );
}




void Editor_details::setWritten()
{
	name.setText( nameStr );
	name.setPosition( screen_w /2 -name.getWidth()/2, nameForm.getBot() +nameForm.getHeight() );
	arrow.setPosition( name.getRight(), name.getY() );
}

string Editor_details::getName()
{
	return nameStr;
}

void Editor_details::setNameStatus( int nameStatus )
{
	this->nameStatus = nameStatus;
	agreebutton.setOffset( 0 );
}

int Editor_details::getNameStatus()
{
	return nameStatus;
}