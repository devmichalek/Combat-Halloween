#include "moving_bg.h"
#include "own/file.h"

Moving_bg::Moving_bg()
{
	free();
}

Moving_bg::~Moving_bg()
{
	free();
}

void Moving_bg::free()
{
	type = 0;
	screen_w = 0;
	screen_h = 0;
	velocity = 0;
	
	if( !types.empty() )
	{
		types.clear();
	}
	
	if( !fs.empty() )
	{
		fs.clear();
	}
	
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
}



void Moving_bg::load( float screen_w, float screen_h, int type )
{
	free();
	
	this->type = type;
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	velocity = 30;
	
	if( type == 0 )
	{
		for( unsigned i = 0; i < 3; i++ )
		{
			sprites.push_back( new MySprite() );
			sprites[ i ]->setIdentity( "moving_bg-sprites" );
			sprites[ i ]->load( "images/play/background/0/" +con::itos(i) +".png" );
			sprites[ i ]->setScale( screen_w /2560, screen_h /1440 );
		}
		
		sprites[ 1 ]->setPosition( 0, screen_h -sprites[ 1 ]->getHeight() -411 *screen_h /1440 );
		sprites[ 2 ]->setPosition( 0, screen_h -sprites[ 2 ]->getHeight() );
		
		fs.push_back( sf::Vector2f( 0, 0 ) );
		fs.push_back( sf::Vector2f( screen_w, sprites[ 1 ]->getY() ) );
		fs.push_back( sf::Vector2f( 0, sprites[ 1 ]->getY() ) );
		fs.push_back( sf::Vector2f( screen_w, sprites[ 2 ]->getY() ) );
		fs.push_back( sf::Vector2f( 0, sprites[ 2 ]->getY() ) );
		
		types.push_back( 0 );
		types.push_back( 1 );
		types.push_back( 1 );
		types.push_back( 2 );
		types.push_back( 2 );
	}
	else
	{
		for( unsigned i = 0; i < 2; i++ )
		{
			sprites.push_back( new MySprite() );
			sprites[ i ]->setIdentity( "moving_bg-sprites" );
			sprites[ i ]->load( "images/play/background/1.png" );
			sprites[ i ]->setScale( screen_w /2560, screen_h /1440 );
		}
		
		fs.push_back( sf::Vector2f( 0, 0 ) );
		fs.push_back( sf::Vector2f( screen_w, 0 ) );
	}
}

void Moving_bg::draw( sf::RenderWindow* &window )
{
	if( type == 0 )
	{
		for( unsigned i = 0; i < fs.size(); i++ )
		{
			sprites[ types[ i ] ]->setPosition( fs[ i ].x, fs[ i ].y );
			window->draw( sprites[ types[ i ] ]->get() );
		}
	}
	else
	{
		for( auto &it :fs )
		{
			sprites[ 0 ]->setPosition( it.x, it.y );
			window->draw( sprites[ 0 ]->get() );
		}
	}
}

void Moving_bg::mechanics( double elapsedTime, float direction )
{
	if( type == 0 )
	{
		for( unsigned i = 1; i < fs.size(); i++ )
		{
			if( i == 3 || i == 4 )	fs[ i ].x += velocity *elapsedTime *direction;
			else					fs[ i ].x += -velocity /2 *elapsedTime *direction;
			
			if( fs[ i ].x < -screen_w )
			{
				fs[ i ].x = screen_w;
			}
			else if( fs[ i ].x > screen_w )
			{
				fs[ i ].x = -screen_w;
			}
		}
	}
	else
	{
		for( unsigned i = 0; i < fs.size(); i++ )
		{
			fs[ i ].x += velocity *elapsedTime *direction;
			
			if( fs[ i ].x < -screen_w )
			{
				fs[ i ].x = screen_w;
			}
			else if( fs[ i ].x > screen_w )
			{
				fs[ i ].x = -screen_w;
			}
		}
	}
}



void Moving_bg::fadein( float v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
}

void Moving_bg::fadeout( float v, int min )
{
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
}



float Moving_bg::getAlpha()
{
	return sprites[ 0 ]->getAlpha();
}