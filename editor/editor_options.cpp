#include "editor_options.h"

Editor_options::Editor_options()
{
	free();
}

Editor_options::~Editor_options()
{
	free();
}

void Editor_options::free()
{
	screen_w = 0;
	screen_h = 0;
	status = 0;
	
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
	
	table.free();
	closebutton.free();
}



void Editor_options::load( float screen_w, float screen_h )
{
	free();
	
	// Load table.
	table.setIdentity( "editor_options-table" );
	table.load( "images/menu/table_second.png" );
	table.setScale( 0.75, 1 );
	table.setPosition( screen_w /2 -table.getWidth()/2, screen_h/2 -table.getHeight()/2 );
	
	// Load "close" button.
	closebutton.setIdentity( "editor_options-closebutton" );
	closebutton.load( "images/editor/disagree.png", 3 );
	closebutton.setScale( 0.3, 0.3 );
	closebutton.setPosition( table.getRight() -closebutton.getWidth()*1.1, table.getY() +closebutton.getHeight()*0.1 );
	
	// Push back, set identity, set font.
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		texts.push_back( new MyText );
		texts[ i ]->setIdentity( "editor_options-texts" );
		texts[ i ]->setFont( "fonts/jcandlestickextracond.ttf" );
	}
	
	// Set text.
	texts[ KEYBOARD ]->setText( "KEYBOARD:" );
	texts[ KEY_A ]->setText( "A - PREVIOUS CATEGORY" );
	texts[ KEY_S ]->setText( "S - RESET CATEGORY" );
	texts[ KEY_D ]->setText( "D - NEXT CATEGORY" );
	
	texts[ KEY_Z ]->setText( "Z - PREVIOUS CHOSEN" );
	texts[ KEY_X ]->setText( "X - CHOSEN /2" );
	texts[ KEY_C ]->setText( "C - NEXT CHOSEN" );
	
	texts[ KEY_LEFT ]->setText( " LEFT - MOVE LEFT" );
	texts[ KEY_RIGHT ]->setText( "RIGHT - MOVE RIGHT" );
	texts[ KEY_TOP ]->setText( "UP - MOVE UP" );
	texts[ KEY_BOT ]->setText( "DOWN - MOVE DOWN" );
	texts[ KEY_CTRL ]->setText( "LEFT CTRL - DELETE MODE" );
	texts[ KEY_SPACE ]->setText( "SPACE - PUT CHOSEN" );
	
	texts[ MOUSE ]->setText( "MOUSE:" );
	texts[ MOUSE_LEFT ]->setText( "LEFT BUTTON - PUT CHOSEN" );
	texts[ MOUSE_RIGHT ]->setText( "RIGHT BUTTON - SET SPECS" );
	
	int size = 28;
	texts[ KEYBOARD ]->setSize( size );
	for( unsigned i = 1; i < MOUSE; i++ )
	{
		texts[ i ]->setSize( size -4 );
	}
	
	texts[ MOUSE ]->setSize( size );
	for( unsigned i = MOUSE; i < texts.size(); i++ )
	{
		texts[ i ]->setSize( size -4 );
	}
	
	for( auto &it :texts )
	{
		it->setAlpha( 0xFF );
	}
	
	// Set position.
	texts[ KEYBOARD ]->setPosition( table.getX() +table.getWidth()/2 -texts[ KEYBOARD ]->getWidth()/2, table.getY() +closebutton.getHeight()*0.1 );
	float y = texts[ KEYBOARD ]->getBot() +closebutton.getHeight()*0.2;
	for( unsigned i = 1; i < KEY_LEFT; i++ )
	{
		texts[ i ]->setPosition( table.getX() +closebutton.getWidth(), y +texts[ KEYBOARD ]->getHeight()*(i -1) );
	}
	for( unsigned i = KEY_LEFT; i < MOUSE; i++ )
	{
		texts[ i ]->setPosition( texts[ KEYBOARD ]->getX() +closebutton.getHeight()*2, y +texts[ KEYBOARD ]->getHeight()*(i -KEY_LEFT) );
	}
	
	texts[ MOUSE ]->setPosition( table.getX() +table.getWidth()/2 -texts[ MOUSE ]->getWidth()/2, texts[ MOUSE -1 ]->getBot() +closebutton.getHeight()*0.2 );
	y = texts[ MOUSE ]->getBot() +closebutton.getHeight()*0.2;
	texts[ MOUSE_LEFT ]->setPosition( table.getX() +closebutton.getWidth(), y );
	texts[ MOUSE_RIGHT ]->setPosition( texts[ KEYBOARD ]->getX() +closebutton.getHeight()*2, y );
	
	line.setFillColor( sf::Color( 0xFF, 0xFF, 0xFF, 0xFF /3 ) );
	line.setSize( sf::Vector2f( table.getWidth() *0.8, 3 ) );
}

void Editor_options::handle( sf::Event& event )
{
	if( status > 0 )
	{
		if( event.type == sf::Event::MouseButtonPressed )
		{
			if( event.mouseButton.button == sf::Mouse::Left )
			{
				float mouseX = event.mouseButton.x;
				float mouseY = event.mouseButton.y;
				
				if( closebutton.checkCollision( mouseX, mouseY ) )
				{
					status = 2;
				}
			}
		}
	}
}

void Editor_options::draw( sf::RenderWindow* &window )
{
	if( status > 0 )
	{
		window->draw( table.get() );
		window->draw( closebutton.get() );
		
		// Keyboard lines.
		line.setPosition( sf::Vector2f( table.getX() +table.getWidth()*0.1, texts[ KEYBOARD ]->getY() +texts[ KEYBOARD ]->getHeight()/1.5 ) );
		window->draw( line );
		// Mouse lines.
		line.setPosition( sf::Vector2f( table.getX() +table.getWidth()*0.1, texts[ MOUSE ]->getY() +texts[ MOUSE ]->getHeight()/1.5 ) );
		window->draw( line );
		
		for( auto &it :texts )
		{
			window->draw( it->get() );
		}
	}
}



void Editor_options::setStatus( int status )
{
	this->status = status;
}

int Editor_options::getStatus()
{
	return status;
}