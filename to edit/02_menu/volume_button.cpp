/**
    volume_button.h
    Purpose: class Volume_button - to show set volume (music, chunk), to show bar.

    @author Adrian Michalek
    @version 2016.10.21
	@email adrmic98@gmail.com
*/

#include "volume_button.h"


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


	
void Volume_button::load( int left, int y, string new_name )
{
	max = 128;
	
	name.setName( "volume_button-text" );
	name.setFont( "data/fonts/Jaapokki-Regular.otf", 30, 0xFF, 0xFF, 0xFF  );
	name.setText( new_name );
	name.setPosition( left, y );
	
	
	minus.setName( "volume_button-minus" );
	minus.load( "data/sprites/menu/minus.png", 4 );
	minus.setPosition( left +120, y -name.getHeight()/2 );
	minus.setScale( 0.4, 0.4 );
	
	
	plus.setName( "volume_button-plus" );
	plus.load( "data/sprites/menu/plus.png", 4 );
	plus.setPosition( minus.getRight(), y -name.getHeight()/2 );
	plus.setScale( 0.4, 0.4 );
	
	
	percent.setName( "volume_button-percent" );
	percent.setFont( "data/fonts/Jaapokki-Regular.otf", 30, 0xFF, 0xFF, 0xFF  );
	percent.setText( std::to_string( static_cast<int>( volume*100/max ) ) + "%" );
	percent.setPosition( plus.getRight() + 10, y );
	
	
	click.setID( "volume_button-click" );
	click.load( "data/sounds/click.wav", 50 );
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
		percent.setText( std::to_string( static_cast<int>( volume*100/max ) ) + "%" );
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



int Volume_button::getBot()
{
	return plus.getBot();
}

int Volume_button::getRight()
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

