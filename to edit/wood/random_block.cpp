#include "wood/random_block.h"



bool Random_block::checkCollision( int x, int y, int w, int h )
{
	for( unsigned i = 0; i < envelope.size(); i++ )
	{
		if( envelope[ i ]->line )
		{
			if( block[ envelope[ i ]->nr ].checkCollision( x, y, w, h ) )
				return true;
		}
	}
	
	return false;
}

Block::Block()
{
	nr = x = y = 0;
	line = false;
}

Law::Law( int nr, bool law )
{
	this->nr = nr;
	this->law = law;
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
	
	for( unsigned i = 0; i < rules_right.size(); i++ )
	{
		rules_right[ i ].clear();
	}
	
	rules_right.clear();
	
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
	
	ruleRightSide();
	
	// start
	positioning();
}

void Random_block::draw( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < envelope.size(); i++ )
	{
		if( envelope[ i ]->line )
		{
			block[ envelope[ i ]->nr ].setPosition( envelope[ i ]->x, envelope[ i ]->y );
			window->draw( block[ envelope[ i ]->nr ].get() );
		}
	}
}

void Random_block::drawBG( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < envelope.size(); i++ )
	{
		if( !envelope[ i ]->line )
		{
			block[ envelope[ i ]->nr ].setPosition( envelope[ i ]->x, envelope[ i ]->y );
			window->draw( block[ envelope[ i ]->nr ].get() );
		}
	}
}

void Random_block::positioning()
{
	envelope.push_back( new Block() );
	envelope[ 0 ]->nr = 1;
	envelope[ 0 ]->x = 0;
	envelope[ 0 ]->y = screen_h -width;
	envelope[ 0 ]->line = true;
	
	envelope.push_back( new Block() );
	envelope[ 1 ]->nr = 15;
	envelope[ 1 ]->x = 128;
	envelope[ 1 ]->y = screen_h -width;
	envelope[ 1 ]->line = true;
	
	envelope.push_back( new Block() );
	envelope[ 2 ]->nr = 11;
	envelope[ 2 ]->x = 256;
	envelope[ 2 ]->y = screen_h -width;
	envelope[ 2 ]->line = true;
	
	envelope.push_back( new Block() );
	envelope[ 3 ]->nr = 13;
	envelope[ 3 ]->x = 256;
	envelope[ 3 ]->y = screen_h -width*2;
	envelope[ 3 ]->line = true;
	
	
}

int Random_block::getScreenWidth()
{
	return screen_w;
}

void Random_block::ruleRightSide()
{
	vector <Law*> temporary;
	
	// 0
	temporary.clear();
	temporary.push_back( new Law( 1 ) );
	temporary.push_back( new Law( 2 ) );
	temporary.push_back( new Law( 3 ) );
	rules_right.push_back( temporary );
	
	// 1
	temporary.clear();
	temporary.push_back( new Law( 2 ) );
	temporary.push_back( new Law( 3 ) );
	rules_right.push_back( temporary );
	
	// 2
	temporary.clear();
	temporary.push_back( new Law( -1 ) );	// means that the block can not be put on the right
	rules_right.push_back( temporary );
	
	// 3
	temporary.clear();
	temporary.push_back( new Law( 14 ) );
	rules_right.push_back( temporary );
	
	// 4
	temporary.clear();
	temporary.push_back( new Law( 1 ) );
	temporary.push_back( new Law( 2 ) );
	temporary.push_back( new Law( 3 ) );
	rules_right.push_back( temporary );
	
	// 5
	temporary.clear();
	temporary.push_back( new Law( 6 ) );
	rules_right.push_back( temporary );
	
	// 6
	temporary.clear();
	temporary.push_back( new Law( 7 ) );
	rules_right.push_back( temporary );
	
	// 7
	temporary.clear();
	temporary.push_back( new Law( -1 ) );
	rules_right.push_back( temporary );
	
	// 8
	temporary.clear();
	temporary.push_back( new Law( 9 ) );
	temporary.push_back( new Law( 15 ) );
	rules_right.push_back( temporary );
	
	// 9
	temporary.clear();
	temporary.push_back( new Law( -1 ) );
	rules_right.push_back( temporary );
	
	// 10
	temporary.clear();
	temporary.push_back( new Law( 11 ) );
	temporary.push_back( new Law( 12 ) );
	temporary.push_back( new Law( 13 ) );
	rules_right.push_back( temporary );
	
	// 11
	temporary.clear();
	temporary.push_back( new Law( 12 ) );
	temporary.push_back( new Law( 13 ) );
	rules_right.push_back( temporary );
	
	// 12
	temporary.clear();
	temporary.push_back( new Law( -1 ) );
	rules_right.push_back( temporary );
	
	// 13
	temporary.clear();
	temporary.push_back( new Law( 14 ) );
	rules_right.push_back( temporary );
	
	// 14
	temporary.clear();
	temporary.push_back( new Law( 11 ) );
	temporary.push_back( new Law( 12 ) );
	temporary.push_back( new Law( 13 ) );
	rules_right.push_back( temporary );
	
	// 15
	temporary.clear();
	temporary.push_back( new Law( 9 ) );
	rules_right.push_back( temporary );
}