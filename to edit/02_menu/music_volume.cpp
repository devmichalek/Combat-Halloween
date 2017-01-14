#include "music_volume.h"
#include <string> 


Music_volume::Music_volume( float volume )
{
	this->volume = volume;
	last_volume = volume;
	play = true;
	
	plus_focus = false;
	minus_focus = false;
}

Music_volume::~Music_volume()
{
	volume = 1;
	last_volume = 1;
	
	plus.free();
	minus.free();

	text.free();
	percent.free();
	click.free();
	
	play = true;
	plus_focus = false;
	minus_focus = false;
}

	
void Music_volume::load( int left, int y, string str )
{
	text.setName( "music_volume-text" );
	text.setFont( "data/fonts/Jaapokki-Regular.otf", 30, 0xFF, 0xFF, 0xFF  );
	text.setText( str );
	text.setPosition( left, y );
	
	
	minus.setName( "music_volume-minus" );
	minus.load( "data/sprites/menu/minus.png", 4 );
	minus.setPosition( left +120, y -text.getHeight()/2 );
	minus.setScale( 0.4, 0.4 );
	
	plus.setName( "music_volume-plus" );
	plus.load( "data/sprites/menu/plus.png", 4 );
	plus.setPosition( minus.getRight(), y -text.getHeight()/2 );
	plus.setScale( 0.4, 0.4 );
	
	
	percent.setName( "music_volume-percent" );
	percent.setFont( "data/fonts/Jaapokki-Regular.otf", 30, 0xFF, 0xFF, 0xFF  );
	percent.setText( std::to_string( static_cast<int>( volume*100/128 ) ) + "%" );
	percent.setPosition( plus.getRight() + 10, y );
	
	click.setID( "music_volume-click" );
	click.load( "data/sounds/click.wav", 50 );
}

void Music_volume::draw( sf::RenderWindow* &window )
{
	if( plus_focus )
	{
		if( volume <= 128 - 1.28 )
			volume += 1.28;
		plus.setOffset( 2 );
	}
	else if( minus_focus )
	{
		if( volume >= 1.28 )
			volume -= 1.28;
		minus.setOffset( 2 );
	}
	
	
	window->draw( plus.get() );
	window->draw( minus.get() );

	window->draw( text.get() );
	window->draw( percent.get() );
	
	if( last_volume != volume )
	{
		last_volume = volume;
		percent.setText( std::to_string( static_cast<int>( volume*100/128 ) ) + "%" );
		percent.reloadPosition();
	}
}

void Music_volume::handle( sf::Event &event )
{
	plus.setOffset( 0 );
	minus.setOffset( 0 );
	int x, y;
	
	if( event.type == sf::Event::MouseMoved )
	{
		x = event.mouseMove.x;
		y = event.mouseMove.y;
		
		if( plus.checkCollision( x, y ) )
		{
			plus.setOffset( 1 );
		}
		else
		{
			plus_focus = false;
		}
		
		if( minus.checkCollision( x, y ) )
		{
			minus.setOffset( 1 );
		}
		else
		{
			minus_focus = false;
		}
	}
	
	else if( event.type == sf::Event::MouseButtonPressed )
	{
		x = event.mouseButton.x;
		y = event.mouseButton.y;
			
		if( plus.checkCollision( x, y ) )
		{
			if( play )
				click.play();
				
			if( volume <= 128 - 1.28 )
				volume += 1.28;
			
			plus_focus = true;
		}
		else
			plus_focus = false;
			
		if( minus.checkCollision( x, y ) )
		{
			if( play )
				click.play();
				
			if( volume >= 1.28 )
				volume -= 1.28;
			
			minus_focus = true;
		}
		else
			minus_focus = false;
	}
	
	else if( event.type == sf::Event::MouseButtonReleased )
	{
		minus_focus = false;
		plus_focus = false;
	}
}

void Music_volume::fadein( int i, int max )
{
	plus.fadein( i, max );
	minus.fadein( i, max );
	text.fadein( i, max );
	percent.fadein( i, max );
}

void Music_volume::fadeout( int i, int min )
{
	plus.fadeout( i, min );
	minus.fadeout( i, min );
	text.fadeout( i, min );
	percent.fadeout( i, min );
}



int Music_volume::getBot()
{
	return plus.getBot();
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

int Music_volume::getRight()
{
	return percent.getRight();
}