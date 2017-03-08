#include "showheal.h"

void Showheal::load()
{
	free();
	
	text.setFont( "data/00_loading/Jaapokki-Regular.otf", 20, 0x32, 0xCD, 0x32 );
	text.setText( " " );
}

void Showheal::run( string dmg )
{
	// printf( "happened\n" );
	vels.push_back( static_cast <float> (rand()%20 +80) /100 );
	lines.push_back( rand()%20 +50 );
	distances.push_back( 0 );
	alphas.push_back( 0xFF *0.9 );
	texts.push_back( dmg );
}