#include "score_dots.h"
#include <cstdlib>
#include "file/file.h"


Score_dots::Score_dots()
{
	free();
}

Score_dots::~Score_dots()
{
	free();
}

void Score_dots::free()
{
	screen_w = 0;
	main_alpha = 0;
	sprite.free();
	if( !dots.empty() )
	{
		for( auto &it :dots )
		{
			delete it;
		}
		
		dots.clear();
	}
	
	point.free();
}

void Score_dots::reset( int distance )
{
	for( auto &it :dots )
	{
		it->active = true;
		it->x += distance;
	}
}



void Score_dots::load( int screen_w )
{
	free();
	
	this->screen_w = screen_w;
	
	sprite.setName( "score_dots-sprite" );
	sprite.load( "data/platform/panel/score/0.png" );
	
	
	point.setName( "score_dots-point" );
	point.load( "data/platform/world/sounds/score_dot/0.wav" );
}

void Score_dots::draw( sf::RenderWindow* &window )
{
	for( auto &it :dots )
	{
		if( it->active && it->x > -30 && it->x < screen_w )
		{
			// Set scale.
			sprite.setScale( it->scale, it->scale );
			
			// Set XY.
			sprite.setPosition( it->x, it->y );
			
			// Set angle.
			sprite.setAngle( it->angle );
			
			// Draw.
			window->draw( sprite.get() );
		}
	}
}

void Score_dots::positioning( int chance, vector <Block*> blocks, int width )
{
	for( auto &it: blocks )
	{
		if( it->nr >= 0 && it->nr <= 7 )
		{
			if( rand()%100 < 50 +chance/2 )
			{
				dots.push_back( new Hp_dot() );
				dots[ dots.size() -1 ]->active = true;
				dots[ dots.size() -1 ]->scale = static_cast <float> (rand()%25 +50) /100;
				dots[ dots.size() -1 ]->angle = static_cast <double> (rand()%360);
				
				// Set x, y.
				// printf( "%f %f\n", it->x, it->y );
				sprite.setScale( dots[ dots.size() -1 ]->scale, dots[ dots.size() -1 ]->scale );
				dots[ dots.size() -1 ]->x = it->x +(width/2) -(sprite.getWidth()/2);
				dots[ dots.size() -1 ]->y = static_cast <float> (it->y) -static_cast <float>(sprite.getHeight()/2) -(width/4);
			}
		}
	}
}




void Score_dots::fadein( int v, int max )
{
	sprite.fadein( v, max );
}

void Score_dots::fadeout( int v, int min )
{
	sprite.fadeout( v, min );
}



void Score_dots::moveX( sf::Uint8 d, float v )
{
	if( d == 1 )
	{
		for( auto &it :dots )
		{
			it->x += v;
		}
	}
	else if( d == 2 )
	{
		for( auto &it :dots )
		{
			it->x -= v;
		}
	}
	
}

void Score_dots::undoFall( sf::Uint8 add )
{
	for( auto &it :dots )
	{
		it->x += add;
	}
}

void Score_dots::mechanics()
{
	for( auto &it :dots )
	{
		if( it->active )
		{
			it->angle += 0.2;
			if( it->angle >= 360 )
			{
				it->angle = 0;
			}
		}
	}
}

void Score_dots::setAlpha( int alpha )
{
	main_alpha = alpha;
}

bool Score_dots::uplift( Rect* rect )
{
	if( rect != NULL )
	{
		for( auto &it :dots )
		{
			if( it->active && it->x > -30 && it->x < screen_w )
			{
				// Set scale.
				sprite.setScale( it->scale, it->scale );
				
				// Set XY.
				sprite.setPosition( it->x, it->y );
				
				if( sprite.checkRectCollision( *rect ) )
				{
					it->active = false;
					
					if( point.isPlayable() )
					{
						point.play();
					}
					
					return true;
				}
			}
		}
	}
	
	return false;
}



void Score_dots::turn()
{
	point.turn();
}

void Score_dots::turnOn()
{
	point.turnOn();
}

void Score_dots::turnOff()
{
	point.turnOff();
}

void Score_dots::setVolume( int v )
{
	point.setVolume( v );
}