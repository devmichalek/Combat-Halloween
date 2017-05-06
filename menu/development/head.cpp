/**
    head.h
    Purpose: class Head - it's a part of head group (headdeck), represents 1 particular hero who can be buy

    @author Adrian Michalek
    @version 2017.04.07
	@email adrmic98@gmail.com
*/

#include "menu/development/head.h"
#include "file/file.h"
#include <vector>

Head::Head()
{
	free();
}

Head::~Head()
{
	free();
}

void Head::free()
{
	cost = 0;
	type = 0;
	kind = 0;
	state = 0;
	locked = true;
	
	click.free();
	sprite.free();
	button.free();
	name.free();
	specs.free();
	cost_text.free();
}



void Head::load( int type, unsigned screen_w, float y )
{
	free();
	
	// Set type.
	this->type = type;
	
	// Set kind.
	this->kind = type;
	if( type < 2 )	this->kind ++;
	else			this->kind += 2;

	
	// Load click.
	click.setID( "develop-click" );
	click.load( "data/menu/click.wav", 50 );
	
	// Set cost (text)
	cost_text.setFont( "data/initialization/Jaapokki-Regular.otf", 25, 0xFF, 0xD8, 0x00 );
	cost_text.setText( " " );
	cost_text.setPosition( screen_w /1.15, y +38 );
	
	// load head
	sprite.setName( "head-sprite" );
	sprite.load( "data/menu/head/" +con::itos( type ) +".png" );
	sprite.setScale( 0.7, 0.7 );
	sprite.setPosition( 20, y );
	
	// load button
	button.setName( "head-button" );
	button.load( "data/menu/upgrade.png", 4 );
	button.setScale( 0.42, 0.42 );
	button.setPosition( screen_w /1.282, y +20 );
	
	// load name
	MyFile file;
	file.load( "data/txt/character/character_name.txt" );
	if( file.is_good() )
	{
		int c = kind;
		
		string line;
		while( file.get() >> line )
		{
			if( c == 0 )
			{
				name.setFont( "data/initialization/Jaapokki-Regular.otf", 25, 0xFF, 0xFF, 0xFF );
				name.setText( line );
				name.setPosition( screen_w /6.9, y +38 );
				break;
			}
			
			c--;
		}
	}
	file.free();
	
	// load specs
	file.load( "data/txt/character/character_specs.txt" );
	if( file.is_good() )
	{
		int c = type;
		string line;
		while( getline( file.get(), line ) )
		{
			if( c == 0 )
			{
				specs.setFont( "data/initialization/Jaapokki-Regular.otf", 25, 0xFF, 0xFF, 0xFF );
				specs.setText( line );
				specs.setPosition( screen_w /2.78, y +38 );
				break;
			}
			
			c--;
		}
	}
	file.free();
}

void Head::draw( sf::RenderWindow* &window )
{
	if( state == 0 )
	{
		window->draw( button.get() );
	}
	
	window->draw( sprite.get() );
	window->draw( name.get() );
	window->draw( specs.get() );
	window->draw( cost_text.get() );
}

void Head::handle( sf::Event &event )
{
	if( !locked && state == 0 )
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
				state = 1;
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



void Head::fadein( int i, int max )
{
	sprite.fadein( i, max );
	button.fadein( i, max );
	name.fadein( i, max );
	specs.fadein( i, max );
	cost_text.fadein( i, max );
}

void Head::fadeout( int i, int min )
{
	sprite.fadeout( i, min );
	button.fadeout( i, min );
	name.fadeout( i, min );
	specs.fadeout( i, min );
	cost_text.fadeout( i, min );
}



void Head::reloadText()
{
	// set cost
	MyFile file;
	file.load( "data/txt/character/character_costs.txt" );
	if( file.is_good() )
	{
		int c = type;
		string line;
		while( file.get() >> line )
		{
			if( c == 0 )
			{
				cost_text.setText( line );
				cost_text.setPosition( button.getRight() +20, name.getY() );
				cost_text.setColor( 0xFF, 0xD8, 0x00 );
				cost = con::stoi( line );
				break;
			}
			
			c--;
		}
	}
	file.free();
	
	locked = true;
	state = 0;
	
	file.load( "data/txt/character/character_temporary.txt" );
	if( file.is_good() )
	{
		int c = kind;
		
		string line;
		while( file.get() >> line )
		{
			if( c == 0 )
			{
				if( con::stoi( line ) == 1 )
				{
					cost = 0;
					state = 1;
					cost_text.setText( "Already owned" );
					cost_text.setPosition( specs.getRight(), cost_text.getY() );
					cost_text.setColor( 0xFF, 0xFF, 0xFF );
					// printf( "happen\n" );
				}
			}
			
			c--;
		}
	}
	file.free();
}

int Head::getCost()
{
	return cost;
}

void Head::lock()
{
	locked = true;
	button.setOffset( 3 );
}

void Head::unlock()
{
	locked = false;
}

bool Head::sellOut()
{
	if( state > 0 )
	{
		return true;
	}
	
	return false;
}

void Head::makeNought()
{
	cost = 0;
	cost_text.setText( "Already owned" );
	cost_text.setPosition( button.getX() -10, cost_text.getY() );
	cost_text.setColor( 0xFF, 0xFF, 0xFF );
	
	vector <string> a;
	
	MyFile file;
	file.load( "data/txt/character/character_temporary.txt" );
	if( file.is_good() )
	{
		string line;
		while( file.get() >> line )
		{
			a.push_back( line );
		}
		
		a[ kind ] = "1";
	}
	file.free();
	
	file.load( "data/txt/character/character_temporary.txt", std::ios::out );
	if( file.is_good() )
	{
		for( auto &it :a )
		{
			file.get() << it << "\n";
		}
	}
	file.free();
	a.clear();
}