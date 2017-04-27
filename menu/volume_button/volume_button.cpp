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
	scale = 0;
	y_state = 0;
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
	scale = 0;
	y_state = 0;
}


	
void Volume_button::load( int y, string new_name )
{
	max = 128;
	scale = 0.4;
	y_state = y;
	
	name.setName( "volume_button-text" );
	name.setFont( "data/initialization/Jaapokki-Regular.otf", 30, 0xFF, 0xFF, 0xFF );
	name.setText( new_name );
	
	minus.setName( "volume_button-minus" );
	minus.load( "data/menu/minus.png", 4 );
	
	plus.setName( "volume_button-plus" );
	plus.load( "data/menu/plus.png", 4 );
	
	
	percent.setName( "volume_button-percent" );
	percent.setFont( "data/initialization/Jaapokki-Regular.otf", 30, 0xFF, 0xFF, 0xFF );
	percent.setText( con::itos( static_cast<int>( volume*100/max ) ) + "%" );
	
	
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

void Volume_button::handle( sf::Event &event, int r_x, int r_y )
{
	plus.setOffset( 0 );
	minus.setOffset( 0 );
	int x, y;
	
	if( event.type == sf::Event::MouseMoved )
	{
		x = event.mouseMove.x;
		y = event.mouseMove.y;
		
		if( plus.checkCollision( x +r_x, y +r_y ) )
		{
			plus.setOffset( 1 );
		}
		else
		{
			plus_focus = false;
		}
		
		if( minus.checkCollision( x +r_x, y +r_y ) )
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
			
		if( plus.checkCollision( x +r_x, y +r_y ) )
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
			
		if( minus.checkCollision( x +r_x, y +r_y ) )
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
	return y_state +plus.getHeight() *scale;
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



void Volume_button::setScale( float s_x, float s_y )
{
	name.setBasicScale( s_x, s_y );
	name.setScale();
	
	minus.setBasicScale( s_x, s_y );
	minus.setScale( scale, scale );
	
	plus.setBasicScale( s_x, s_y );
	plus.setScale( scale, scale );
	
	percent.setBasicScale( s_x, s_y );
	percent.setScale();
}

void Volume_button::setView( int w, int r_x, int r_y )
{
	name.setPosition( w /10 +r_x, y_state *name.getYScale() +r_y );
	minus.setPosition( name.getX() +300 *minus.getXScale(), (y_state -20) *name.getYScale() +r_y );
	plus.setPosition( minus.getRight(), (y_state -20) *name.getYScale() +r_y );
	percent.setPosition( plus.getRight() +10 *percent.getXScale(), y_state *name.getYScale() +r_y );
}