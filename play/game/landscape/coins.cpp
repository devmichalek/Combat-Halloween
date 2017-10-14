#include "coins.h"
#include "own/file.h"

Coins::Coins()
{
	free();
}

Coins::~Coins()
{
	free();
}

void Coins::free()
{
	screen_w = 0;
	screen_h = 0;
	
	line = 0;
	width = 32;
	offset = 0;
	sprite.free();
	
	reset();
}

void Coins::reset()
{
	border_x = 0;
	border_y = 0;
	offset = 0;
	
	if( !tiles.empty() )
	{
		for( auto &it :tiles )
		{
			it.clear();
		}
		
		tiles.clear();
	}
	
	error = "";
	thread.free();
}

void Coins::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	// Load sprite.
	line = 7;
	sprite.setIdentity( "coins-sprite" );
	sprite.load( "images/play/coin.png", line );
	sprite.setScale( 0.5, 0.5 );
}

void Coins::draw( sf::RenderWindow* &window, sf::Shader &shader )
{
	int l = static_cast <int> (border_x) /width /2;
	int r = static_cast <int> (border_x +screen_w) /width +1;
	int b = static_cast <int> (-border_y) /width;
	int t = static_cast <int> (-border_y +screen_h) /width +1;
	
	for( int i = l; i < r; i++ )
	{
		for( int j = b; j < t; j++ )
		{
			if( tiles[ i ][ j ] )
			{
				sprite.setOffset( static_cast <int> ( offset ) );
				sprite.setPosition( i *width, -((j +1) *width) +screen_h );
				window->draw( sprite.get(), &shader );
			}
		}
	}
}

void Coins::mechanics( double elapsedTime )
{
	offset += elapsedTime *25;
	if( offset >= line )
	{
		offset = static_cast <int> (offset) %line;
	}
}



bool Coins::isNull()
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

bool Coins::isReady()
{
	return thread.s;
}

void Coins::setThread( string message )
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

void Coins::prepare( string message )
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
	
	for( unsigned i = 0; i < 550; i++ )
	{
		vector <bool> temporary;
		for( unsigned j = 0; j < 300; j++ )
		{
			temporary.push_back( false );
		}
		
		tiles.push_back( temporary );
	}
	
	// printf( "%f %f\n", screen_w, screen_h );
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
						if( con::stoi( nrstr ) != 4 )
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
				float x = con::stoi( data[ 2 ] );
				float y = con::stoi( data[ 3 ] ) +my_screen_h;
				
				if( w == 4 )
				{
					// printf( "%f=%d  %f=%d\n", x, static_cast <int> (x /width), y, static_cast <int>(-(y -screen_h) /width) );
					// fs.push_back( sf::Vector2f( x, y ) );
					// printf( "Coin: %f %f\n", x /width, -(y -screen_h) /width );
					tiles[ x /width ][ -(y -screen_h) /width ] = true;
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

string Coins::getError()
{
	return error;
}



void Coins::setBorderX( float x )
{
	border_x = x;
}

void Coins::setBorderY( float y )
{
	border_y = y;
}