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
	fadingout = false;
	
	if( !fs.empty() )
	{
		fs.clear();
	}
	
	if( !types.empty() )
	{
		types.clear();
	}
	
	if( !ufs.empty() )
	{
		ufs.clear();
	}
	
	if( !utypes.empty() )
	{
		utypes.clear();
	}
	
	if( !ualpha.empty() )
	{
		ualpha.clear();
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
		sprites[ sprites.size() -1 ]->setScale( 0.5, 0.5 );
	}
	
	// Collision.
	rect.setSize( sf::Vector2f( sprites[ 0 ]->getWidth(), sprites[ 0 ]->getHeight() /4 ) );
	rect.setFillColor( sf::Color( 0x99, 0x99, 0x00, 0x99 ) );
}

void Tiles::draw( sf::RenderWindow* &window )
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
	
	if( !fadingout )
	{
		for( unsigned i = 0; i < ualpha.size(); i++ )
		{
			if( ualpha[ i ] > 0 )
			{
				if( ufs[ i ].x < border_x +screen_w && ufs[ i ].y < border_y +screen_h )
				{
					if( ufs[ i ].x +sprites[ utypes[ i ] ]->getWidth() > border_x && ufs[ i ].y +sprites[ utypes[ i ] ]->getHeight() > border_y )
					{
						float alpha = sprites[ utypes[ i ] ]->getAlpha();
						sprites[ utypes[ i ] ]->setAlpha( ualpha[ i ] );
						sprites[ utypes[ i ] ]->setPosition( ufs[ i ].x, ufs[ i ].y );
						window->draw( sprites[ utypes[ i ] ]->get() );
						sprites[ utypes[ i ] ]->setAlpha( alpha );
					}
				}
			}
		}
	}
	
	// Test.
	if( collision )
	{
		window->draw( rect );
		rect.setPosition( -rect.getSize().x, -rect.getSize().y );
	}
}

void Tiles::fadein( float v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
	
	fadingout = false;
}

void Tiles::fadeout( float v, int min )
{
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
	
	fadingout = true;
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
				float x = con::stoi( data[ 2 ] ) *0.995;
				float y = con::stoi( data[ 3 ] ) +my_screen_h;
				
				if( w == 1 )
				{
					types.push_back( t );
					fs.push_back( sf::Vector2f( x, y ) );
				}
				else if( w == 2 )
				{
					utypes.push_back( t );
					ufs.push_back( sf::Vector2f( x, y ) );
					ualpha.push_back( 0 );
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
	sf::Uint8 t;
	
	// Visible tiles.
	for( unsigned i = 0; i < fs.size(); i++ )
	{
		x = fs[ i ].x;
		y = fs[ i ].y;
		t = types[ i ];
		
		if( x < border_x +screen_w && y < border_y +screen_h )
		{
			if( x +sprites[ t ]->getWidth() > border_x && y +sprites[ t ]->getHeight() > border_y )
			{
				sprites[ t ]->setPosition( x, y );
				if( sprites[ t ]->checkCollisionRect( rect ) )
				{
					if( rect.top > y )	this->rect.setPosition( sf::Vector2f(x, y +sprites[ t ]->getHeight() -this->rect.getSize().y) );
					else				this->rect.setPosition( sf::Vector2f(x, y) );
					return true;
				}
			}
		}
	}
	
	// Unvisible tiles.
	for( unsigned i = 0; i < ufs.size(); i++ )
	{
		x = ufs[ i ].x;
		y = ufs[ i ].y;
		t = utypes[ i ];
		
		if( x < border_x +screen_w && y < border_y +screen_h )
		{
			if( x +sprites[ t ]->getWidth() > border_x && y +sprites[ t ]->getHeight() > border_y )
			{
				sprites[ t ]->setPosition( x, y );
				if( sprites[ t ]->checkCollisionRect( rect ) )
				{
					if( rect.top < y )	this->rect.setPosition( sf::Vector2f(x, y) );
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
	sf::Uint8 t;
	
	// Unvisible tiles but for alpha.
	for( unsigned i = 0; i < ufs.size(); i++ )
	{
		x = ufs[ i ].x;
		y = ufs[ i ].y;
		t = utypes[ i ];
		
		if( ualpha[ i ] > 0 )
		{
			ualpha[ i ] -= elapsedTime *0xFF/2;
		}
		
		if( x < border_x +screen_w && y < border_y +screen_h )
		{
			if( x +sprites[ t ]->getWidth() > border_x && y +sprites[ t ]->getHeight() > border_y )
			{
				sprites[ t ]->setPosition( x, y );
				if( sprites[ t ]->checkCollisionRect( rect ) )
				{
					if( ualpha[ i ] < 0xFF /2 )
					{
						ualpha[ i ] += elapsedTime *0xFF;
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