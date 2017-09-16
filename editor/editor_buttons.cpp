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
	
	if( !states.empty() )
	{
		states.clear();
	}
	
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
	
	if( !buttons.empty() )
	{
		for( auto &it :buttons )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		buttons.clear();
	}
}

void Editor_buttons::reset()
{
	for( auto it :states )
	{
		it = false;
	}
	
	for( auto it :buttons )
	{
		it->setOffset( 0 );
	}
}



void Editor_buttons::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		states.push_back( false );
		
		texts.push_back( new MyText() );
		texts[ texts.size() -1 ]->setIdentity( "editor_buttons-texts" );
		texts[ texts.size() -1 ]->setFont( "fonts/Jaapokki-Regular.otf" );
		
		buttons.push_back( new MySprite() );
		buttons[ buttons.size() -1 ]->setIdentity( "editor_buttons-buttons" );
	}
	
	
	// "mode".
	texts.push_back( new MyText() );
	texts[ texts.size() -1 ]->setIdentity( "editor_buttons-texts" );
	texts[ texts.size() -1 ]->setFont( "fonts/Jaapokki-Regular.otf" );
	
	// Set.
	texts[ HOME ]->setText( "home" );
	texts[ OPTIONS ]->setText( "options" );
	texts[ NAME ]->setText( "name" );
	texts[ DELETE ]->setText( "delete" );
	texts[ LOAD ]->setText( "load" );
	texts[ SAVE ]->setText( "save" );
	texts[ PLAY ]->setText( "play" );
	texts[ UPLOAD ]->setText( "upload" );
	texts[ AMOUNT ]->setText( " mode" );
	texts[ AMOUNT ]->setSize( 17 );
	texts[ AMOUNT ]->setAlpha( 0xFF );
	
	buttons[ HOME ]->load( "images/level/home.png", 3 );
	buttons[ OPTIONS ]->load( "images/menu/settings.png", 3 );
	buttons[ NAME ]->load( "images/editor/info.png", 3 );
	buttons[ DELETE ]->load( "images/play/rubbish.png", 3 );
	buttons[ LOAD ]->load( "images/play/load.png", 3 );
	buttons[ SAVE ]->load( "images/play/save.png", 3 );
	buttons[ UPLOAD ]->load( "images/level/update.png", 3 );
	buttons[ PLAY ]->load( "images/level/play.png", 3 );
	
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		texts[ i ]->setSize( 17 );
		texts[ i ]->setAlpha( 0xFF );
		buttons[ i ]->setScale( 0.5, 0.5 );
	}
	
	float y = screen_h /144;
	buttons[ HOME ]->setPosition( screen_w /256, y );
	buttons[ OPTIONS ]->setPosition( screen_w /128 +buttons[ HOME ]->getWidth(), y );
	buttons[ NAME ]->setPosition( screen_w -(screen_w /256 +buttons[ UPLOAD ]->getWidth())*6, y );
	buttons[ DELETE ]->setPosition( screen_w -(screen_w /256 +buttons[ UPLOAD ]->getWidth())*5, y );
	buttons[ LOAD ]->setPosition( screen_w -(screen_w /256 +buttons[ UPLOAD ]->getWidth())*4, y );
	buttons[ SAVE ]->setPosition( screen_w -(screen_w /256 +buttons[ UPLOAD ]->getWidth())*3, y );
	buttons[ UPLOAD ]->setPosition( screen_w -(screen_w /256 +buttons[ UPLOAD ]->getWidth())*2, y );
	buttons[ PLAY ]->setPosition( screen_w -(screen_w /256 +buttons[ UPLOAD ]->getWidth()), y );
	
	
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		texts[ i ]->setPosition( buttons[ i ]->getX() +buttons[ i ]->getWidth()/2 -texts[ i ]->getWidth()/2, buttons[ i ]->getBot() +screen_h /360 );
	}
	texts[ AMOUNT ]->setPosition( texts[ DELETE ]->getX(), texts[ DELETE ]->getBot() );
}

