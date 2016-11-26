#include "map_editor/brickXY.h"

BrickXY::BrickXY()
{
	width = 0;
	screen_h = 0;
	
	brick_nr = 0;
	brick = NULL;
	
	x = imx = -1;
	y = imy = -1;
	
	realXY = "x: -1  y: -1";
	imagXY = "w: 0  h: 0";
	action = false;
}

BrickXY::~BrickXY()
{
	free();
}

void BrickXY::free()
{
	width = 0;
	screen_h = 0;
	
	if( brick != NULL )
	{
		delete [] brick;
		brick = NULL;
		brick_nr = 0;
	}

	x = imx = -1;
	y = imy = -1;
	
	realXY = "x: -1  y: -1";
	imagXY = "w: 0  h: 0";
	
	real.free();
	imag.free();
	action = false;
}


void BrickXY::load( int screen_w, int screen_h )
{
	free();
	
	width = 128;
	this->screen_h = screen_h;
	
	
	// set bricks
	brick_nr = 8;
	brick = new MySprite[ brick_nr ];
	
	for( int i = 0; i < brick_nr -1; i++ )
	{
		brick[ i ].setName( "BrickXY-brick[" + to_string( i ) + "]" );
		brick[ i ].create( width, width );
		brick[ i ].setColor( sf::Color( 0xCC, 0xCC, 0xCC ) );
		brick[ i ].setAlpha( 0xFF );
		brick[ i ].setPosition( screen_w -width*2, screen_h -width*i );
	}
	
	brick[ brick_nr -1 ].setName( "BrickXY-dot" );
	brick[ brick_nr -1 ].create( 1, 1 );
	brick[ brick_nr -1 ].setColor( sf::Color( 0, 0, 0 ) );
	brick[ brick_nr -1 ].setAlpha( 0xFF );
	
	
	
	// Text
	real.setID( "brickXY-real" );
	real.setFont( "data/fonts/Jaapokki-Regular.otf", 17, 0x99, 0x66, 0x33 );
	real.setText( realXY );
	real.setPosition( brick[ 0 ].getRight() +10, real.getHeight() );
	real.setAlpha( 0xFF );
	
	imag.setID( "brickXY-imag" );
	imag.setFont( "data/fonts/Jaapokki-Regular.otf", 17, 0x33, 0x66, 0x99 );
	imag.setText( imagXY );
	imag.setPosition(  brick[ 0 ].getRight() +10, real.getBot() +4 );
	imag.setAlpha( 0xFF );
}

void BrickXY::draw( sf::RenderWindow* &window )
{
	// Draw bricks
	for( int i = 0; i < brick_nr-1; i ++ )
	{
		window->draw( brick[ i ].get() );
	}
		
	// Draw points
	for( int i = brick[ 0 ].getLeft(); i < brick[ 0 ].getRight(); i += 2 )	// our x
	{
		for( int j = screen_h; j > 0; j -= width ) // our y
		{
			brick[ brick_nr -1 ].setPosition( i, j );
			window->draw( brick[ brick_nr -1 ].get() );
		}
	}
}

void BrickXY::drawXY( sf::RenderWindow* &window )
{
	window->draw( real.get() );
	window->draw( imag.get() );
	
	if( action )
	{
		action = false;
		
		realXY = "x: " + to_string( x ) + "  y: " + to_string( y );
		real.setText( realXY );
		real.reloadPosition();
	}
	
	imagXY = "w: " + to_string( imx ) + "  h: " + to_string( imy );
	imag.setText( imagXY );
	imag.reloadPosition();
	
	imx = 0;
	imy = 0;
}

void BrickXY::handle( sf::Event &event )
{
	for( int i = 0; i < brick_nr -1; i ++ )
	{
		brick[ i ].setColor( sf::Color( 0xCC, 0xCC, 0xCC ) );
	}

	if( event.type == sf::Event::MouseMoved )
	{
		action = true;
		x = event.mouseMove.x;
		y = event.mouseMove.y;
		
		for( int i = 0; i < brick_nr -1; i ++ )
		{
			if( brick[ i ].checkCollision( x, y )  )
			{
				brick[ i ].setColor( sf::Color( 0xCC, 0xCC, 88 ) );
			}
		}
	}
	
	else if( event.type == sf::Event::MouseButtonPressed )
	{
		action = true;
		x = event.mouseButton.x;
		y = event.mouseButton.y;
		
		for( int i = 0; i < brick_nr -1; i ++ )
		{
			if( brick[ i ].checkCollision( x, y )  )
			{
				brick[ i ].setColor( sf::Color( 0xCC, 0xCC, 88 ) );
			}
		}
	}
	else if( event.type == sf::Event::MouseButtonReleased )
	{
		for( int i = 0; i < brick_nr -1; i ++ )
		{
			if( brick[ i ].checkCollision( x, y )  )
			{
				brick[ i ].setColor( sf::Color( 0xCC, 0xCC, 88 ) );
			}
		}
	}
}

void BrickXY::getImag( int imx, int imy )
{
	this->imx = imx;
	this->imy = imy;
}