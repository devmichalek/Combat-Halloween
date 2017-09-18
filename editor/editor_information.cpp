#include "editor_information.h"

Editor_information::Editor_information()
{
	free();
}

Editor_information::~Editor_information()
{
	free();
}

void Editor_information::free()
{
	layout.free();
	table.free();
	agreeButton.free();
	disagreeButton.free();
	info.free();
	worldname.free();
	status = 0;
}



void Editor_information::load( float screen_w, float screen_h )
{
	free();
	
	// Set identity.
	layout.setIdentity( "editor_information-layout" );
	table.setIdentity( "editor_information-layout" );
	agreeButton.setIdentity( "editor_information-agreeButton" );
	disagreeButton.setIdentity( "editor_information-disagreeButton" );
	info.setIdentity( "editor_information-info" );
	worldname.setIdentity( "editor_information-worldname" );
	
	// Sprites.
	layout.create( screen_w, screen_h );
	layout.setColor( sf::Color::Black );
	layout.setAlpha( 150 );
	table.load( "images/menu/table_second.png" );
	agreeButton.load( "images/editor/agree.png", 3 );
	disagreeButton.load( "images/editor/disagree.png", 3 );
	table.setScale( 0.6, 0.8 );
	agreeButton.setScale( 0.4, 0.4 );
	disagreeButton.setScale( 0.4, 0.4 );
	table.setPosition( screen_w/2 -table.getWidth()/2, screen_h /2 -table.getHeight()/2 );
	agreeButton.setPosition( table.getRight() -agreeButton.getWidth()*1.1, table.getBot() -agreeButton.getHeight()*1.1 );
	disagreeButton.setPosition( table.getX() +agreeButton.getWidth()*0.1, agreeButton.getY() );
	
	// Texts.
	info.setFont( "fonts/jcandlestickextracond.ttf" );
	worldname.setFont( "fonts/jcandlestickextracond.ttf" );
	info.setText( " " );
	worldname.setText( " " );
	info.setSize( 26 );
	info.setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
	worldname.setSize( 26 );
	info.setAlpha( 0xFF );
	worldname.setAlpha( 0xFF );
	setInfo( " " );
	setWorldname( " " );
}

void Editor_information::handle( sf::Event& event )
{
	// Mouse stuff.
	if( status > 0 )
	{
		if( event.type == sf::Event::MouseButtonPressed )
		{
			if( event.mouseButton.button == sf::Mouse::Left )
			{
				if( agreeButton.checkCollision( event.mouseButton.x, event.mouseButton.y ) )
				{
					agreeButton.setOffset( 1 );
					status = 2;
				}
				else if( disagreeButton.checkCollision( event.mouseButton.x, event.mouseButton.y ) )
				{
					disagreeButton.setOffset( 1 );
					status = 3;
				}
			}
		}
	}
}

void Editor_information::draw( sf::RenderWindow* &window )
{
	if( status > 0 )
	{
		window->draw( table.get() );
		window->draw( agreeButton.get() );
		window->draw( disagreeButton.get() );
		window->draw( info.get() );
		window->draw( worldname.get() );
	}
}

void Editor_information::drawLayout( sf::RenderWindow* &window, bool permit )
{
	if( status > 0 || permit )
	{
		window->draw( layout.get() );
	}
}



void Editor_information::setInfo( string line )
{
	info.setText( line );
	info.setPosition( layout.getX() +layout.getWidth()/2 -info.getWidth()/2, table.getY() +info.getHeight()*1.5 );
}

void Editor_information::setWorldname( string line )
{
	worldname.setText( line );
	worldname.setPosition( layout.getX() +layout.getWidth()/2 -worldname.getWidth()/2, info.getBot() +worldname.getHeight()*1.5 );
}

void Editor_information::setAsVisible()
{
	if( status == 0 )
	{
		status = 1;
	}
}

bool Editor_information::isActive()
{
	if( status == 1 )
	{
		return true;
	}
	
	return false;
}

bool Editor_information::answerYes()
{
	if( status == 2 )
	{
		agreeButton.setOffset( 0 );
		status = 0;
		return true;
	}
	
	return false;
}

bool Editor_information::answerNo()
{
	if( status == 3 )
	{
		disagreeButton.setOffset( 0 );
		status = 0;
		return true;
	}
	
	return false;
}

void Editor_information::setStatus( int status )
{
	this->status = status;
}