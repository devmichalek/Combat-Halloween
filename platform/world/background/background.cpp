#include "background.h"
#include "file/file.h"

Background::Background()
{
	free();
}

Background::~Background()
{
	free();
}

void Background::free()
{
	if( !sprites.empty() )
	{
		for( auto &it :sprites )
		{
			it->free();
		}
		
		sprites.clear();
	}
}




void Background::load( int type, unsigned screen_w, unsigned screen_h )
{
	free();
	
	if( type == 1 )
	{
		for( unsigned i = 0; i < 2; i++ )
		{
			sprites.push_back( new MySprite() );
			sprites[ sprites.size() -1 ]->setName( "background-sprite" );
			sprites[ sprites.size() -1 ]->load( "data/platform/world/1/bg" +con::itos( i ) +".png" );
			
			float scale_x = 1, scale_y = 1;
			
			if( screen_w > sprites[ sprites.size() -1 ]->getWidth() )
			{
				scale_x = static_cast <float> (screen_w) /sprites[ sprites.size() -1 ]->getWidth();
			}
			
			if( screen_h > sprites[ sprites.size() -1 ]->getHeight() )
			{
				scale_y = static_cast <float> (screen_h) /sprites[ sprites.size() -1 ]->getHeight();
			}
			
			sprites[ sprites.size() -1 ]->setScale( scale_x, scale_y );
			
			sprites[ sprites.size() -1 ]->setPosition( screen_w /2 -sprites[ sprites.size() -1 ]->getWidth() /2,
													   screen_h /2 -sprites[ sprites.size() -1 ]->getHeight() /2 );
		}
	}
	else
	{
		sprites.push_back( new MySprite() );
		sprites[ sprites.size() -1 ]->setName( "background-sprite" );
		sprites[ sprites.size() -1 ]->load( "data/platform/world/" +con::itos( type ) +"/bg.png" );
		
		float scale_x = 1, scale_y = 1;
			
		if( screen_w > sprites[ sprites.size() -1 ]->getWidth() )
		{
			scale_x = static_cast <float> (screen_w) /sprites[ sprites.size() -1 ]->getWidth();
		}
		
		if( screen_h > sprites[ sprites.size() -1 ]->getHeight() )
		{
			scale_y = static_cast <float> (screen_h) /sprites[ sprites.size() -1 ]->getHeight();
		}
		
		sprites[ sprites.size() -1 ]->setScale( scale_x, scale_y );
			
		sprites[ sprites.size() -1 ]->setPosition( screen_w /2 -sprites[ sprites.size() -1 ]->getWidth() /2,
													   screen_h /2 -sprites[ sprites.size() -1 ]->getHeight() /2 );
	}
}

void Background::draw( sf::RenderWindow* &window )
{
	window->draw( sprites[ 0 ]->get() );
}

void Background::drawFront( sf::RenderWindow* &window )
{
	window->draw( sprites[ sprites.size() -1 ]->get() );
}


void Background::fadein( int v, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( v, max );
	}
}

void Background::fadeout( int v, int min )
{
	if( sprites.size() > 1 )
	{
		sprites[ sprites.size() -1 ]->setAlpha( min );
	}
	
	for( auto &it :sprites )
	{
		it->fadeout( v, min );
	}
}



sf::Uint8 Background::getAlpha()
{
	return sprites[ 0 ]->getAlpha();
}

void Background::setColor( sf::Color color )
{
	for( auto &it :sprites )
	{
		it->setColor( color );
	}
}