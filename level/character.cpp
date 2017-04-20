/**
    character.h
    Purpose: class Character - shows 2 animations in level state and allow to choose what of them, then game starts.

    @author Adrian Michalek
    @version 2016.12.06
	@email adrmic98@gmail.com
*/

#include "character.h"
#include "file/file.h"

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
	tick.free();
	cross.free();
	if( !unlocked.empty() )
	{
		unlocked.clear();
	}
	
	if( !sprites.empty() )
	{
		for( auto &it :sprites )
		{
			it->free();
		}
		
		sprites.clear();
	}
	
	if( !texts.empty() )
	{
		for( auto &it :texts )
		{
			it->free();
		}
		
		texts.clear();
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
	int w = 110;
	int distance = ((sprites[ 0 ]->getWidth()*3) +(w*2)) /2;
	int distance2 = ((sprites[ sprites.size() -1 ]->getWidth()*3) +(w*2)) /2;
	
	sprites[ 0 ]->setPosition( screen_w +screen_w /2 -distance, screen_h /5 -25 );
	sprites[ 1 ]->setPosition( sprites[ 0 ]->getRight() +w, screen_h /5 -25 );
	sprites[ 2 ]->setPosition( sprites[ 1 ]->getRight() +w, screen_h /5 -25 );
	
	sprites[ 3 ]->setPosition( screen_w +screen_w /2 -distance2, screen_h /2 +30 );
	sprites[ 4 ]->setPosition( sprites[ 3 ]->getRight() +w, screen_h /2 +30 );
	sprites[ 5 ]->setPosition( sprites[ 4 ]->getRight() +w, screen_h /2 +30 ); // RUDA <3
	
	texts[ 0 ]->setPosition( sprites[ 0 ]->getX() -5, sprites[ 0 ]->getBot() +5 );
	texts[ 1 ]->setPosition( sprites[ 1 ]->getX() +13, sprites[ 1 ]->getBot() +5 );
	texts[ 2 ]->setPosition( sprites[ 2 ]->getX() +4, sprites[ 2 ]->getBot() +5 );
	texts[ 3 ]->setPosition( sprites[ 3 ]->getX() +55, sprites[ 3 ]->getBot() +5 );
	texts[ 4 ]->setPosition( sprites[ 4 ]->getX() +35, sprites[ 4 ]->getBot() +5 );
	texts[ 5 ]->setPosition( sprites[ 5 ]->getX() +20, sprites[ 5 ]->getBot() +5 );
	
	text.center( screen_w, 90, screen_w );
	information.setPosition( screen_w + 10, screen_h - information.getHeight() - 10 );
}



void Character::load( int screen_w, int screen_h )
{
	free();
	
	for( unsigned i = 0; i < 6; i++ )
	{
		sprites.push_back( new MySprite() );
		sprites[ sprites.size() -1 ]->setName( "character-sprite nr" +con::itos( i ) );
		sprites[ sprites.size() -1 ]->load( "data/level/hero" +con::itos( i ) +".png", 10 );
		
		texts.push_back( new MyText() );
		texts[ texts.size() -1 ]->setName( "character-texts nr" +con::itos( i ) );
		texts[ texts.size() -1 ]->setFont( "data/initialization/Jaapokki-Regular.otf", 30, 255, 255, 255 );
	}
	
	texts[ 0 ]->setText( "adventure" );
	texts[ 1 ]->setText( "military" );
	texts[ 2 ]->setText( "phantom" );
	texts[ 3 ]->setText( "girl" );
	texts[ 4 ]->setText( "gorgeous" );
	texts[ 5 ]->setText( "powerful" );
	
	
	click.setID( "character-click" );
	click.load( "data/menu/click.wav", 50 );
	
	text.setName( "character-text" );
	text.setFont( "data/initialization/Jaapokki-Regular.otf", 50, 255, 255, 255 );
	text.setText( "Choose character" );
	
	information.setName( "character-information" );
	information.setFont( "data/initialization/Jaapokki-Regular.otf", 20, 0xFF, 0xFF, 0xFF );
	information.setText( "Tip: Choose character to start game." );
	
	range = screen_w;
	
	offset = 0;
	how_many = 10;
	
	delay = 8;
	alpha_line = 100;
	
	tick.setName( "choice-tick" );
	tick.load( "data/level/tick.png" );
	
	cross.setName( "choice-cross" );
	cross.load( "data/level/x.png" );
	
	// load unlocked worlds
	MyFile file;
	file.load( "data/txt/character/character_temporary.txt" );
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
	
	reset( screen_w, screen_h );
}

void Character::draw( sf::RenderWindow* &window )
{
	for( unsigned i = 0; i < sprites.size(); i++ )
	{
		if( unlocked[ i ] )
		{
			tick.setAlpha( sprites[ i ]->getAlpha() );
			tick.setPosition( texts[ i ]->getX() -tick.getWidth() -10, sprites[ i ]->getBot() +5 );
			window->draw( tick.get() );
		}
		else
		{
			cross.setPosition( texts[ i ]->getX() -cross.getWidth() -10, sprites[ i ]->getBot() +5 );
			window->draw( cross.get() );
		}
		
		window->draw( sprites[ i ]->get() );
	}
	
	for( auto &it :texts )
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
			
			for( unsigned i = 0; i < sprites.size(); i++ )
			{
				if( sprites[ i ]->checkCollision( x, y ) && unlocked[ i ] )
				{
					texts[ i ]->setAlpha( 0xFF );
					sprites[ i ]->setAlpha( 0xFF );
				}
				else
				{
					texts[ i ]->setAlpha( alpha_line );
					sprites[ i ]->setAlpha( alpha_line );
				}
			}
		}
		
		else if( event.type == sf::Event::MouseButtonPressed )
		{
			x = event.mouseButton.x;
			y = event.mouseButton.y;
			
			for( unsigned i = 0; i < sprites.size(); i++ )
			{
				if( sprites[ i ]->checkCollision( x, y ) && unlocked[ i ] )
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
	tick.fadein( j, alpha_line );
	cross.fadein( j, alpha_line );
	
	for( auto &it :sprites )
	{
		it->fadein( j, alpha_line );
	}
	
	for( auto &it :texts )
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
	tick.fadeout( j, min );
	cross.fadeout( j, min );
	
	for( auto &it :sprites )
	{
		it->fadeout( j, min );
	}
	
	for( auto &it :texts )
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
		
		for( auto &it :texts )
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