/**
    character.h
    Purpose: class Character - shows 2 animations in level state and allow to choose what of them, then game starts.

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
	
	delay = 0;
	alpha_line = 0;
}

Character::~Character()
{
	free();
}

void Character::free()
{
	if( !sprites.empty() )
	{
		for( auto &it :sprites )
		{
			it->free();
		}
		
		sprites.clear();
	}
	
	text.free();
	information.free();
	
	ready = 0;
	result = -1;
	
	offset = 0;
	how_many = 0;
	
	range = 0;
	keep = false;
	
	delay = 0;
	alpha_line = 0;
	
	click.free();
}

void Character::reset( int screen_w, int screen_h )
{
	sprites[ 0 ]->setPosition( screen_w +screen_w/4 -sprites[ 0 ]->getWidth()/2 -10, screen_h /4 -40 );
	sprites[ 1 ]->setPosition( screen_w +screen_w /2 -sprites[ 1 ]->getWidth()/2, screen_h /4 -40 );
	sprites[ 2 ]->setPosition( screen_w +screen_w/4 *3 -sprites[ 2 ]->getWidth()/2 +10, screen_h /4 -40 );
	
	sprites[ 3 ]->setPosition( screen_w +screen_w/4 -sprites[ 0 ]->getWidth()/2 -10, screen_h /3 *2 -30 );
	sprites[ 4 ]->setPosition( screen_w +screen_w /2 -sprites[ 1 ]->getWidth()/2, screen_h /3 *2 -30 );
	sprites[ 5 ]->setPosition( screen_w +screen_w /4 *3 -sprites[ 5 ]->getWidth()/2 +10, screen_h /3 *2 -30 ); // RUDA <3
	
	text.center( screen_w, 100, screen_w );
	information.setPosition( screen_w + 10, screen_h - information.getHeight() - 10 );
}



void Character::load( int screen_w, int screen_h )
{
	free();
	
	for( unsigned i = 0; i < 6; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ sprites.size() -1 ]->setName( "character-sprite nr" +to_string( i ) );
		sprites[ sprites.size() -1 ]->load( "data/03_level/hero" +to_string( i ) +".png", 10 );
	}
	
	
	click.setID( "character-click" );
	click.load( "data/02_menu/click.wav", 50 );
	
	text.setName( "character-text" );
	text.setFont( "data/00_loading/Jaapokki-Regular.otf", 50, 255, 255, 255 );
	text.setText( "Choose character" );
	
	information.setName( "character-information" );
	information.setFont( "data/00_loading/Jaapokki-Regular.otf", 20, 0xFF, 0xFF, 0xFF );
	information.setText( "Tip: Choose character to start game." );
	
	range = screen_w;
	
	offset = 0;
	how_many = 10;
	
	delay = 8;
	alpha_line = 100;
	
	reset( screen_w, screen_h );
}

void Character::draw( sf::RenderWindow* &window )
{
	for( auto &it :sprites )
	{
		window->draw( it->get() );
	}
	
	offset ++;
	if( offset == how_many *delay )
	{
		offset = 0;
	}
	
	for( auto &it :sprites )
	{
		it->setOffset( offset /delay );
	}
	
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
			
			for( auto &it :sprites )
			{
				if( it->checkCollision( x, y ) )
				{
					it->setAlpha( 0xFF );
				}
				else
				{
					it->setAlpha( alpha_line );
				}
			}
		}
		
		else if( event.type == sf::Event::MouseButtonPressed )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
			
			for( unsigned i = 0; i < sprites.size(); i++ )
			{
				if( sprites[ i ]->checkCollision( x, y ) )
				{
					ready = 2;
					result = i;
					
					if( play )
					{
						click.play();
					}
				}
			}
		}
	}
}



void Character::fadein( int j, int max )
{
	for( auto &it :sprites )
	{
		it->fadein( j, alpha_line );
	}
	
	if( ready == 0 )
	{
		if( sprites[ 0 ]->getAlpha() == alpha_line )
		{
			ready = 1;
		}
	}
	
	text.fadein( j, max );
	information.fadein( j, max );
}

void Character::fadeout( int j, int min )
{
	for( auto &it :sprites )
	{
		it->fadeout( j, min );
	}
	
	text.fadeout( j, min );
	information.fadeout( j, min );
}



int Character::getAlpha()
{
	return sprites[ 0 ]->getAlpha();
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
		
		for( auto &it :sprites )
		{
			it->setPosition( it->getX() +vel, it->getY() );
		}
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