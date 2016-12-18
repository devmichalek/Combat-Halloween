#include "world/brick.h"


void Brick::positioning()
{
	for( int i = 0; i < 8; i ++ )
	{
		blocks.push_back( new Block() );
		blocks[ blocks.size()-1 ]->nr = 1;
		blocks[ blocks.size()-1 ]->x = width *i;
		blocks[ blocks.size()-1 ]->y = screen_h -width;
	}

	ladders.push_back( new Ladder() );
	ladders[ ladders.size()-1 ]->x = width;
	ladders[ ladders.size()-1 ]->y = screen_h -width -ladder.getHeight();
	
	ladders.push_back( new Ladder() );
	ladders[ ladders.size()-1 ]->x = width -ladder.getWidth();
	ladders[ ladders.size()-1 ]->y = screen_h -width*2 -ladder.getHeight();
	
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 2;
	blocks[ blocks.size()-1 ]->x = 0;
	blocks[ blocks.size()-1 ]->y = screen_h -width*2;
	
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 5;
	blocks[ blocks.size()-1 ]->x = width*5;
	blocks[ blocks.size()-1 ]->y = screen_h -width*2;
	
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 7;
	blocks[ blocks.size()-1 ]->x = width*6;
	blocks[ blocks.size()-1 ]->y = screen_h -width*2;
	
	
	ladders.push_back( new Ladder() );
	ladders[ ladders.size()-1 ]->x = width*5 -ladder.getWidth();
	ladders[ ladders.size()-1 ]->y = screen_h -ladder.getHeight() -width;
	
	ladders.push_back( new Ladder() );
	ladders[ ladders.size()-1 ]->x = width*5;
	ladders[ ladders.size()-1 ]->y = screen_h -width*2 -ladder.getHeight();
	
	
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 5;
	blocks[ blocks.size()-1 ]->x = width;
	blocks[ blocks.size()-1 ]->y = screen_h -width*4;
	
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 6;
	blocks[ blocks.size()-1 ]->x = width*2;
	blocks[ blocks.size()-1 ]->y = screen_h -width*4;
	
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 6;
	blocks[ blocks.size()-1 ]->x = width*3;
	blocks[ blocks.size()-1 ]->y = screen_h -width*4;
	
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 7;
	blocks[ blocks.size()-1 ]->x = width*4;
	blocks[ blocks.size()-1 ]->y = screen_h -width*4;
	
	
	
	
	
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 5;
	blocks[ blocks.size()-1 ]->x = width*6;
	blocks[ blocks.size()-1 ]->y = screen_h -width*4;
	
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 7;
	blocks[ blocks.size()-1 ]->x = width*7;
	blocks[ blocks.size()-1 ]->y = screen_h -width*4;
}



bool Brick::checkCollision( Rect* rect )
{
	if( rect != NULL )
	{
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			block[ blocks[ i ]->nr ].setPosition( blocks[ i ]->x, blocks[ i ]->y );
			if( block[ blocks[ i ]->nr ].checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
			{
				return true;
			}
		}
	}
	
	return false;
}

bool Brick::checkBlockByPixel( Rect* rect )
{
	if( rect != NULL )
	{
		int l = rect->getX();		// left
		int r = rect->getRight();	// right
		int t = rect->getY();		// top
		int b = rect->getBot(); 		// bot
		
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			block[ blocks[ i ]->nr ].setPosition( blocks[ i ]->x, blocks[ i ]->y );
			
			for( int j = l; j <= r; j++ )
			{
				if( block[ blocks[ i ]->nr ].checkPixelCollision( j, t ) )		return true;
				else if( block[ blocks[ i ]->nr ].checkPixelCollision( j, b ) )	return true;
			}
			
			for( int j = t; j <= b; j++ )
			{
				if( block[ blocks[ i ]->nr ].checkPixelCollision( l, j ) )		return true;
				else if( block[ blocks[ i ]->nr ].checkPixelCollision( r, j ) )	return true;
			}
		}
	}
	
	return false;
}

bool Brick::checkLadder( Rect* rect )
{
	if( rect != NULL )
	{
		for( unsigned i = 0; i < ladders.size(); i++ )
		{
			ladder.setPosition( ladders[ i ]->x, ladders[ i ]->y );
			if( ladder.checkCollision( rect->getX() +rect->getWidth() /4, rect->getY() -50, rect->getWidth() /2, rect->getHeight() ) )
			{
				return true;
			}
		}
	}
	
	return false;
}





Brick::Brick()
{
	nr = 0;
	block = NULL;
	
	width = 0;
	screen_w = 0;
	screen_h = 0;
}

Brick::~Brick()
{
	free();
}

void Brick::free()
{
	if( block != NULL )
	{
		for( int i = 0; i < nr; i++ )
		{
			block[ i ].free();
		}
		
		delete [] block;
		block = NULL;
		nr = 0;
	}
	
	ladder.free();
	
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	blocks.clear();
	ladders.clear();
}




void Brick::load( int screen_w, int screen_h, int nr, int type )
{
	free();
	
	width = 128;
	this->screen_w = screen_w;
	this->screen_h = screen_h;

	this->nr = nr;
	block = new MySprite[ nr ];
	
	for( int i = 0; i < nr; i++ )
	{
		block[ i ].setName( "brick-block[" +to_string( i ) +"]" );
		block[ i ].loadByImage( "data/sprites/play/" +to_string( type ) +"/" +to_string( i ) +".png" );
	}
	
	ladder.setName( "brick-ladder" );
	ladder.loadByImage( "data/sprites/play/0/ladder.png" );
	
	// start
	positioning();
}

void Brick::draw( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		block[ blocks[ i ]->nr ].setPosition( blocks[ i ]->x, blocks[ i ]->y );
		window->draw( block[ blocks[ i ]->nr ].get() );
	}
}

void Brick::drawBG( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < ladders.size(); i++ )
	{
		ladder.setPosition( ladders[ i ]->x, ladders[ i ]->y );
		ladder.setColor( sf::Color( ladders[ i ]->red, ladders[ i ]->green, ladders[ i ]->blue ) );
		window->draw( ladder.get() );
	}
}





int Brick::getScreenWidth()
{
	return screen_w;
}

void Brick::fadein( int v, int max )
{
	for( int i = 0; i < nr; i++ )
	{
		block[ i ].fadein( v, max );
	}
	
	ladder.fadein( v, max );
}

void Brick::fadeout( int v, int min )
{
	for( int i = 0; i < nr; i++ )
	{
		block[ i ].fadeout( v, min );
	}
	
	ladder.fadeout( v, min );
}