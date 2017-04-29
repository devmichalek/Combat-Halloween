#include "sound_pad.h"

Sound_pad::Sound_pad()
{
	free();
}

Sound_pad::~Sound_pad()
{
	free();
}

void Sound_pad::free()
{
	music_state = false;
	chunk_state = false;
	
	mus_scratch = false;
	chu_scratch = false;
	
	scratch.free();
	music.free();
	chunk.free();
}



void Sound_pad::setChunk( bool s )
{
	chu_scratch = !s;
}

void Sound_pad::setMusic( bool s )
{
	mus_scratch = !s;
}

void Sound_pad::load( int screen_w, int screen_h )
{
	free();
	
	float scale = 0.48;
	
	scratch.setName( "sound_pad-scratch" );
	scratch.load( "data/platform/panel/sound_pad/scratch.png" );
	scratch.setScale( scale, scale );
	
	music.setName( "sound_pad-music" );
	music.load( "data/platform/panel/sound_pad/music.png" );
	music.setScale( scale, scale );
	music.setPosition( 10, screen_h -music.getHeight() -10 );
	
	chunk.setName( "sound_pad-chunk" );
	chunk.load( "data/platform/panel/sound_pad/chunk.png" );
	chunk.setScale( scale, scale );
	chunk.setPosition( music.getRight() +20, screen_h -chunk.getHeight() -10 );
}

void Sound_pad::draw( sf::RenderWindow* &window )
{
	window->draw( music.get() );
	window->draw( chunk.get() );
	
	if( mus_scratch )
	{
		scratch.setPosition( music.getX(), music.getY() );
		window->draw( scratch.get() );
	}
	
	if( chu_scratch )
	{
		scratch.setPosition( chunk.getX(), chunk.getY() );
		window->draw( scratch.get() );
	}
}

void Sound_pad::handle( sf::Event &event )
{
	if( music.getAlpha() == 0xFF )
	{
		int x, y;
		
		if( event.type == sf::Event::MouseButtonPressed && !focus )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
					
			if( music.checkCollision( x, y ) )
			{
				focus = true;
				music_state = true;
				mus_scratch = !mus_scratch;
				
				if( play )
				{
					click.play();
				}
			}
			
			if( chunk.checkCollision( x, y ) )
			{
				focus = true;
				chunk_state = true;
				chu_scratch = !chu_scratch;
				
				if( play )
				{
					click.play();
				}
			}
		}
		
		if( event.type == sf::Event::MouseButtonReleased )
		{
			focus = false;
		}
	}
}



void Sound_pad::fadein( int i, int max )
{
	music.fadein( i, max );
	chunk.fadein( i, max );
	scratch.fadein( i, max );
}

void Sound_pad::fadeout( int i, int min )
{
	music.fadeout( i, min );
	chunk.fadeout( i, min );
	scratch.fadeout( i, min );
}



bool Sound_pad::musicChanged()
{
	if( music_state )
	{
		music_state = false;
		return true;
	}
	
	return false;
}

bool Sound_pad::chunkChanged()
{
	if( chunk_state )
	{
		chunk_state = false;
		return true;
	}
	
	return false;
}
