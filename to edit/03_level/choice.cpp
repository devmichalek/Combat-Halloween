/**
    choice.h
    Purpose: class Choice - choose world or random.

    @author Adrian Michalek
    @version 2016.12.13
	@email adrmic98@gmail.com
*/

#include "choice.h"
#include <time.h>
#include <cstdlib>

Choice::Choice()
{
	counter = -1;
	result = -1;
	chosen = -1;
	
	range = 0;
	keep = false;
	
	alpha_line = 0;
	counter_line = 0;
}

Choice::~Choice()
{
	free();
}

void Choice::free()
{
	if( !world.empty() )
	{
		for( auto &it :world )
		{
			it->free();
		}
		
		world.clear();
	}
	
	frame.free();
	button.free();
	
	text.free();
	information.free();

	counter = -1;
	result = -1;
	chosen = -1;
	
	range = 0;
	keep = false;
	
	alpha_line = 0;
	counter_line = 0;
	
	click.free();
}



void Choice::load( int screen_w, int screen_h )
{
	button.setName( "choice-button" );
	button.load( "data/sprites/level/random.png", 4 );
	button.setScale( 0.4, 0.4 );
	
	text.setName( "choice-text" );
	text.setFont( "data/fonts/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	text.setText( "Choose world or " );
	text.setPosition( screen_w/2 -text.getWidth()/2 -button.getWidth(), screen_h/4 - text.getHeight()/2 -80 );
	button.setPosition( text.getRight() +10, text.getY() -5 );
	
	
	information.setName( "choice-information" );
	information.setFont( "data/fonts/Jaapokki-Regular.otf", 20, 0xFF, 0xFF, 0xFF );
	information.setText( "Tip: Following worlds will be generated randomly." );
	information.setPosition( 10, screen_h - information.getHeight() - 10 );
	
	

	for( int i = 0; i < 4; i ++ )
	{
		world.push_back( new MySprite() );
		world[ i ]->setName( "choice-world[ " + to_string( i ) + " ]" );
		world[ i ]->load( "data/sprites/level/" + to_string( i ) + ".png" );
		world[ i ]->setScale( 0.2, 0.2 );
	}
	
	int w = world[ 0 ]->getWidth()*4 + 15*4;
	world[ 0 ]->setPosition( screen_w/2 - w/2, button.getY() +90 );
	world[ 1 ]->setPosition( world[ 0 ]->getRight() + 15, button.getY() +90 );
	world[ 2 ]->setPosition( world[ 1 ]->getRight() + 15, button.getY() +90 );
	world[ 3 ]->setPosition( world[ 2 ]->getRight() + 15, button.getY() +90 );
	

	
	click.setID( "choice-click" );
	click.load( "data/sounds/click.wav", 50 );
	
	frame.setName( "choice-frame" );
	frame.load( "data/sprites/level/frame.png" );
	frame.setScale( 0.2, 0.2 );
	frame.setPosition( -1000, -1000 );
	
	alpha_line = 100;
	counter_line = 150;
}

void Choice::handle( sf::Event &event )
{
	chosen = -1;
	
	if( button.getAlpha() == 0xFF && counter == -1 )
	{
		int x, y;
		button.setOffset( 0 );

		if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
				
			if( button.checkCollision( x, y ) )
			{
				button.setOffset( 1 );
			}
			else
			{
				focus = false;
			}
			
			for( unsigned i = 0; i < world.size(); i++ )
			{
				if( world[ i ]->checkCollision( x, y ) )
				{
					chosen = i;
				}
				else
				{
					frame.setPosition( -1000, -1000 );
				}
			}
		}

		if( event.type == sf::Event::MouseButtonPressed )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
				
			if( button.checkCollision( x, y ) )
			{
				button.setOffset( 2 );
					
				if( play )
				{
					click.play();
				}
				
				
				focus = true;
				counter = 0;
				
			}
			
			for( unsigned i = 0; i < world.size(); i++ )
			{
				if( world[ i ]->checkCollision( x, y ) )
				{
					if( play )
					{
						click.play();
					}
					
					result = i;
				}
			}
		}
			
		if( event.type == sf::Event::MouseButtonReleased )
		{
			focus = false;
		}
		
		if( focus )
		{
			button.setOffset( 2 );
		}
	}
}

void Choice::draw( sf::RenderWindow &window )
{
	for( auto &it :world )
	{
		window.draw( it->get() );
	}
	
	window.draw( button.get() );
	window.draw( text.get() );
	window.draw( information.get() );
	
	
	if( world[ 0 ]->getAlpha() > alpha_line-1 )
	{
		for( unsigned i = 0; i < world.size(); i ++ )
		{
			if( i != static_cast <unsigned> (result) && i != static_cast <unsigned> (chosen) )
			{
				world[ i ]->setAlpha( alpha_line );
			}
			else
			{
				world[ i ]->setAlpha( 0xFF );
				frame.setPosition( world[ i ]->getX(), world[ i ]->getY() );
			}
				
		}
	}
	
	if( counter > -1 && counter < counter_line )
	{
		if( counter %7 == 0 )
		{
			result = rand()%(world.size());
		}
		
		counter ++;
	}
		
	window.draw( frame.get() );
}



void Choice::fadein( int j, int max )
{
	frame.fadein( j, max );
	text.fadein( j, max );
	button.fadein( j, max );
	information.fadein( j, max );
	
	for( auto &it :world )
	{
		it->fadein( j, alpha_line );
	}
}

void Choice::fadeout( int j, int min )
{
	text.fadeout( j, min );
	button.fadeout( j, min );
	information.fadeout( j, min );
	frame.fadeout( j, min );

	if( result != -1 )
	{
		world[ result ]->fadeout( j, min );
	}
	
	

	if( text.getAlpha() < 100 )
	{
		for( auto &it :world )
		{
			it->fadeout( j, min );
		}
	}
}



int Choice::getResult()
{
	return result;
}

sf::Uint8 Choice::getAlpha()
{
	return text.getAlpha();
}

bool Choice::isChosen()
{
	if( ( counter == counter_line || counter == -1 ) && result != -1 )
	{
		return true;
	}
	
	return false;
}



void Choice::reset( int screen_w, int screen_h )
{
	counter = -1;
	result = -1;
	chosen = -1;
	
	text.setPosition( screen_w/2 -text.getWidth()/2 -button.getWidth(), screen_h/4 - text.getHeight()/2 -80 );
	button.setPosition( text.getRight() +10, text.getY() -5 );

	information.setPosition( 10, screen_h - information.getHeight() - 10 );

	int w = world[ 0 ]->getWidth()*4 + 15*4;
	world[ 0 ]->setPosition( screen_w/2 - w/2, button.getY() +90 );
	world[ 1 ]->setPosition( world[ 0 ]->getRight() + 15, button.getY() +90 );
	world[ 2 ]->setPosition( world[ 1 ]->getRight() + 15, button.getY() +90 );
	world[ 3 ]->setPosition( world[ 2 ]->getRight() + 15, button.getY() +90 );
	
	frame.setPosition( -1000, -1000 );
	
	range = 0;
	keep = false;
}

bool Choice::move( int vel, int scope )
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
		button.setPosition( button.getX() +vel, button.getY() );
		text.setPosition( text.getX() +vel, text.getY() );
		information.setPosition( information.getX() +vel, information.getY() );
		frame.setPosition( frame.getX() +vel, frame.getY() );
		
		for( auto &it :world )
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