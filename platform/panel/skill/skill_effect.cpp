#include "skill_effect.h"
#include "file/file.h"

Skill_effect::Skill_effect()
{
	free();
}

Skill_effect::~Skill_effect()
{
	free();
}

void Skill_effect::free()
{
	screen_w = 0;
	screen_h = 0;
	
	line = 0;
	vel = 0;
	
	
	if( !scales.empty() )
	{
		scales.clear();
	}
	
	if( !alphas.empty() )
	{
		alphas.clear();
	}
	
	if( !counters.empty() )
	{
		counters.clear();
	}
	
	if( !sprites.empty() )
	{
		for( auto &it: sprites )
		{
			it->free();
		}
		
		sprites.clear();
	}
}

void Skill_effect::reset()
{
	for( auto &it: scales )
	{
		it = 1;
	}
	
	for( auto &it: alphas )
	{
		it = 0xFF;
	}
	
	for( auto &it: counters )
	{
		it = 0;
	}
}



void Skill_effect::load( unsigned FPS, int screen_w, int screen_h )
{
	free();
	
	this->screen_w = screen_w;
	this->screen_h = screen_h;
	
	int seconds = 3;
	line = FPS *seconds;
	vel = 1;
	
	int max = 4;
	for( int i = 0; i < max; i++ )
	{
		scales.push_back( 1 );
		alphas.push_back( 0xFF );
		counters.push_back( 0 );
		sprites.push_back( new MySprite() );
		sprites[ sprites.size() -1 ]->setName( "skill_effect-sprites" );
		sprites[ sprites.size() -1 ]->load( "data/platform/panel/skill/effect/" +con::itos( i+2 ) +".png" );
		sprites[ sprites.size() -1 ]->center( 0, 0, screen_w, screen_h );
		sprites[ sprites.size() -1 ]->setAlpha( 0xFF );
	}
}

void Skill_effect::draw( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < counters.size(); i++ )
	{
		if( counters[ i ] > 0 )
		{
			scales[ i ] -= 0.01;
			if( scales[ i ] <= 0 )
			{
				scales[ i ] = 0;
			}
			
			alphas[ i ] -= vel;
			if( alphas[ i ] <= 0 )
			{
				alphas[ i ] = 0;
			}
			
			counters[ i ] ++;
			if( counters[ i ] == line )
			{
				counters[ i ] = 0;
			}
			
			sprites[ i ]->setScale( scales[ i ], scales[ i ] );
			sprites[ i ]->center( 0, 0, screen_w, screen_h );
			sprites[ i ]->setAlpha( alphas[ i ] );
			window->draw( sprites[ i ]->get() );
		}
	}
}



void Skill_effect::run( int which )
{
	counters[ which ] = 1;
	alphas[ which ] = 0xFF;
	scales[ which ] = 1;
}
