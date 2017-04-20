/**
    cube.h
    Purpose: class Cube as a world setter.

    @author Adrian Michalek
    @version 2017.02.13
	@email adrmic98@gmail.com
*/

#include "cube.h"
#include "file/file.h"

Cube::Cube()
{
	flatness_value = 0;
	worldSize_value = 0;
	
	offset = 0;
	delay = 0;
	line = 0;
	
	range = 0;
	keep = false;
}

Cube::~Cube()
{
	free();
}

void Cube::free()
{
	down.free();
	left.free();
	paper.free();
	cube.free();
	
	flatness.free();
	worldSize.free();
	
	offset = 0;
	delay = 0;
	line = 0;
	
	range = 0;
	keep = false;
	
	click.free();
}

void Cube::reset( int left, int bot )
{
	paper.setPosition( left +40, bot +120 );
	cube.center( paper.getX() -5, paper.getY() -5, paper.getWidth(), paper.getHeight() );
	
	flatness_value = 50;
	worldSize_value = 27;
	setFlatness( flatness_value );
	setWorldSize( worldSize_value );
	flatness.setPosition( paper.getX() -30, paper.getBot() -paper.getHeight()/6 );
	worldSize.setPosition( paper.getX() +50, paper.getBot() +5 );
}

void Cube::load( int left, int bot )
{
	free();
	
	delay = 5;
	line = 61;
	
	down.setName( "cube-down" );
	down.load( "data/level/down.png" );
	
	this->left.setName( "cube-left" );
	this->left.load( "data/level/left.png" );
	
	paper.setName( "cube-paper" );
	paper.load( "data/level/paper.png" );
	
	cube.setName( "cube-right" );
	cube.load( "data/level/cube.png", line );
	
	flatness.setFont( "data/initialization/Jaapokki-Regular.otf", 20, 0xFF, 0xFF, 0xFF );
	worldSize.setFont( "data/initialization/Jaapokki-Regular.otf", 20, 0xFF, 0xFF, 0xFF );
	
	reset( left, bot );
	
	click.setID( "cube-click" );
	click.load( "data/menu/click.wav", 50 );
}

void Cube::handle( sf::Event &event )
{
	if( paper.getAlpha() == 0xFF )
	{
		if( event.type == sf::Event::MouseButtonPressed )
		{
			int x, y;
			
			x = event.mouseButton.x;
			y = event.mouseButton.y;
				
			if( paper.checkCollision( x, y ) )
			{
				if( play )
				{
					click.play();
				}
				
				int s_v = (x -paper.getX()) *100 /paper.getWidth();
				int f_v = 100 -((y -paper.getY())  *100 /paper.getHeight());
				
				setWorldSize( s_v );
				setFlatness( f_v );
			}
		}
	}
}

void Cube::draw( sf::RenderWindow &window )
{
	window.draw( paper.get() );
	
	offset ++;
	if( offset == line *delay )
		offset = 0;
	
	cube.setOffset( offset /delay );
	window.draw( cube.get() );
	
	window.draw( down.get() );
	window.draw( left.get() );
	
	window.draw( flatness.get() );
	window.draw( worldSize.get() );
}

void Cube::fadein( int j, int max )
{
	down.fadein( j, max );
	left.fadein( j, max );
	paper.fadein( j +2, max );
	cube.fadein( j, max );
	flatness.fadein( j, max );
	worldSize.fadein( j, max );
}

void Cube::fadeout( int j, int min )
{
	down.fadeout( j, min );
	left.fadeout( j, min );
	paper.fadeout( j, min );
	cube.fadeout( j +2, min );
	flatness.fadeout( j, min );
	worldSize.fadeout( j, min );
}


void Cube::setFlatness( int value )
{
	flatness_value = value;
	flatness.setText( "flatness " +con::itos( value ) + " %" );
	flatness.reloadPosition();
	flatness.setRotation( 270 );
	
	float surplus = static_cast <float> (value) /100;
	// printf( "%f\n", surplus );
	left.setPosition( paper.getRight(), paper.getBot() -paper.getHeight()*surplus -down.getHeight()/2 +3 );
}

void Cube::setWorldSize( int value )
{
	worldSize_value = value *3 +30;
	worldSize.setText( "length: " +con::itos( worldSize_value ) );
	worldSize.reloadPosition();
	
	float surplus = static_cast <float> (value) /100;
	// printf( "%f\n", surplus );
	down.setPosition( paper.getX() +paper.getHeight()*surplus -down.getWidth()/2, paper.getY() -down.getHeight() );
}



bool Cube::move( int vel, int scope )
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
		
		down.setPosition( down.getX() +vel, down.getY() );
		left.setPosition( left.getX() +vel, left.getY() );
		paper.setPosition( paper.getX() +vel, paper.getY() );
		cube.setPosition( cube.getX() +vel, cube.getY() );
		
		flatness.setPosition( flatness.getX() +vel, flatness.getY() );
		worldSize.setPosition( worldSize.getX() +vel, worldSize.getY() );
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

int Cube::getFlatness()
{
	return flatness_value;
}

int Cube::getWorldSize()
{
	return worldSize_value;
}

int Cube::getTop()
{
	return paper.getTop();
}

int Cube::getRight()
{
	return paper.getRight();
}