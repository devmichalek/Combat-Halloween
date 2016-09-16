#include "music_volume.h"
#include <string> 


Music_volume::Music_volume( int volume )
{
	this->volume = volume;
	last_volume = volume;
	play = true;
}

Music_volume::~Music_volume()
{
	volume = 1;
	last_volume = 1;
	
	green_bar.free();
	white_bar.free();

	text.free();
	percent.free();
	click.free();
	play = true;
}

	
void Music_volume::load( int screen_w, int y, string str )
{
	text.setID( "music_volume-text" );
	text.setFont( "intro/Jaapokki-Regular.otf", 30, 0xFF, 0xFF, 0xFF  );
	text.setText( str );
	text.setPosition( 20, y );
	
	white_bar.setName( "music_volume-white_bar" );
	white_bar.create( 128*3, 40, sf::Color( 0xFF, 0xFF, 0xFF, 0x00 ) );
	white_bar.setPosition( 150, y );
	
	green_bar.setName( "music_volume-green_bar" );
	green_bar.create( 1, 40, sf::Color( 0x70, 0xB7, 0x59 ) );
	green_bar.setPosition( 150, y ); // screen_h/2 - green_bar.getHeight()/2
	green_bar.setScale( volume * 3 );
	
	percent.setID( "music_volume-percent" );
	percent.setFont( "intro/Jaapokki-Regular.otf", 30, 0xFF, 0xFF, 0xFF  );
	percent.setText( std::to_string( volume*100/128 ) + "%" );
	percent.setPosition( white_bar.getRight() + 10, y );
	
	click.setID( "music_volume-click" );
	click.load( "menu/click.wav", 50 );
}

void Music_volume::draw( sf::RenderWindow* &window )
{
	window->draw( white_bar.get() );
	window->draw( green_bar.get() );
	window->draw( text.get() );
	window->draw( percent.get() );
	
	if( last_volume != volume )
	{
		last_volume = volume;
		green_bar.setScale( volume * 3 );
		percent.setText( std::to_string( volume*100/128 ) + "%" );
		percent.reloadPosition();
	}
}

void Music_volume::handle( sf::Event &event )
{
	if( event.type == sf::Event::MouseButtonPressed )
	{
		int x = event.mouseButton.x;
		int y = event.mouseButton.y;
			
		if( white_bar.checkCollision( x, y ) )
		{
			volume = ( x - white_bar.getX() ) / 3;
			if( play )
				click.play();
		}
	}
}

void Music_volume::fadein( int i, int max )
{
	white_bar.fadein( i, max );
	green_bar.fadein( i, max );
	text.fadein( i, max );
	percent.fadein( i, max );
}

void Music_volume::fadeout( int i, int min )
{
	white_bar.fadeout( i, min );
	green_bar.fadeout( i, min );
	text.fadeout( i, min );
	percent.fadeout( i, min );
}



int Music_volume::getBot()
{
	return white_bar.getBot();
}

void Music_volume::turn()
{
	play = !play;
}

void Music_volume::setVolume( sf::Uint8 volume )
{
	click.setVolume( volume );
}



bool Music_volume::changeVolume()
{
	if( last_volume != volume )
	{
		return true;
	}
	
	return false;
}

sf::Uint8 Music_volume::getVolume()
{
	return volume;
}
