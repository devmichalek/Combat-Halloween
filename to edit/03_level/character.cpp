/**
    character.h
    Purpose: class Character - shows 2 animations in level state.

    @author Adrian Michalek
    @version 2016.12.06
	@email adrmic98@gmail.com
*/

#include "character.h"

Character::Character()
{
	ready = 0;
	result = -1;
	
	offset = 0;
	how_many = 0;
	
	range = 0;
	keep = false;
}

Character::~Character()
{
	free();
}

void Character::free()
{
	one.free();
	two.free();
	text.free();
	information.free();
	
	ready = 0;
	result = -1;
	
	offset = 0;
	how_many = 0;
	
	range = 0;
	keep = false;
	
	click.free();
}

void Character::reset( int screen_w, int screen_h )
{
	one.center( screen_w, 100, screen_w/2, screen_h );
	two.center( screen_w + screen_w/2, 100, screen_w/2, screen_h ); // RUDA <3
	text.center( screen_w, screen_h/2 -40, screen_w );
	information.setPosition( screen_w + 10, screen_h - information.getHeight() - 10 );
}



void Character::load( int screen_w, int screen_h )
{
	one.setName( "character-one" );
	one.load( "data/sprites/hero/0/choose/0.png", 10 );
	one.center( screen_w, 100, screen_w/2, screen_h );
	
	two.setName( "character-two" );
	two.load( "data/sprites/hero/1/choose/0.png", 10 );
	two.setScale( 0.93, 0.93 );
	two.center( screen_w + screen_w/2, 100, screen_w/2, screen_h ); //RUDA <3
	
	click.setID( "music_button-click" );
	click.load( "data/sounds/click.wav", 50 );
	
	text.setName( "character-text" );
	text.setFont( "data/fonts/Jaapokki-Regular.otf", 50, 255, 255, 255 );
	text.setText( "Choose character" );
	text.center( screen_w, screen_h/2 -40, screen_w );
	
	information.setName( "choice-information" );
	information.setFont( "data/fonts/Jaapokki-Regular.otf", 20, 0xFF, 0xFF, 0xFF );
	information.setText( "Tip: Choose character to start game." );
	information.setPosition( screen_w + 10, screen_h - information.getHeight() - 10 );
	
	range = screen_w;
	
	offset = 0;
	how_many = 10;
}

void Character::draw( sf::RenderWindow* &window )
{
	window->draw( one.get() );
	window->draw( two.get() );
	
	offset ++;
	if( offset == how_many *6 )
	{
		offset = 0;
	}
	
	
	one.setOffset( offset /6 );
	two.setOffset( offset /6 );
	
	window->draw( text.get() );
	window->draw( information.get() );
}

void Character::handle( sf::Event &event )
{
	int x = -1, y = -1;
	
	if( ready == 1 )
	{
		if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
			
			if( one.checkCollision( x, y ) )
			{
				one.setAlpha( 0xFF );
			}
			else
			{
				one.setAlpha( 100 );
			}
			
			if( two.checkCollision( x, y ) )
			{
				two.setAlpha( 0xFF );
			}
			else
			{
				two.setAlpha( 100 );
			}
		}
		
		else if( event.type == sf::Event::MouseButtonPressed )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
			
			if( one.checkCollision( x, y ) )
			{
				ready = 2;
				result = 0;
				
				if( play )
				{
					click.play();
				}
			}
			else if( two.checkCollision( x, y ) )
			{
				ready = 2;
				result = 1;
				
				if( play )
				{
					click.play();
				}
			}
		}
	}
}



void Character::fadein( int j, int max )
{
	int value = 100;
	one.fadein( j, value );
	two.fadein( j, value );
	
	if( ready == 0 )
	{
		if( one.getAlpha() == value )
		{
			ready = 1;
		}
	}
	
	text.fadein( j, max );
	information.fadein( j, max );
}

void Character::fadeout( int j, int min )
{
	one.fadeout( j, min );
	two.fadeout( j, min );
	
	text.fadeout( j, min );
	information.fadeout( j, min );
}



int Character::getAlpha()
{
	return one.getAlpha();
}

bool Character::move( int vel, int scope )
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
		information.setPosition( information.getX() +vel, information.getY() );
		one.setPosition( one.getX() +vel, one.getY() );
		two.setPosition( two.getX() +vel, two.getY() );
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

bool Character::nextState()
{
	if( ready == 2 )
	{
		return true;
	}
	
	return false;
}
	
int Character::getResult()
{
	if( result != -1 )
	{
		int save = result;
		
		result = -1;
		ready = 0;
		return save;
	}
	
	return -1;
}