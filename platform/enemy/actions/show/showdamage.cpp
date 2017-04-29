#include "showdamage.h"
#include <cstdlib>

Showdamage::Showdamage()
{
	free();
}

Showdamage::~Showdamage()
{
	free();
}

void Showdamage::free()
{
	fadedout = false;
	
	if( !vels.empty() )
	{
		vels.clear();
	}
	
	if( !texts.empty() )
	{
		texts.clear();
	}
	
	if( !distances.empty() )
	{
		distances.clear();
	}
	
	if( !lines.empty() )
	{
		lines.clear();
	}
	
	if( !alphas.empty() )
	{
		alphas.clear();
	}
	
	text.free();
	x = y = 0;
}

void Showdamage::reset()
{
	fadedout = false;
	
	if( !vels.empty() )
	{
		vels.clear();
	}
	
	if( !texts.empty() )
	{
		texts.clear();
	}
	
	if( !distances.empty() )
	{
		distances.clear();
	}
	
	if( !lines.empty() )
	{
		lines.clear();
	}
	
	if( !alphas.empty() )
	{
		alphas.clear();
	}
}


void Showdamage::load()
{
	free();
	
	text.setFont( "data/initialization/Jaapokki-Regular.otf", 18, 0xFF, 0x33, 0x33 );
	text.setText( " " );
}

void Showdamage::draw( sf::RenderWindow &window )
{
	for( unsigned i = 0; i < texts.size(); i++ )
	{
		text.setText( texts[ i ] );
		if( !fadedout )
		{
			text.setAlpha( alphas[ i ] );
		}
		text.setPosition( x, y -distances[ i ] );
		window.draw( text.get() );
	}
}

void Showdamage::mechanics()
{
	for( unsigned i = 0; i < texts.size(); i++ )
	{
		alphas[ i ] -= 2;
		distances[ i ] += vels[ i ];
		
		if( alphas[ i ] <= 0 || distances[ i ] >= lines[ i ] )
		{
			vels.erase( vels.begin() +i );
			lines.erase( lines.begin() +i );
			distances.erase( distances.begin() +i );
			alphas.erase( alphas.begin() +i );
			texts.erase( texts.begin() +i );
			continue;
		}
	}
}


void Showdamage::run( string dmg )
{
	// printf( "happened\n" );
	vels.push_back( static_cast <float> (rand()%20 +80) /100 );
	lines.push_back( rand()%20 +60 );
	distances.push_back( 0 );
	alphas.push_back( 0xFF *0.75 );
	texts.push_back( dmg );
}

void Showdamage::focus( int x, int y )
{
	this->x = x;
	this->y = y +10;
}

void Showdamage::fadeout( int i, int min )
{
	fadedout = true;
	text.fadeout( i, min );
}