#include "heart.h"

Heart::Heart()
{
	max = 0;
	flag = false;
	life = 0;
}

Heart::~Heart()
{
	free();
}

void Heart::free()
{
	if( !fill.empty() )
	{
		for( unsigned i = 0; i < fill.size(); i++ )
		{
			fill[ i ]->free();
		}
		
		fill.clear();
	}
	
	if( !frame.empty() )
	{
		for( unsigned i = 0; i < frame.size(); i++ )
		{
			frame[ i ]->free();
		}
		
		frame.clear();
	}
	
	if( !grey_panel.empty() )
	{
		for( unsigned i = 0; i < grey_panel.size(); i++ )
		{
			grey_panel[ i ]->free();
		}
		
		grey_panel.clear();
	}
	
	max = 0;
	flag = false;
	life = 0;
}

	
void Heart::load()
{
	free();
	
	max = 5;
	int nr = 2;
	float scale = 0.75;
	
	for( int i = 0; i < nr; i++ )
	{
		fill.push_back( new MySprite() );
		fill[ i ]->setName( "heart-fill[" + to_string( i ) + "]" );
		fill[ i ]->load( "data/sprites/hero/heart/fill.png");
		fill[ i ]->setScale( scale, scale );
		fill[ i ]->setPosition( 10 + (fill[ i ]->getWidth() +10)*i, 10 );
		
		frame.push_back( new MySprite() );
		frame[ i ]->setName( "heart-frame[" + to_string( i ) + "]" );
		frame[ i ]->load( "data/sprites/hero/heart/frame.png");
		frame[ i ]->setScale( scale, scale );
		frame[ i ]->setPosition( 10 + (frame[ i ]->getWidth() +10)*i, 10 );
	}
	
	for( int i = 0; i < max; i++ )
	{
		grey_panel.push_back( new MySprite() );
		grey_panel[ grey_panel.size() -1 ]->setName( "heart-gray_panel[" + to_string( i ) + "]" );
		grey_panel[ grey_panel.size() -1 ]->load( "data/sprites/hero/grey/grey_panel.png");
		grey_panel[ grey_panel.size() -1 ]->setScale( 0.5, 0.5 );
		grey_panel[ grey_panel.size() -1 ]->setPosition( 5 + (frame[ 0 ]->getWidth() +10)*i, 5 );
	}
}

void Heart::draw( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < grey_panel.size(); i++ )
	{
		window->draw( grey_panel[ i ]->get() );
	}
	
	for( unsigned i = 0; i < fill.size(); i++ )
	{
		window->draw( fill[ i ]->get() );
		window->draw( frame[ i ]->get() );
	}
	
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( 0 ) ) )
	{
		harm( -4 );
	}
	
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( 1 ) ) )
	{
		harm( 4 );
	}
}

void Heart::setLife( int chance )
{
	float newChance = 100 -( static_cast <float> (chance) /1.5);
	newChance /= 100;
	
	life = fill.size() *0xFF *newChance;
	harm( 0 );
}

void Heart::fadein( int v, int max )
{
	for( unsigned i = 0; i < grey_panel.size(); i++ )
	{
		grey_panel[ i ]->fadein( v, max );
	}
	
	if( !flag )
	{
		for( unsigned i = 0; i < fill.size(); i++ )
		{
			frame[ i ]->fadein( v, max );
		}
		
		if( frame[ 0 ]->getAlpha() == 0xFF )
		{
			flag = true;
		}
	}
}

void Heart::fadeout( int v, int min )
{
	for( unsigned i = 0; i < grey_panel.size(); i++ )
	{
		grey_panel[ i ]->fadeout( v, min );
	}
	
	for( unsigned i = 0; i < fill.size(); i++ )
	{
		fill[ i ]->fadeout( v, min );
		frame[ i ]->fadeout( v, min );
	}
}

void Heart::harm( int damage )
{
	life += damage;
	
	int temporary_life = 0;
	for( unsigned i = 0; i < fill.size(); i++ )
	{
		temporary_life += fill[ i ]->getAlpha();
	}
	
	if( temporary_life != life )
	{
		temporary_life = life;
		
		for( unsigned i = 0; i < fill.size(); i++ )
		{
			fill[ i ]->setAlpha( 0 );
		}
		
		if( temporary_life > 0 )
		{
			for( unsigned i = 0; i < fill.size(); i++ )
			{
				if( temporary_life < 0xFF )
				{
					fill[ i ]->setAlpha( temporary_life );
					break;
				}
				else
				{
					fill[ i ]->setAlpha( 0xFF );
				}
				
				temporary_life -= 0xFF;
			}
		}
	}
}

bool Heart::isDead()
{
	if( life <= 0 )
	{
		return true;
	}
	
	return false;
}

void Heart::reset()
{
	life = fill.size() *0xFF;
	harm( 0 );
	flag = false;
}