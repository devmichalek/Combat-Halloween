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
	
	if( !texts2.empty() )
	{
		for( auto &it :texts2 )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		texts2.clear();
	}
	
	table.free();
	closebutton.free();
}



void Editor_options::load( float screen_w, float screen_h )
{
	free();
	
	// Load table.
	table.setIdentity( "editor_options-table" );
	table.load( "images/menu/table.png" );
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
		texts2.push_back( new MyText );
		texts2[ i ]->setIdentity( "editor_options-texts2" );
		texts2[ i ]->setFont( "fonts/jcandlestickextracond.ttf" );
	}
	
	// Set text.
	texts[ KEYBOARD ]->setText( "KEYBOARD" );
	texts[ KEY_A ]->setText( "A: " );
	texts[ KEY_S ]->setText( "S: " );
	texts[ KEY_D ]->setText( "D: " );
	
	texts[ KEY_Z ]->setText( "Z: " );
	texts[ KEY_X ]->setText( "X: " );
	texts[ KEY_C ]->setText( "C: " );
	
	texts[ KEY_LEFT ]->setText( "LEFT: " );
	texts[ KEY_RIGHT ]->setText( "RIGHT: " );
	texts[ KEY_TOP ]->setText( "UP: " );
	texts[ KEY_BOT ]->setText( "DOWN: " );
	texts[ KEY_ENTER ]->setText( "ENTER: " );
	texts[ KEY_ESC ]->setText( "ESC: " );
	texts[ KEY_CTRL ]->setText( "LEFT CTRL: " );
	texts[ KEY_SPACE ]->setText( "SPACE: " );
	
	texts[ MOUSE ]->setText( "MOUSE" );
	texts[ MOUSE_LEFT ]->setText( "LEFT BUTTON: " );
	texts[ MOUSE_RIGHT ]->setText( "RIGHT BUTTON: " );
	texts[ MOUSE_SCROLL ]->setText( "SCROLL: " );
	
	texts2[ KEYBOARD ]->setText( " " );
	texts2[ KEY_A ]->setText( "BACK CATEGORY" );
	texts2[ KEY_S ]->setText( "NONE CATEGORY / RESET" );
	texts2[ KEY_D ]->setText( "NEXT CATEGORY" );
	
	texts2[ KEY_Z ]->setText( "BACK CHOSEN" );
	texts2[ KEY_X ]->setText( "SET MIDDLE CHOSEN" );
	texts2[ KEY_C ]->setText( "NEXT CHOSEN" );
	
	texts2[ KEY_LEFT ]->setText( "MOVE LEFT MAP" );
	texts2[ KEY_RIGHT ]->setText( "MOVE RIGHT MAP" );
	texts2[ KEY_TOP ]->setText( "MOVE UP MAP" );
	texts2[ KEY_BOT ]->setText( "MOVE DOWN MAP" );
	texts2[ KEY_ENTER ]->setText( "THE BEGINNING OF THE MAP / AGREE" );
	texts2[ KEY_ESC ]->setText( "CLOSE WINDOW / RESET / DISAGREE" );
	texts2[ KEY_CTRL ]->setText( "DELETE MODE" );
	texts2[ KEY_SPACE ]->setText( "PUT CHOSEN" );
	
	texts2[ MOUSE ]->setText( " " );
	texts2[ MOUSE_LEFT ]->setText( "PUT CHOSEN" );
	texts2[ MOUSE_RIGHT ]->setText( "SET OBJECT SETTINGS (CLICK ON THE OBJECT)" );
	texts2[ MOUSE_SCROLL ]->setText( "BACK / NEXT CATEGORY" );
	
	
	
	int size = 28;
	for( unsigned i = 0; i < texts.size(); i++ )
	{
		if( i == KEYBOARD || i == MOUSE )	texts[ i ]->setSize( size );
		else
		{
			texts[ i ]->setSize( size -4 );
			texts2[ i ]->setSize( size -4 );
		}
			
		texts[ i ]->setAlpha( 0xFF );
		texts2[ i ]->setAlpha( 0xFF );
	}

	
	// Set position.
	texts[ KEYBOARD ]->setPosition( table.getX() +table.getWidth()/2 -texts[ KEYBOARD ]->getWidth()/2, table.getY() +closebutton.getHeight()*0.1 );
	float y = texts[ KEYBOARD ]->getBot() +closebutton.getHeight()*0.2;
	float add = 0;
	for( unsigned i = 1; i < MOUSE; i++ )
	{
		if( i == KEY_Z || i == KEY_LEFT || i == KEY_CTRL )
		{
			add += 7;
		}
		texts[ i ]->setPosition( table.getX() +closebutton.getWidth(), y +add +texts[ KEYBOARD ]->getHeight()*(i -1) );
	}
	
	texts[ MOUSE ]->setPosition( table.getX() +table.getWidth()/2 -texts[ MOUSE ]->getWidth()/2, texts[ MOUSE -1 ]->getBot() +closebutton.getHeight()*0.2 );
	y = texts[ MOUSE ]->getBot() +closebutton.getHeight()*0.2;
	texts[ MOUSE_LEFT ]->setPosition( table.getX() +closebutton.getWidth(), y );
	texts[ MOUSE_RIGHT ]->setPosition( table.getX() +closebutton.getWidth(), y +texts[ KEYBOARD ]->getHeight() );
	texts[ MOUSE_SCROLL ]->setPosition( table.getX() +closebutton.getWidth(), y +texts[ KEYBOARD ]->getHeight()*2 );
	
	for( unsigned i = 0; i < MOUSE; i++ )
	{
		texts2[ i ]->setPosition( texts[ KEY_CTRL ]->getRight() + 10, texts[ i ]->getY() );
	}
	
	for( unsigned i = MOUSE; i < texts2.size(); i++ )
	{
		texts2[ i ]->setPosition( texts[ MOUSE_RIGHT ]->getRight() + 10, texts[ i ]->getY() );
	}
	
	texts2[ KEY_A ]->setColor( sf::Color( 0x96, 0xFF, 0x96 ) );
	texts2[ KEY_S ]->setColor( sf::Color( 0x96, 0xFF, 0x96 ) );
	texts2[ KEY_D ]->setColor( sf::Color( 0x96, 0xFF, 0x96 ) );
	texts2[ MOUSE_SCROLL ]->setColor( sf::Color( 0x96, 0xFF, 0x96 ) );
	
	texts2[ KEY_LEFT ]->setColor( sf::Color( 0xEC, 0xFF, 0x72 ) );
	texts2[ KEY_RIGHT ]->setColor( sf::Color( 0xEC, 0xFF, 0x72 ) );
	texts2[ KEY_TOP ]->setColor( sf::Color( 0xEC, 0xFF, 0x72 ) );
	texts2[ KEY_BOT ]->setColor( sf::Color( 0xEC, 0xFF, 0x72 ) );
	texts2[ KEY_ENTER ]->setColor( sf::Color( 0xEC, 0xFF, 0x72 ) );
	texts2[ KEY_ESC ]->setColor( sf::Color( 0xEC, 0xFF, 0x72 ) );
	
	texts2[ KEY_CTRL ]->setColor( sf::Color( 0xF2, 0x58, 0x3E ) );
	texts2[ KEY_SPACE ]->setColor( sf::Color( 0x2F, 0x9E, 0x75 ) );
	texts2[ MOUSE_LEFT ]->setColor( sf::Color( 0x2F, 0x9E, 0x75 ) );
	texts2[ MOUSE_RIGHT ]->setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
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
		else if( event.type == sf::Event::KeyPressed )
		{
			if( event.key.code == sf::Keyboard::Escape )
			{
				status = 2;
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
		line.setSize( sf::Vector2f( table.getWidth() *0.35, 3 ) );
		line.setPosition( sf::Vector2f( table.getX() +table.getWidth()*0.03, texts[ KEYBOARD ]->getY() +texts[ KEYBOARD ]->getHeight()/1.5 ) );
		window->draw( line );
		line.setSize( sf::Vector2f( -table.getWidth() *0.28, 3 ) );
		line.setPosition( sf::Vector2f( table.getRight() -table.getWidth()*0.10, texts[ KEYBOARD ]->getY() +texts[ KEYBOARD ]->getHeight()/1.5 ) );
		window->draw( line );
		
		// Mouse lines.
		line.setSize( sf::Vector2f( table.getWidth() *0.4, 3 ) );
		line.setPosition( sf::Vector2f( table.getX() +table.getWidth()*0.03, texts[ MOUSE ]->getY() +texts[ MOUSE ]->getHeight()/1.5 ) );
		window->draw( line );
		line.setSize( sf::Vector2f( -table.getWidth() *0.4, 3 ) );
		line.setPosition( sf::Vector2f( table.getRight() -table.getWidth()*0.03, texts[ MOUSE ]->getY() +texts[ MOUSE ]->getHeight()/1.5 ) );
		window->draw( line );
		
		for( auto &it :texts )
		{
			window->draw( it->get() );
		}
		
		for( auto &it :texts2 )
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