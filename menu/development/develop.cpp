/**
    develop.h
    Purpose: class Develop - for one special skill in menu state.

    @author Adrian Michalek
    @version 2017.02.02
	@email adrmic98@gmail.com
*/

#include "menu/development/develop.h"
#include "file/file.h"

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
	
	y_state = 0;
	scale = 0;
	scale_sprite = 0;
}



void Develop::load( int nr, int bot )
{
	free();
	
	// Set states.
	y_state = bot;
	
	// Set scale.
	scale = 0.36;
	scale_sprite = 0.5;
	
	// Load button.
	button.setName( "develop-button" );
	button.load( "data/menu/upgrade.png", 4 );
	
	MyFile file;
	
	// Set name.
	file.load( "data/txt/skill/skill_name.txt" );
	if( file.is_good() )
	{
		string line;
		int counter = nr;
		while( getline( file.get(), line ) )
		{
			if( counter == 0 )
			{
				
				name.setName( "develop-name" );
				name.setFont( "data/initialization/Jaapokki-Regular.otf", 30, 255, 255, 255 );
				name.setText( line );
				break;
			}
			
			counter --;
		}
	}
	file.free();
	
	// Load sprite.
	sprite.setName( "develop-sprite" );
	sprite.load( "data/menu/skill/" +con::itos( nr ) +".png" );
	
	// Set name_base.
	file.load( "data/txt/skill/skill_namebase.txt" );
	if( file.is_good() )
	{
		string line;
		int counter = nr;
		while( file.get() >> line )
		{
			if( counter == 0 )
			{
				// set name
				name_base.setName( "develop-name" );
				name_base.setFont( "data/initialization/Jaapokki-Regular.otf", 30, 255, 255, 255 );
				name_base.setText( line );
				break;
			}
			
			counter --;
		}
	}
	file.free();
	
	// Set max.
	file.load( "data/txt/skill/skill_max.txt" );
	if( file.is_good() )
	{
		string line;
		int counter = nr;
		while( file.get() >> line )
		{
			if( counter == 0 )
			{
				max = con::stoi( line );
				break;
			}
			
			counter --;
		}
	}
	file.free();
	
	// Set actual.
	actual.setName( "develop-actual" );
	actual.setFont( "data/initialization/Jaapokki-Regular.otf", 30, 255, 255, 255 );
	actual.setText( " " );
	
	// Set label.
	label.setName( "develop-label" );
	label.setFont( "data/initialization/Jaapokki-Regular.otf", 30, 255, 255, 255 );
	label.setText( " " );
	
	// Cost_text settings.
	cost_text.setName( "develop-cost_text" );
	cost_text.setFont( "data/initialization/Jaapokki-Regular.otf", 30, 255, 255, 255 );
	cost_text.setText( " " );
	cost_text.setColor( 0xFF, 0xD8, 0x00 );
	
	// Load click.
	click.setID( "develop-click" );
	click.load( "data/menu/click.wav", 50 );
	
	// Other.
	button.setOffset( 3 );
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

void Develop::handle( sf::Event &event, int r_x, int r_y )
{
	if( !locked && level < max )
	{
		int x, y;
		button.setOffset( 0 );

		if( event.type == sf::Event::MouseMoved )
		{
			x = event.mouseMove.x;
			y = event.mouseMove.y;
				
			if( button.checkCollision( x +r_x, y +r_y ) )
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
				
			if( button.checkCollision( x+r_x, y +r_y ) )
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
					this->label.setText( con::itos( level ) );
					
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
		cost_text.setText( con::itos( newcost ) );
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
			this->label.setText( con::itos( level ) );
			
			if( level == 0 )	this->label.setColor( 0xE8, 0x68, 0x50 );
			else				this->label.setColor( 0x58, 0x70, 0x58 );
		}
		
		this->label.reloadPosition();
	}
	
	this->actual.setText( actual );
	this->actual.reloadPosition();
}



void Develop::setScale( float s_x, float s_y )
{
	button.setBasicScale( s_x, s_y );
	button.setScale( scale, scale );
	
	sprite.setBasicScale( s_x, s_y );
	sprite.setScale( scale_sprite, scale_sprite );
	
	label.setBasicScale( s_x, s_y );
	label.setScale();
	
	actual.setBasicScale( s_x, s_y );
	actual.setScale();
	
	name.setBasicScale( s_x, s_y );
	name.setScale();
	
	name_base.setBasicScale( s_x, s_y );
	name_base.setScale();
	
	cost_text.setBasicScale( s_x, s_y );
	cost_text.setScale();
}

void Develop::setView( int w, int h, int r_x, int r_y )
{
	// Positions.
	button.setPosition( w /1.321 +r_x, (y_state -10) *button.getYScale() /scale +r_y );
	sprite.setPosition( w /50 +r_x, (y_state -10) *sprite.getYScale() /scale_sprite +r_y );
	int new_y = (y_state -10) *sprite.getYScale() /scale_sprite;
	
	name.setPosition( w /12.5 +r_x, new_y +r_y );
	
	label.setPosition( w /3.225 +r_x, new_y +r_y );
	actual.setPosition( w /2.34 +r_x, new_y +r_y );
	name_base.setPosition( w /1.754 +r_x, new_y +r_y );
	
	
	cost_text.setPosition( w /1.166 +r_x, new_y +r_y );
}