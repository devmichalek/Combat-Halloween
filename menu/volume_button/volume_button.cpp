/**
    volume_button.h
    Purpose: class Volume_button - to show set volume (music, chunk), to show bar.

    @author Adrian Michalek
    @version 2016.10.21
	@email adrmic98@gmail.com
*/

#include "volume_button.h"
#include "file/file.h"

Volume_button::Volume_button( float volume )
{
	play = true;
	
	max = 0;
	this->volume = volume;
	last_volume = volume;
	
	plus_focus = false;
	minus_focus = false;
}

Volume_button::~Volume_button()
{
	free();
}

void Volume_button::free()
{
	name.free();
	percent.free();
	
	plus.free();
	minus.free();
	
	click.free();
	play = true;
	
	max = 0;
	volume = 0;
	last_volume = 0;
	
	plus_focus = false;
	minus_focus = false;
}


	
void Volume_button::load( unsigned screen_w, float y, string new_name )
{
	max = 128;
	float scale = 0.45;
	
	name.setName( "volume_button-text" );
	name.setFont( "data/initialization/Jaapokki-Regular.otf", 30, 0xFF, 0xFF, 0xFF );
	name.setText( new_name );
	name.setPosition( screen_w /10, y );
	
	minus.setName( "volume_button-minus" );
	minus.load( "data/menu/minus.png", 4 );
	minus.setScale( scale, scale );
	minus.setPosition( name.getX() +100, y -10 );
	
	plus.setName( "volume_button-plus" );
	plus.load( "data/menu/plus.png", 4 );
	plus.setScale( scale, scale );
	plus.setPosition( minus.getRight(), minus.getY() );
	
	percent.setName( "volume_button-percent" );
	percent.setFont( "data/initialization/Jaapokki-Regular.otf", 30, 0xFF, 0xFF, 0xFF );
	percent.setText( con::itos( static_cast<int>( volume*100/max ) ) + "%" );
	percent.setPosition( plus.getRight() +10, y );
	
	click.setID( "volume_button-click" );
	click.load( "data/menu/click.wav", 50 );
}

void Volume_button::draw( sf::RenderWindow* &window )
{
	if( plus_focus )
	{
		if( volume <= max - (max/100) )
		{
			volume += (max/100);
		}
			
		plus.setOffset( 2 );
	}
	else if( minus_focus )
	{
		if( volume >= (max/100) )
		{
			volume -= (max/100);
		}
			
		minus.setOffset( 2 );
	}
	
	
	window->draw( plus.get() );
	window->draw( minus.get() );

	window->draw( name.get() );
	window->draw( percent.get() );
	
	if( last_volume != volume )
	{
		percent.setText( con::itos( static_cast<int>( volume*100/max ) ) + "%" );
		percent.reloadPosition();
	}
}

void Volume_button::handle( sf::Event &event )
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
				
			if( volume <= max - (max/100) )
				volume += max/100;
			
			plus_focus = true;
		}
		else
		{
			plus_focus = false;
		}
			
		if( minus.checkCollision( x, y ) )
		{
			if( play )
				click.play();
				
			if( volume >= max/100 )
				volume -= max/100;
			
			minus_focus = true;
		}
		else
		{
			minus_focus = false;
		}
	}
	
	else if( event.type == sf::Event::MouseButtonReleased )
	{
		plus_focus = false;
		minus_focus = false;
	}
}



void Volume_button::fadein( int i, int max )
{
	name.fadein( i, max );
	percent.fadein( i, max );
	plus.fadein( i, max );
	minus.fadein( i, max );
}

void Volume_button::fadeout( int i, int min )
{
	name.fadeout( i, min );
	percent.fadeout( i, min );
	plus.fadeout( i, min );
	minus.fadeout( i, min );
}



float Volume_button::getBot()
{
	return plus.getBot();
}

float Volume_button::getRight()
{
	return percent.getRight();
}



bool Volume_button::isChanged()
{
	if( last_volume != volume )
	{
		last_volume = volume;
		return true;
	}
	
	return false;
}

sf::Uint8 Volume_button::getVolume()
{
	return volume;
}