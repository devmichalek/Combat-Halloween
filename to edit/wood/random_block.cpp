#include "wood/random_block.h"

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
	
	
	for( unsigned i = 0; i < rules_left.size(); i++ )
	{
		rules_left[ i ].clear();
	}
	rules_left.clear();
	
	
	for( unsigned i = 0; i < rules_bot.size(); i++ )
	{
		rules_bot[ i ].clear();
	}
	rules_bot.clear();
	
	
	for( unsigned i = 0; i < rules_top.size(); i++ )
	{
		rules_top[ i ].clear();
	}
	rules_top.clear();
	
	
	width = 0;
	screen_w = 0;
	screen_h = 0;
	
	envelope.clear();
	ladders.clear();
}

	
void Random_block::load( int screen_w, int screen_h, int number )
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
		block[ i ].load( "data/sprites/play/" +to_string( number ) +"/" +to_string( i ) +".png" );
	}
	
	ruleRightSide();
	ruleLeftSide();
	ruleBotSide();
	ruleTopSide( number );
	
	// start
	positioning();
}

void Random_block::draw( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < envelope.size(); i++ )
	{
		if( envelope[ i ]->bg )
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
		if( !envelope[ i ]->bg )
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

void Random_block::positioning()
{
	envelope.push_back( new Block() );
	envelope[ envelope.size()-1 ]->nr = 4;
	envelope[ envelope.size()-1 ]->x = 0;
	envelope[ envelope.size()-1 ]->y = screen_h -width;

	envelope.push_back( new Block() );
	envelope[ envelope.size()-1 ]->nr = 3;
	envelope[ envelope.size()-1 ]->x = width;
	envelope[ envelope.size()-1 ]->y = screen_h -width;
	
	envelope.push_back( new Block() );
	envelope[ envelope.size()-1 ]->nr = 14;
	envelope[ envelope.size()-1 ]->x = width*2;
	envelope[ envelope.size()-1 ]->y = screen_h -width;
	
	envelope.push_back( new Block() );
	envelope[ envelope.size()-1 ]->nr = 10;
	envelope[ envelope.size()-1 ]->x = width*2;
	envelope[ envelope.size()-1 ]->y = screen_h -width*2;
	
	
	ladders.push_back( new Block() );
	ladders[ ladders.size()-1 ]->nr = 31;
	ladders[ ladders.size()-1 ]->x = width*2 -5;
	ladders[ ladders.size()-1 ]->y = screen_h -width -block[ 31 ].getHeight();
	
	ladders.push_back( new Block() );
	ladders[ ladders.size()-1 ]->nr = 31;
	ladders[ ladders.size()-1 ]->x = 0;
	ladders[ ladders.size()-1 ]->y = screen_h -width -block[ 31 ].getHeight();
}

bool Random_block::checkCollision( int x, int y, int w, int h )
{
	for( unsigned i = 0; i < envelope.size(); i++ )
	{
		if( envelope[ i ]->line )
		{
			block[ envelope[ i ]->nr ].setPosition( envelope[ i ]->x, envelope[ i ]->y );
			if( block[ envelope[ i ]->nr ].checkCollision( x, y, w, h ) )
			{
				return true;
			}
		}
	}
	
	return false;
}

bool Random_block::checkLadder( int x, int y, int w, int h )
{
	for( unsigned i = 0; i < ladders.size(); i++ )
	{
		block[ ladders[ i ]->nr ].setPosition( ladders[ i ]->x, ladders[ i ]->y );
		if( block[ ladders[ i ]->nr ].checkCollision( x, y, w, h ) )
		{
			return true;
		}
	}
	
	return false;
}