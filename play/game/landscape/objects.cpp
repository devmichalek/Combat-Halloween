#include "objects.h"
#include "own/file.h"

Objects::Objects()
{
	free();
}

Objects::~Objects()
{
	free();
}

void Objects::free()
{
	FPS.free();
	line = 0;
	
	screen_w = 0;
	screen_h = 0;
	
	if( !sprites.empty() )
	{
		for( auto &it :sprites )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		sprites.clear();
	}
	
	reset();
}

void Objects::reset()
{
	currentTime = 0;
	FPS_state = false;
	counter = line;
	
	border_x = 0;
	border_y = 0;
	
	if( !fs.empty() )
	{
		fs.clear();
	}
	
	if( !types.empty() )
	{
		types.clear();
	}
	
	error = "";
	thread.free();
}

void Objects::load( float screen_w, float screen_h )
{
	free();
	
	// Test.
	FPS.setIdentity( "objects-FPS" );
	FPS.setFont( "fonts/Jaapokki-Regular.otf" );
	FPS.setText( "FPS: " );
	FPS.setSize( screen_h /36 );
	FPS.setPosition( screen_w -FPS.getWidth(), screen_h -FPS.getHeight()*1.5 );
	line = 0.25;
	counter = line;
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	// Load sprites.
	for( unsigned i = 0; i < 14; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ sprites.size() -1 ]->setIdentity( "objects-sprites" );
		sprites[ sprites.size() -1 ]->load( "images/play/objects/" +con::itos(i) +".png" );
		sprites[ sprites.size() -1 ]->setScale( 0.5, 0.5 );
	}
}

void Objects::draw( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < fs.size(); i++ )
	{
		if( fs[ i ].x < border_x +screen_w && fs[ i ].y < border_y +screen_h )
		{
			if( fs[ i ].x +sprites[ types[ i ] ]->getWidth() > border_x && fs[ i ].y +sprites[ types[ i ] ]->getHeight() > border_y )
			{
				sprites[ types[ i ] ]->setPosition( fs[ i ].x, fs[ i ].y );
				window->draw( sprites[ types[ i ] ]->get() );
			}
		}
	}
}

void Objects::drawFPS( sf::RenderWindow* &window )
{
	if( FPS_state )
	{
		window->draw( FPS.get() );
	}
}

void Objects::mechanics( double elapsedTime )
{
	float fps = 1.f /currentTime;
	currentTime = clock.restart().asSeconds();
	
	if( FPS_state )
	{
		if( counter > line )
		{
			FPS.setText( "FPS: " +con::itos( static_cast <int> (fps) ) );
			FPS.setPosition( screen_w -FPS.getWidth(), screen_h -FPS.getHeight()*1.5 );
			counter = 0;
		}
		else
		{
			counter += elapsedTime;
		}
	}
}

void Objects::fadein( float v, int max )
{
	FPS.fadein( v, max );
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
}

void Objects::fadeout( float v, int min )
{
	FPS.fadeout( v, min );
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
}



void Objects::setFPS( bool state )
{
	FPS_state = state;
}

bool Objects::getFPS()
{
	return FPS_state;
}



bool Objects::isNull()
{
	// Delete thread.
	if( thread.t != NULL && thread.r )
	{
		thread.reset();
		return true;
	}
	
	if( thread.t == NULL )
	{
		return true;
	}
	
	return false;
}

bool Objects::isReady()
{
	return thread.s;
}

void Objects::setThread( string message )
{
	if( !thread.s )
	{
		if( !thread.r && thread.t == NULL )
		{
			thread.t = new std::thread( [=] { prepare( message ); } );
			thread.t->detach();
		}
	}
}

void Objects::prepare( string message )
{
	string line = message;
	
	// Bufor and start.
	string bufor = "";
	unsigned start = 0;
	
	
	// AUTHOR --------------------------------------------------------------------------
	for( unsigned i = start; i < line.size(); i++ )
	{
		if( line[ i ] == '|' )
		{
			start = i +1;
			// printf( "%s\n", bufor.c_str() );
			bufor = "";
			break;
		}
		
		bufor += line[ i ];
	}
	
	
	// NEW SIZES --------------------------------------------------------------------------
	float my_screen_w = 0;
	float my_screen_h = 0;
	
	// Set my_screen_w.
	for( unsigned i = start; i < line.size(); i++ )
	{
		if( line[ i ] == '|' )
		{
			start = i +1;
			my_screen_w = screen_w -con::stof( bufor );
			bufor = "";
			break;
		}
		
		bufor += line[ i ];
	}
	
	// Set my_screen_h.
	for( unsigned i = start; i < line.size(); i++ )
	{
		if( line[ i ] == '|' )
		{
			start = i +1;
			my_screen_h = screen_h -con::stof( bufor ) +1;
			bufor = "";
			break;
		}
		
		bufor += line[ i ];
	}
	
	// FS --------------------------------------------------------------------------
	for( unsigned i = start; i < line.size(); i++ )
	{
		if( line[ i ] == '|' )
		{
			bufor += "*";
			string nrstr = "";
			vector <string> data;
			
			bool wrong = false;
			for( unsigned j = 0; j < bufor.size(); j++ )
			{
				if( bufor[ j ] == '*' )
				{
					if( data.size() == 0 )
					{
						if( con::stoi( nrstr ) != 3 )
						{
							wrong = true;
							break;
						}
					}
					
					data.push_back( nrstr );
					nrstr = "";
				}
				else
				{
					nrstr += bufor[ j ];
				}
			}
			
			if( !wrong )
			{
				sf::Uint8 w = con::stoi( data[ 0 ] );
				sf::Uint8 t = con::stoi( data[ 1 ] );
				float x = con::stoi( data[ 2 ] ) *0.995;
				float y = con::stoi( data[ 3 ] ) +my_screen_h;
				
				if( w == 3 )
				{
					types.push_back( t );
					fs.push_back( sf::Vector2f( x, y ) );
				}
			}
			
			// Clear.
			bufor = "";
		}
		else
		{
			bufor += line[ i ];
		}
	}
	
	// Inform that everything is ok.
	thread.s = true;
	
	// Inform that thread is ready for next action.
	thread.r = true;
}

string Objects::getError()
{
	return error;
}



void Objects::setBorderX( float x )
{
	border_x = x;
}

void Objects::setBorderY( float y )
{
	border_y = y;
}