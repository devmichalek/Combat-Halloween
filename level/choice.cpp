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
#include "file/file.h"

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
	tick.free();
	cross.free();
	if( !unlocked.empty() )
	{
		unlocked.clear();
	}
	
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
	if( !description.empty() )
	{
		for( auto &it :description )
		{
			it->free();
		}
		
		description.clear();
	}

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
	button.load( "data/level/random.png", 4 );
	button.setScale( 0.4, 0.4 );
	
	text.setName( "choice-text" );
	text.setFont( "data/initialization/Jaapokki-Regular.otf", 40, 0xFF, 0xFF, 0xFF );
	text.setText( "Choose world or " );
	
	
	information.setName( "choice-information" );
	information.setFont( "data/initialization/Jaapokki-Regular.otf", 20, 0xFF, 0xFF, 0xFF );
	information.setText( "Tip: Following worlds will be generated randomly." );

	for( int i = 0; i < 5; i ++ )
	{
		world.push_back( new MySprite() );
		world[ i ]->setName( "choice-world[ " + con::itos( i ) + " ]" );
		world[ i ]->load( "data/platform/world/" + con::itos( i ) + "/bg.png" );
		world[ i ]->setScale( 0.1, 0.1 );
		
		description.push_back( new MyText() );
		description[ i ]->setName( "choice-description" );
		description[ i ]->setFont( "data/initialization/Jaapokki-Regular.otf", 20, 0xFF, 0xFF, 0xFF );
	}
	
	// set text
	description[ 0 ]->setText( "The last stand" );
	description[ 1 ]->setText( "As nature goes" );
	description[ 2 ]->setText( "Winter's Embrace" );
	description[ 3 ]->setText( "Zany Gorge Race" );
	description[ 4 ]->setText( "Lost in Cyberspace" );
	

	
	click.setID( "choice-click" );
	click.load( "data/menu/click.wav", 50 );
	
	frame.setName( "choice-frame" );
	frame.load( "data/level/frame.png" );
	frame.setScale( 0.2, 0.2 );
	
	alpha_line = 100;
	counter_line = 150;
	
	tick.setName( "choice-tick" );
	tick.load( "data/level/tick.png" );
	
	cross.setName( "choice-cross" );
	cross.load( "data/level/x.png" );
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
				if( world[ i ]->checkCollision( x, y ) && unlocked[ i ] )
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
				if( world[ i ]->checkCollision( x, y ) && unlocked[ i ] )
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
	for( unsigned i = 0; i < world.size(); i++ )
	{
		if( unlocked[ i ] )
		{
			tick.setAlpha( world[ i ]->getAlpha() );
			tick.setPosition( world[ i ]->getX() -tick.getWidth()/2 +world[ i ]->getWidth()/2, world[ i ]->getBot() +5 );
			window.draw( tick.get() );
		}
		else
		{
			cross.setAlpha( world[ i ]->getAlpha() );
			cross.setPosition( world[ i ]->getX() -cross.getWidth()/2 +world[ i ]->getWidth()/2, world[ i ]->getBot() +5 );
			window.draw( cross.get() );
		}
		
		window.draw( world[ i ]->get() );
	}
	
	for( auto &it :description )
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
			while( !unlocked[ result ] )
			{
				result = rand()%(world.size());
			}
		}
		
		counter ++;
	}
		
	window.draw( frame.get() );
}



void Choice::fadein( int j, int max )
{
	tick.fadein( j, alpha_line );
	cross.fadein( j, alpha_line );
	frame.fadein( j, max );
	text.fadein( j, max );
	button.fadein( j, max );
	information.fadein( j, max );
	
	for( auto &it :world )
	{
		it->fadein( j, alpha_line );
	}
	
	for( auto &it :description )
	{
		it->fadein( j, max );
	}
}

void Choice::fadeout( int j, int min )
{
	tick.fadeout( j, min );
	cross.fadeout( j, min );
	text.fadeout( j, min );
	button.fadeout( j, min );
	information.fadeout( j, min );
	frame.fadeout( j, min );
	
	for( auto &it :description )
	{
		it->fadeout( j, min );
	}

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

int Choice::getLeft()
{
	return world[ 0 ]->getX();
}

int Choice::getBot()
{
	return world[ world.size() -1 ]->getBot();
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
	if( !unlocked.empty() )
	{
		unlocked.clear();
	}
	
	// load unlocked worlds
	MyFile file;
	file.load( "data/txt/world/world_temporary.txt" );
	if( file.is_good() )
	{
		string line;
		while( file.get() >> line )
		{
			// printf( "%d\n", con::stoi( line ) );
			unlocked.push_back( static_cast <bool> (con::stoi( line )) );
		}
	}
	file.free();
	
	counter = -1;
	result = -1;
	chosen = -1;
	
	text.setPosition( screen_w/2 -text.getWidth()/2, screen_h/4 - text.getHeight()/2 -80 );
	button.setPosition( text.getRight() +10, text.getY() -5 );

	information.setPosition( 10, screen_h - information.getHeight() - 10 );

	int w = world[ 0 ]->getWidth()*world.size() + 35*world.size();
	world[ 0 ]->setPosition( screen_w/2 - w/2 +7, button.getY() +115 );
	for( unsigned i = 1; i < world.size(); i++ )
	{
		world[ i ]->setPosition( world[ i -1 ]->getRight() + 40, button.getY() +115 );
	}
	
	int y = world[ 0 ]->getY() -description[ 0 ]->getHeight() -10;
	
	for( unsigned i = 0; i < world.size(); i++ )
	{
		description[ i ]->setPosition( world[ i ]->getX() +world[ i ]->getWidth()/2 -description[ i ]->getWidth()/2, y );
	}
	
	frame.setPosition( -screen_w, -screen_w );
	
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
		
		for( auto &it :description )
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