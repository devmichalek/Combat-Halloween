#include "flatness.h"

Flatness::Flatness( string text_one, string text_two, int percent )
{
	this->text_one = text_one;
	this->text_two = text_two;
	
	range = 0;
	blocks = 0;
	keep = false;
	this->percent = percent;
}

Flatness::~Flatness()
{
	free();
}

void Flatness::free()
{
	range = 0;
	blocks = 0;
	keep = false;
	percent = 0;
	
	text.free();
	percent_text.free();
	white_bar.free();
	green_bar.free();
}

void Flatness::reset( unsigned screen_w, unsigned screen_h, int bot )
{
	range = 0;
	green_bar.setScale( white_bar.getWidth() /100 *percent, 1 );
	percent_text.setText( to_string( percent ) + text_two );
	
	text.setPosition( screen_w/2 -text.getWidth()/2, bot +15 );
	white_bar.setPosition( screen_w/2 -white_bar.getWidth()/2, text.getBot() +20 );
	green_bar.setPosition( white_bar.getLeft(), text.getBot() +20 );
	percent_text.setPosition( screen_w/2 -percent_text.getWidth()/2, white_bar.getTop() );
}



void Flatness::load( unsigned screen_w, unsigned screen_h, int bot )
{
	text.setName( "flatness-text" );
	text.setFont( "data/fonts/Jaapokki-Regular.otf", 30, 0xFF, 0xFF, 0xFF );
	text.setText( text_one );
	text.setPosition( screen_w/2 -text.getWidth()/2, bot +15  );
	
	percent_text.setName( "flatness-percent_text" );
	percent_text.setFont( "data/fonts/Jaapokki-Regular.otf", 20, 0x33, 0x66, 0x99 );
	percent_text.setText( to_string( percent ) +text_two );
	
	
	sf::Uint8 bar_width = 25;
	
	white_bar.setName( "flatness-white_bar" );
	white_bar.create( screen_w/4 *3, bar_width );
	white_bar.setPosition( screen_w/2 -white_bar.getWidth()/2, text.getBot() +20 );
	white_bar.setColor( sf::Color( 0xFF, 0xFF, 0xFE ) );
	
	green_bar.setName( "flatness-green_bar" );
	green_bar.create( 1, bar_width );
	green_bar.setPosition( white_bar.getLeft(), text.getBot() +20 );
	green_bar.setColor( sf::Color( 0x66, 0x99, 0x66 ) );
	
	green_bar.setScale( white_bar.getWidth() /100 *percent, 1 );
	
	percent_text.setPosition( screen_w/2 -percent_text.getWidth()/2, white_bar.getTop() );
	
	click.setID( "flatness-click" );
	click.load( "data/sounds/click.wav", 50 );
}

void Flatness::handle( sf::Event &event )
{
	if( text.getAlpha() == 0xFF )
	{
		if( event.type == sf::Event::MouseButtonPressed )
		{
			int x, y;
			
			x = event.mouseButton.x;
			y = event.mouseButton.y;
				
			if( white_bar.checkCollision( x, y ) )
			{
				if( x -white_bar.getX() )
				{
					green_bar.setScale( x -white_bar.getX() );
					
					if( play )
					{
						click.play();
					}
					
					percent = green_bar.getWidth()*100 /white_bar.getWidth();
					percent_text.setText( to_string( percent ) +text_two );
					percent_text.reloadPosition();
				}
			}
		}
	}
}

void Flatness::draw( sf::RenderWindow &window )
{
	window.draw( text.get() );
	window.draw( white_bar.get() );
	window.draw( green_bar.get() );
	window.draw( percent_text.get() );
}



void Flatness::fadein( int j, int max )
{
	text.fadein( j, max );
	percent_text.fadein( j, max );
	white_bar.fadein( j, max );
	green_bar.fadein( j, max );
}

void Flatness::fadeout( int j, int min )
{
	text.fadeout( j, min );
	percent_text.fadeout( j, min );
	white_bar.fadeout( j, min );
	green_bar.fadeout( j, min );
}


int Flatness::getResult()
{
	return percent;
}

bool Flatness::move( int vel, int scope )
{
	if( vel < 0 )
	{
		if( range > scope )
		{
			keep = true;
		}
	}
	else if( vel > 0 )
	{
		if( range < scope )
		{
			keep = true;
		}
	}
	
	if( keep )
	{
		range += vel;
		text.setPosition( text.getX() +vel, text.getY() );
		white_bar.setPosition( white_bar.getX() +vel, white_bar.getY() );
		green_bar.setPosition( green_bar.getX() +vel, green_bar.getY() );
		percent_text.setPosition( percent_text.getX() +vel, percent_text.getY() );
	}
	else
	{
		range = scope;
	}
		
		
	if( range == scope )
	{
		return true;
	}
		
	return false;
}

int Flatness::getBot()
{
	return white_bar.getBot();
}