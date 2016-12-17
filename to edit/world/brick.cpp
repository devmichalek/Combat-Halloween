#include "world/brick.h"


void Brick::positioning()
{
	for( int i = 0; i < 8; i ++ )
	{
		envelope.push_back( new Block() );
		envelope[ envelope.size()-1 ]->nr = 1;
		envelope[ envelope.size()-1 ]->x = width *i;
		envelope[ envelope.size()-1 ]->y = screen_h -width;
	}

	ladders.push_back( new Block() );
	ladders[ ladders.size()-1 ]->nr = 31;
	ladders[ ladders.size()-1 ]->x = width;
	ladders[ ladders.size()-1 ]->y = screen_h -width -block[ 31 ].getHeight();
	
	ladders.push_back( new Block() );
	ladders[ ladders.size()-1 ]->nr = 31;
	ladders[ ladders.size()-1 ]->x = width -block[ 31 ].getWidth();
	ladders[ ladders.size()-1 ]->y = screen_h -width*2 -block[ 31 ].getHeight();
	
	envelope.push_back( new Block() );
	envelope[ envelope.size()-1 ]->nr = 2;
	envelope[ envelope.size()-1 ]->x = 0;
	envelope[ envelope.size()-1 ]->y = screen_h -width*2;
	
	envelope.push_back( new Block() );
	envelope[ envelope.size()-1 ]->nr = 5;
	envelope[ envelope.size()-1 ]->x = width*6;
	envelope[ envelope.size()-1 ]->y = screen_h -width*2;
	
	envelope.push_back( new Block() );
	envelope[ envelope.size()-1 ]->nr = 6;
	envelope[ envelope.size()-1 ]->x = width*7;
	envelope[ envelope.size()-1 ]->y = screen_h -width*2;
	
	
	ladders.push_back( new Block() );
	ladders[ ladders.size()-1 ]->nr = 31;
	ladders[ ladders.size()-1 ]->x = width*6 -block[ 31 ].getWidth();
	ladders[ ladders.size()-1 ]->y = screen_h -block[ 31 ].getHeight() -width;
	
	ladders.push_back( new Block() );
	ladders[ ladders.size()-1 ]->nr = 31;
	ladders[ ladders.size()-1 ]->x = width*6;
	ladders[ ladders.size()-1 ]->y = screen_h -width*2 -block[ 31 ].getHeight();
	
	
	envelope.push_back( new Block() );
	envelope[ envelope.size()-1 ]->nr = 5;
	envelope[ envelope.size()-1 ]->x = width;
	envelope[ envelope.size()-1 ]->y = screen_h -width*3 -50;
	
	envelope.push_back( new Block() );
	envelope[ envelope.size()-1 ]->nr = 6;
	envelope[ envelope.size()-1 ]->x = width*2;
	envelope[ envelope.size()-1 ]->y = screen_h -width*3 -50;
	
	envelope.push_back( new Block() );
	envelope[ envelope.size()-1 ]->nr = 6;
	envelope[ envelope.size()-1 ]->x = width*3;
	envelope[ envelope.size()-1 ]->y = screen_h -width*3 -50;
	
	envelope.push_back( new Block() );
	envelope[ envelope.size()-1 ]->nr = 6;
	envelope[ envelope.size()-1 ]->x = width*4;
	envelope[ envelope.size()-1 ]->y = screen_h -width*3 -50;
	
	envelope.push_back( new Block() );
	envelope[ envelope.size()-1 ]->nr = 7;
	envelope[ envelope.size()-1 ]->x = width*5;
	envelope[ envelope.size()-1 ]->y = screen_h -width*3 -50;
}



bool Brick::checkCollision( Rect* rect )
{
	if( rect != NULL )
	{
		for( unsigned i = 0; i < envelope.size(); i++ )
		{
			if( envelope[ i ]->line )
			{
				block[ envelope[ i ]->nr ].setPosition( envelope[ i ]->x, envelope[ i ]->y );
				if( block[ envelope[ i ]->nr ].checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
				{
					return true;
				}
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
		
		for( unsigned i = 0; i < envelope.size(); i++ )
		{
			if( envelope[ i ]->line )
			{
				block[ envelope[ i ]->nr ].setPosition( envelope[ i ]->x, envelope[ i ]->y );
				
				for( int j = l; j <= r; j++ )
				{
					if( block[ envelope[ i ]->nr ].checkPixelCollision( j, t ) )		return true;
					else if( block[ envelope[ i ]->nr ].checkPixelCollision( j, b ) )	return true;
				}
				
				for( int j = t; j <= b; j++ )
				{
					if( block[ envelope[ i ]->nr ].checkPixelCollision( l, j ) )		return true;
					else if( block[ envelope[ i ]->nr ].checkPixelCollision( r, j ) )	return true;
				}
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
			block[ ladders[ i ]->nr ].setPosition( ladders[ i ]->x, ladders[ i ]->y );
			if( block[ ladders[ i ]->nr ].checkCollision( rect->getX(), rect->getY() -50, rect->getWidth(), rect->getHeight() ) )
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
	
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	envelope.clear();
	ladders.clear();
}




void Brick::load( int screen_w, int screen_h, int number )
{
	free();
	
	string path = "data/txt/map/" + to_string( number ) + "/";
	width = 128;
	this->screen_w = screen_w;
	this->screen_h = screen_h;


	// load blocks
	if( number == 0 )		nr = 31;
	else if( number == 1 )	nr = 32;
	else if( number == 2 )	nr = 29;
	else					nr = 31;
	block = new MySprite[ nr ];
	for( int i = 0; i < nr; i++ )
	{
		block[ i ].setName( "palette-block[" +to_string( i ) +"]" );
		block[ i ].loadByImage( "data/sprites/play/" +to_string( number ) +"/" +to_string( i ) +".png" );
	}
	
	// start
	positioning();
}

void Brick::draw( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < envelope.size(); i++ )
	{
		if( !envelope[ i ]->bg )
		{
			block[ envelope[ i ]->nr ].setPosition( envelope[ i ]->x, envelope[ i ]->y );
			window->draw( block[ envelope[ i ]->nr ].get() );
		}
	}
}

void Brick::drawBG( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < envelope.size(); i++ )
	{
		if( envelope[ i ]->bg )
		{
			block[ envelope[ i ]->nr ].setPosition( envelope[ i ]->x, envelope[ i ]->y );
			window->draw( block[ envelope[ i ]->nr ].get() );
		}
	}
	
	for( unsigned i = 0; i < ladders.size(); i++ )
	{
		block[ ladders[ i ]->nr ].setPosition( ladders[ i ]->x, ladders[ i ]->y );
		window->draw( block[ ladders[ i ]->nr ].get() );
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
}

void Brick::fadeout( int v, int min )
{
	for( int i = 0; i < nr; i++ )
	{
		block[ i ].fadeout( v, min );
	}
}