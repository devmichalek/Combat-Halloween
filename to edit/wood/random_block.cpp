#include "wood/random_block.h"

bool Random_block::checkCollisionH( int x, int w )
{
	for( unsigned i = 0; i < envelope.size(); i++ )
	{
		if( block[ envelope[ i ]->nr ].catchHorizontally( x, w ) )
			return true;
	}
	
	return false;
}

bool Random_block::checkCollisionV( int y, int h )
{
	for( unsigned i = 0; i < envelope.size(); i++ )
	{
		if( block[ envelope[ i ]->nr ].catchVertically( y, h ) )
			return true;
	}
	
	return false;
}




Block::Block()
{
	nr = x = y = 0;
	line = false;
}

Random_block::Random_block()
{
	nr = 0;
	block = NULL;
	
	width = 0;
	screen_w = 0;
	screen_h = 0;
}

Random_block::~Random_block()
{
	free();
}

void Random_block::free()
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
}

	
void Random_block::load( int screen_w, int screen_h, int number )
{
	free();
	
	string path = "data/txt/map/" + to_string( number ) + "/";
	width = 128;
	this->screen_w = screen_w;
	this->screen_h = screen_h;


	// load blocks
	if( number == 0 )		nr = 30;
	else if( number == 1 )	nr = 31;
	else if( number == 2 )	nr = 28;
	else					nr = 30;
	block = new MySprite[ nr ];
	for( int i = 0; i < nr; i++ )
	{
		block[ i ].setName( "palette-block[" +to_string( i ) +"]" );
		block[ i ].load( "data/sprites/play/" +to_string( number ) +"/" +to_string( i ) +".png" );
		block[ i ].setAlpha( 0xFF );
	}
	
	
	positioning();
}

void Random_block::draw( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < envelope.size(); i++ )
	{
		block[ envelope[ i ]->nr ].setPosition( envelope[ i ]->x, envelope[ i ]->y );
		window->draw( block[ envelope[ i ]->nr ].get() );
	}
}

void Random_block::positioning()
{
	envelope.push_back( new Block() );
	
	// first block
	envelope[ 0 ]->nr = 0;
	envelope[ 0 ]->x = 0;
	envelope[ 0 ]->y = screen_h -block[ 0 ].getHeight();
	envelope[ 0 ]->line = true;
}