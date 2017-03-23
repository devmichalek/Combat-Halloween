/**
    develop.h
    Purpose: class Develop - for one special skill in menu state.

    @author Adrian Michalek
    @version 2017.02.02
	@email adrmic98@gmail.com
*/

#include "02_menu/development/develop.h"
#include <fstream>

Develop::Develop()
{
	free();
}

Develop::~Develop()
{
	free();
}

void Develop::free()
{
	button.free();
	sprite.free();
	label.free();
	actual.free();
	
	name.free();
	name_base.free();
	cost_text.free();
	
	max = 0;
	cost = 0;
	level = 0;
	locked = true;
}



void Develop::load( int main_x, int nr, int bot )
{
	free();
	
	// Load button.
	button.setName( "develop-button" );
	button.load( "data/02_menu/upgrade.png", 4 );
	
	fstream file;
	
	// Set name.
	string path = "data/txt/skill/skill_name.txt";
	file.open( path );
	if( file.bad() )
	{
		printf( "Cannot load %s\n", path.c_str() );
	}
	else
	{
		string line;
		int counter = nr;
		while( getline( file, line ) )
		{
			if( counter == 0 )
			{
				
				name.setName( "develop-name" );
				name.setFont( "data/00_loading/Jaapokki-Regular.otf", 30, 255, 255, 255 );
				name.setText( line );
				break;
			}
			
			counter --;
		}
	}
	file.close();
	
	// Load sprite.
	sprite.setName( "develop-sprite" );
	sprite.load( "data/02_menu/skill/" +to_string( nr ) +".png" );
	
	// Set name_base.
	path = "data/txt/skill/skill_namebase.txt";
	file.open( path );
	if( file.bad() )
	{
		printf( "Cannot load %s\n", path.c_str() );
	}
	else
	{
		string line;
		int counter = nr;
		while( file >> line )
		{
			if( counter == 0 )
			{
				// set name
				name_base.setName( "develop-name" );
				name_base.setFont( "data/00_loading/Jaapokki-Regular.otf", 30, 255, 255, 255 );
				name_base.setText( line );
				break;
			}
			
			counter --;
		}
	}
	file.close();
	
	// Set actual.
	actual.setName( "develop-actual" );
	actual.setFont( "data/00_loading/Jaapokki-Regular.otf", 30, 255, 255, 255 );
	actual.setText( " " );
	
	// Set label.
	label.setName( "develop-label" );
	label.setFont( "data/00_loading/Jaapokki-Regular.otf", 30, 255, 255, 255 );
	label.setText( " " );
	
	// Set max.
	path = "data/txt/skill/skill_max.txt";
	file.open( path );
	if( file.bad() )
	{
		printf( "Cannot load %s\n", path.c_str() );
	}
	else
	{
		string line;
		int counter = nr;
		while( file >> line )
		{
			if( counter == 0 )
			{
				max = stoi( line );
				break;
			}
			
			counter --;
		}
	}
	file.close();
	
	
	// Cost_text settings.
	cost_text.setName( "develop-cost_text" );
	cost_text.setFont( "data/00_loading/Jaapokki-Regular.otf", 30, 255, 255, 255 );
	cost_text.setText( " " );
	cost_text.setColor( 0xFF, 0xD8, 0x00 );
	
	// Load click.
	click.setID( "develop-click" );
	click.load( "data/02_menu/click.wav", 50 );
	
	// Positions.
	name.setPosition( main_x, bot );
	sprite.setScale( 0.5, 0.5 );
	sprite.setPosition( main_x -sprite.getWidth() -10, bot -10 );
	label.setPosition( main_x +230, bot );
	actual.setPosition( label.getRight() +100, bot );
	name_base.setPosition( actual.getRight() +90, bot );
	
	button.setOffset( 3 );
	button.setScale( 0.8, 0.8 );
	button.setPosition( label.getRight() +430, bot -10 );
	cost_text.setPosition( label.getRight() +530, bot );
}

void Develop::draw( sf::RenderWindow* &window )
{
	window->draw( button.get() );
	window->draw( sprite.get() );
	window->draw( label.get() );
	window->draw( actual.get() );
	window->draw( name.get() );
	window->draw( name_base.get() );
	window->draw( cost_text.get() );
}

void Develop::handle( sf::Event &event )
{
	if( !locked && level < max )
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
				level ++;
				if( this->level == max )
				{
					this->label.setText( "max" );
					this->label.setColor( 0xFF, 0xD8, 0x00 );
				}
				else
				{
					this->label.setText( to_string( level ) );
					
					if( level == 0 )	this->label.setColor( 0xE8, 0x68, 0x50 );
					else				this->label.setColor( 0x58, 0x70, 0x58 );
				}

				label.reloadPosition();
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



void Develop::fadein( int i, int max )
{
	button.fadein( i, max );
	sprite.fadein( i, max );
	label.fadein( i, max );
	actual.fadein( i, max );
	name.fadein( i, max );
	name_base.fadein( i, max );
	cost_text.fadein( i, max );
}

void Develop::fadeout( int i, int min )
{
	button.fadeout( i, min );
	sprite.fadeout( i, min );
	label.fadeout( i, min );
	actual.fadeout( i, min );
	name.fadeout( i, min );
	name_base.fadeout( i, min );
	cost_text.fadeout( i, min );
}



bool Develop::ableToUpgrade( int bank )
{
	locked = true;
	button.setOffset( 3 );
	
	if( bank >= cost && level < max )
	{
		locked = false;
		button.setOffset( 0 );
		return true;
	}
	
	return false;
}

void Develop::setCost( int newcost )
{
	if( level == max )
	{
		cost_text.setText( "illicit" );
		cost_text.setColor( 0xE8, 0x68, 0x50 );
	}
	else
	{
		cost = newcost;
		cost_text.setText( to_string( newcost ) );
	}
	
	cost_text.reloadPosition();
}

int Develop::getCost()
{
	return cost;
}

int Develop::getLevel()
{
	return level;
}



void Develop::setActual( int level, string actual )
{
	if( this->level != level || this->level == 0 )
	{
		this->level = level;
		
		if( this->level == max )
		{
			this->label.setText( "max" );
			this->label.setColor( 0xFF, 0xD8, 0x00 );
		}
		else
		{
			this->label.setText( to_string( level ) );
			
			if( level == 0 )	this->label.setColor( 0xE8, 0x68, 0x50 );
			else				this->label.setColor( 0x58, 0x70, 0x58 );
		}
		
		this->label.reloadPosition();
	}
	
	this->actual.setText( actual );
	this->actual.reloadPosition();
}