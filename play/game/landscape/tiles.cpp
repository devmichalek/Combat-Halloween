#include "tiles.h"
#include "own/file.h"

Tiles::Tiles()
{
	free();
}

Tiles::~Tiles()
{
	free();
}

void Tiles::free()
{
	screen_w = 0;
	screen_h = 0;
	
	width = 32;
	
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

void Tiles::reset()
{
	collision = false;
	
	border_x = 0;
	border_y = 0;
	
	if( !tiles.empty() )
	{
		for( auto &it :tiles )
		{
			it.clear();
		}
		
		tiles.clear();
	}
	
	if( !alpha.empty() )
	{
		for( auto &it :alpha )
		{
			it.clear();
		}
		
		alpha.clear();
	}
	
	error = "";
	thread.free();
}

void Tiles::load( float screen_w, float screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	// Load sprites.
	for( unsigned i = 0; i < 17; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ sprites.size() -1 ]->setIdentity( "tiles-sprites" );
		sprites[ sprites.size() -1 ]->load( "images/play/tiles/" +con::itos(i) +".png" );
		sprites[ sprites.size() -1 ]->setScale( 0.51, 0.51 );
	}
	
	// Collision.
	rect.setSize( sf::Vector2f( sprites[ 0 ]->getWidth(), sprites[ 0 ]->getHeight() /4 ) );
	rect.setFillColor( sf::Color( 0x99, 0x99, 0x00, 0x99 ) );
}

void Tiles::draw( sf::RenderWindow* &window, sf::Shader &shader )
{
	int l = static_cast <int> (border_x) /width /2;
	int r = static_cast <int> (border_x +screen_w) /width +1;
	int b = static_cast <int> (-border_y) /width;
	int t = static_cast <int> (-border_y +screen_h) /width +1;
	
	for( int i = l; i < r; i++ )
	{
		for( int j = b; j < t; j++ )
		{
			if( tiles[ i ][ j ] != -1 )
			{
				sprites[ tiles[ i ][ j ] ]->setPosition( i *width, -((j +1) *width) +screen_h );
				shader.setUniform( "addAlpha", alpha[ i ][ j ] /0xFF );
				window->draw( sprites[ tiles[ i ][ j ] ]->get(), &shader );
			}
		}
	}
	
	shader.setUniform( "addAlpha", 1 );
	
	// Test.
	if( collision )
	{
		window->draw( rect, &shader );
		rect.setPosition( -rect.getSize().x, -rect.getSize().y );
	}
}

void Tiles::turnCollision( bool collision )
{
	this->collision = collision;
}




bool Tiles::isNull()
{
	// Delete thread.
	if( thread.t != NULL && thread.r )
	{
		thread.reset();
	}
	
	if( thread.t == NULL )
	{
		return true;
	}
	
	return false;
}

bool Tiles::isReady()
{
	return thread.s;
}

void Tiles::setThread( string message )
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

void Tiles::prepare( string message )
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
		vector <sf::Int8> new_tiles;
		vector <float> new_alpha;
		for( unsigned j = 0; j < 300; j++ )
		{
			new_tiles.push_back( -1 );
			new_alpha.push_back( static_cast <float> (0xFF) );
		}
		
		tiles.push_back( new_tiles );
		alpha.push_back( new_alpha );
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
						if( con::stoi( nrstr ) != 1 && con::stoi( nrstr ) != 2 )
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
				
				if( w == 1 || w == 2 )
				{
					// printf( "%f %f\n", x /width, -(y -screen_h) /width );
					tiles[ x /width ][ -(y -screen_h) /width ] = static_cast <sf::Int8> (t);
					if( w == 2 )	alpha[ x /width ][ -(y -screen_h) /width ] = 0;
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

string Tiles::getError()
{
	return error;
}



bool Tiles::checkCollisionRect( sf::Rect <float> rect )
{
	// The rest.
	float x;
	float y;
	
	int l = static_cast <int> (border_x) /width /2;
	int r = static_cast <int> (border_x +screen_w) /width +1;
	int b = static_cast <int> (-border_y) /width;
	int t = static_cast <int> (-border_y +screen_h) /width +1;
	
	for( int i = l; i < r; i++ )
	{
		for( int j = b; j < t; j++ )
		{
			if( tiles[ i ][ j ] != -1 )
			{
				x = i *width;
				y = -((j +1) *width) +screen_h;
				
				sprites[ tiles[ i ][ j ] ]->setPosition( x, y );
				if( sprites[ tiles[ i ][ j ] ]->checkCollisionRect( rect ) )
				{
					if( rect.top < y )	this->rect.setPosition( sf::Vector2f( x, y ) );
					else				this->rect.setPosition( sf::Vector2f( x, y +sprites[ tiles[ i ][ j ] ]->getHeight() -this->rect.getSize().y ) );
					return true;
				}
			}
		}
	}
	
	return false;
}

void Tiles::tickGravity( sf::Rect <float> rect, double elapsedTime )
{
	// The rest.
	float x;
	float y;
	
	int l = static_cast <int> (border_x) /width /2;
	int r = static_cast <int> (border_x +screen_w) /width +1;
	int b = static_cast <int> (-border_y) /width;
	int t = static_cast <int> (-border_y +screen_h) /width +1;
	
	for( int i = l; i < r; i++ )
	{
		for( int j = b; j < t; j++ )
		{
			if( tiles[ i ][ j ] != -1 && alpha[ i ][ j ] < 0xFF )
			{
				x = i *width;
				y = -((j +1) *width) +screen_h;
				
				if( alpha[ i ][ j ] > 0 ) 	alpha[ i ][ j ] -= elapsedTime *0xFF /2;
				else 						alpha[ i ][ j ] = 0;
				
				sprites[ tiles[ i ][ j ] ]->setPosition( x, y );
				if( sprites[ tiles[ i ][ j ] ]->checkCollisionRect( rect ) )
				{
					if( alpha[ i ][ j ] < 0xFF /2 )
					{
						alpha[ i ][ j ] += elapsedTime *0xFF;
					}
				}
			}
		}
	}
}

void Tiles::setBorderX( float x )
{
	border_x = x;
}

void Tiles::setBorderY( float y )
{
	border_y = y;
}

float Tiles::getBorderX()
{
	return border_x;
}

float Tiles::getBorderY()
{
	return border_y;
}

float Tiles::getScreenWidth()
{
	return screen_w;
}

float Tiles::getScreenHeight()
{
	return screen_h;
}