void Editor_buttons::handle( sf::Event& event )
{
	// Mouse stuff.
	if( event.type == sf::Event::MouseButtonPressed )
	{
		if( event.mouseButton.button == sf::Mouse::Left )
		{
			for( unsigned i = 0; i < buttons.size(); i++ )
			{
				if( buttons[ i ]->checkCollision( event.mouseButton.x, event.mouseButton.y ) )
				{
					set( i );
					break;
				}
			}
		}
	}
}

void Editor_buttons::draw( sf::RenderWindow* &window )
{
	for( auto &it :texts )
	{
		window->draw( it->get() );
	}
	
	for( auto &it :buttons )
	{
		window->draw( it->get() );
	}
}




bool Editor_buttons::isAnything()
{
	for( auto it :states )
	{
		if( it )
		{
			return true;
		}
	}
	
	return false;
}

bool Editor_buttons::isHome()
{
	if( states[ HOME ] )
	{
		states[ HOME ] = false;
		buttons[ HOME ]->setOffset( 0 );
		return true;
	}
	
	return false;
}

bool Editor_buttons::isOptions()
{
	if( states[ OPTIONS ] )
	{
		return true;
	}
	
	return false;
}

bool Editor_buttons::isName()
{
	if( states[ NAME ] )
	{
		return true;
	}
	
	return false;
}

bool Editor_buttons::isDelete()
{
	if( states[ DELETE ] )
	{
		return true;
	}
	
	return false;
}

bool Editor_buttons::isSave()
{
	if( states[ SAVE ] )
	{
		states[ SAVE ] = false;
		buttons[ SAVE ]->setOffset( 0 );
		return true;
	}
	
	return false;
}

bool Editor_buttons::isLoad()
{
	if( states[ LOAD ] )
	{
		states[ LOAD ] = false;
		buttons[ LOAD ]->setOffset( 0 );
		return true;
	}
	
	return false;
}

bool Editor_buttons::isPlay()
{
	if( states[ PLAY ] )
	{
		return true;
	}
	
	return false;
}

bool Editor_buttons::isUpload()
{
	if( states[ UPLOAD ] )
	{
		return true;
	}
	
	return false;
}

string Editor_buttons::getInfo()
{
	if( states[ HOME ] )			return "Be sure that the world below is saved:";
	else if( states[ LOAD ] )		return "Confirm to load local world with name:";
	else if( states[ SAVE ] )		return "Save/overwrite local world with name:";
	else if( states[ UPLOAD ] )		return "Upload current local world:";
	else if( states[ PLAY ] )		return "Launch current local world:";
	
	return " ";
}

string Editor_buttons::getWorldname( string worldname )
{
	if( states[ HOME ] )			return worldname;
	else if( states[ LOAD ] )		return worldname;
	else if( states[ SAVE ] )		return worldname;
	else if( states[ UPLOAD ] )		return worldname;
	else if( states[ PLAY ] )		return worldname;
	
	return " ";
}




void Editor_buttons::set( int w )
{
	states[ w ] = !states[ w ];
	
	if( states[ w ] )
	{
		buttons[ w ]->setOffset( 1 );
	}
	else
	{
		buttons[ w ]->setOffset( 0 );
	}
}

void Editor_buttons::setHome()
{
	set( HOME );
}

void Editor_buttons::setOptions()
{
	set( OPTIONS );
}

void Editor_buttons::setName()
{
	set( NAME );
}

void Editor_buttons::setDelete()
{
	set( DELETE );
}

void Editor_buttons::setSave()
{
	set( SAVE );
}

void Editor_buttons::setLoad()
{
	set( LOAD );
}

void Editor_buttons::setPlay()
{
	set( PLAY );
}

void Editor_buttons::setUpload()
{
	set( PLAY );
}