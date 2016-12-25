#include "world/brick.h"
#include "world/rules.h"
#include <cstdlib>	// rand

void Brick::positioning() // algorithm
{
	Rules* rules = new Rules;
//-------------------------------------------------------------------------------------
	
	rules->ruleRightSide();
	rules->ruleLeftSide();
	rules->ruleBotSide();
	
		
	
	unsigned scope = 0;
	int result = 0;
	
	int c = 10; // how many blocks
	while( c-- )
	{
		// get scope
		scope = rules->getRightRules( blocks[ blocks.size()-1 ]->nr ).size();
		
		// get result
		result = rules->getRightRules( blocks[ blocks.size()-1 ]->nr )[ rand()%scope ]->nr;
		
		// add block
		blocks.push_back( new Block() );
		blocks[ blocks.size()-1 ]->nr = result;
		blocks[ blocks.size()-1 ]->x = blocks[ blocks.size()-2 ]->x +width;
		blocks[ blocks.size()-1 ]->y = screen_h -width;
	}
	
	ladders.push_back( new Ladder() );
	ladders[ 0 ]->x = screen_w *3/4;
	ladders[ 0 ]->y = screen_h -width -ladder.getHeight();
	
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 7;
	blocks[ blocks.size()-1 ]->x = screen_w *3/4 -width;
	blocks[ blocks.size()-1 ]->y = screen_h -width*3;
	
//-------------------------------------------------------------------------------------
	delete rules;
}



bool Brick::checkCollision( Rect* rect )
{
	if( rect != NULL )
	{
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			if( blocks[ i ]->nr != -1 )
			{
				if( blocks[ i ]->x > -width && blocks[ i ]->x < screen_w )
				{
					block[ blocks[ i ]->nr ].setPosition( blocks[ i ]->x, blocks[ i ]->y );
					if( block[ blocks[ i ]->nr ].checkCollision( rect->getX(), rect->getY(), rect->getWidth(), rect->getHeight() ) )
					{
						return true;
					}
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
		
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			if( blocks[ i ]->nr != -1 )
			{
				if( blocks[ i ]->x > -width && blocks[ i ]->x < screen_w )
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
			if( ladders[ i ]->x > -width && ladders[ i ]->x < screen_w )
			{
				ladder.setPosition( ladders[ i ]->x, ladders[ i ]->y );
				if( ladder.checkCollision( rect->getX() +rect->getWidth() /4, rect->getY() -50, rect->getWidth() /2, rect->getHeight() ) )
				{
					return true;
				}
			}
		}
	}
	
	return false;
}



sf::Uint8 Brick::moveX( sf::Uint8 direction, float vel )
{
	if( direction == 1 )
	{
		// Searching for bop X
		int left = 0;
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			if( blocks[ i ]->x < left )
			{
				left = blocks[ i ]->x;
			}
		}
		
		if( left > -10 )
		{
			return 1;
		}
		
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			blocks[ i ]->x += vel;
		}
		
		for( unsigned i = 0; i < ladders.size(); i++ )
		{
			ladders[ i ]->x += vel;
		}
	}
	else if( direction == 2 )
	{
		// Searching for top X
		int right = 0;
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			if( blocks[ i ]->x > right )
			{
				right = blocks[ i ]->x;
			}
		}
		
		if( right < screen_w -width +10 )
		{
			return 2;
		}
		
		for( unsigned i = 0; i < blocks.size(); i++ )
		{
			blocks[ i ]->x -= vel;
		}
		
		for( unsigned i = 0; i < ladders.size(); i++ )
		{
			ladders[ i ]->x -= vel;
		}
	}
	
	return 0;
}

sf::Uint8 Brick::getWidth()
{
	return width;
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
	
	blocks.push_back( new Block() );
	blocks[ blocks.size()-1 ]->nr = 1;
	blocks[ blocks.size()-1 ]->x = 0;
	blocks[ blocks.size()-1 ]->y = screen_h -width;
	
	// start
	positioning();
}

void Brick::draw( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < blocks.size(); i++ )
	{
		if( blocks[ i ]->nr != -1 )
		{
			if( blocks[ i ]->x > -width && blocks[ i ]->x < screen_w )
			{
				block[ blocks[ i ]->nr ].setPosition( blocks[ i ]->x, blocks[ i ]->y );
				window->draw( block[ blocks[ i ]->nr ].get() );
			}
		}
	}
}

void Brick::drawLadders( sf::RenderWindow* &window )
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