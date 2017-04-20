/**
    heart.h
    Purpose: class Heart responsible for drawing hearts, heart mechanis etc.

    @author Adrian Michalek
    @version 2017.03.06
	@email adrmic98@gmail.com
*/

#include "heart.h"
#include "file/file.h"


Heart::Heart()
{
	free();
}

Heart::~Heart()
{
	free();
}

void Heart::free()
{
	max = 0;
	life = 0;
	fadedout = false;
	
	if( !fill_bits.empty() )
	{
		for( auto &it :fill_bits )
		{
			it->free();
		}
		
		fill_bits.clear();
	}
	
	if( !grey_bits.empty() )
	{
		for( auto &it :grey_bits )
		{
			it->free();
		}
		
		grey_bits.clear();
	}
	
	if( !frame_bits.empty() )
	{
		for( auto &it :frame_bits )
		{
			it->free();
		}
		
		frame_bits.clear();
	}
	
	fill.free();
	grey.free();
	frame.free();
}

void Heart::reset()
{
	fadedout = false;
	life = fill_bits.size() *0xFF;
	harm( 0 );
}



void Heart::load()
{
	free();
	
	MyFile file;
	
	// Set max variable.
	file.load( "data/txt/heart/heart.txt" );
	if( file.is_good() )
	{
		string line;
		file.get() >> line;
		max = con::stoi( line );
	}
	file.free();
	
	
	// Set actual amount of hearts.
	file.load( "data/txt/heart/heart_current.txt" );
	if( file.is_good() )
	{
		string line;
		file.get() >> line;
		int nr = con::stoi( line );
		
		fill.setName( "heart-fill" );
		fill.load( "data/platform/panel/heart/fill.png");
		
		frame.setName( "heart-frame" );
		frame.load( "data/platform/panel/heart/frame.png");
		
		grey.setName( "heart-grey_square" );
		grey.load( "data/platform/panel/grey/grey_square.png");
		
		for( int i = 0; i < nr; i++ )
		{
			fill_bits.push_back( new Heart_bit() );
			fill_bits[ fill_bits.size() -1 ]->alpha = 0xFF;
			fill_bits[ fill_bits.size() -1 ]->x = 10 + (fill.getWidth() +10) *i;
			fill_bits[ fill_bits.size() -1 ]->y = 10;
			
			frame_bits.push_back( new Heart_bit() );
			frame_bits[ frame_bits.size() -1 ]->x = 10 + (frame.getWidth() +10) *i;
			frame_bits[ frame_bits.size() -1 ]->y = 10;
		}
		
		for( int i = 0; i < max; i++ )
		{
			grey_bits.push_back( new Heart_bit() );
			grey_bits[ grey_bits.size() -1 ]->x = 5 + (frame.getWidth() +10) *i;
			grey_bits[ grey_bits.size() -1 ]->y = 5;
		}
	}
	file.free();

	reset();
}

void Heart::draw( sf::RenderWindow* &window )
{
	for( auto &it :grey_bits )
	{
		grey.setPosition( it->x, it->y );
		window->draw( grey.get() );
	}
	
	for( auto &it :fill_bits )
	{
		fill.setPosition( it->x, it->y );
		fill.setAlpha( it->alpha );
		window->draw( fill.get() );
	}
	
	for( auto &it :frame_bits )
	{
		frame.setPosition( it->x, it->y );
		window->draw( frame.get() );
	}
	
	// Delete later.
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( 0 ) ) )
	{
		harm( -4 );
	}
	
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( 1 ) ) )
	{
		harm( 4 );
	}
	
	// printf( "%d\n", life );
}



void Heart::fadein( int v, int max )
{
	grey.fadein( v, max /2 );
	frame.fadein( v, max /2 );
}

void Heart::fadeout( int v, int min )
{
	for( auto &it :fill_bits )
	{
		if( it->alpha > min )
		{
			it->alpha -= v;
			if( it->alpha < min )
				it->alpha = min;
		}
	}
	
	fill.fadeout( v, min );
	grey.fadeout( v, min );
	frame.fadeout( v, min );
}



void Heart::harm( int damage )
{
	life += damage;
	if( life > static_cast <int> (fill_bits.size() *0xFF) )
	{
		// printf( "%d\n", life );
		life = fill_bits.size() *0xFF;
	}
	
	int temporary_life = 0;
	for( auto &it :fill_bits )
	{
		temporary_life += it->alpha;
	}
	
	if( temporary_life != life )
	{
		temporary_life = life;
		
		for( auto &it :fill_bits )
		{
			it->alpha = 0;
		}
		
		if( temporary_life > 0 )
		{
			for( auto &it :fill_bits )
			{
				if( temporary_life < 0xFF )
				{
					it->alpha = temporary_life;
					break;
				}
				else
				{
					it->alpha = 0xFF;
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