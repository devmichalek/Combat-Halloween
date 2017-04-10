#include "04_platform/panel/scores/scores.h"
#include "file/file.h"

Scores::Scores()
{
	free();
}

Scores::~Scores()
{
	free();
}

void Scores::free()
{
	text.free();
	
	result = 0;
	last_result = 0;
	screen_w = 0;
	
	scale = 0;
	scale_bot = 0;
	point_scale_top = 0;
	foe_point_scale_top = 0;
	scale_vel = 0;
}

void Scores::reset()
{
	result = 0;
	last_result = 0;
	scale = scale_bot;
	
	text.setText( con::itos( result ) );
	text.setScale( scale, scale );
	text.setPosition( screen_w /2 -text.getWidth() /2, 5 );
}



void Scores::load( int type, int screen_w )
{
	free();
	
	this->screen_w = screen_w;
	
	text.setName( "scores-text" );
	text.setFont( "data/00_loading/Jaapokki-Regular.otf", 46, 0xFF, 0xFF, 0xFF );
	text.setText( "0" );
	text.setPosition( screen_w /2 -text.getWidth() /2, 5 );
	
	scale_bot = 1;
	point_scale_top = 1.85;
	foe_point_scale_top = 2.5;
	scale_vel = 0.05;
	scale = scale_bot;
	
	// Set point.
	MyFile file;
	file.load( "data/txt/scores/points.txt" );
	if( file.is_good() )
	{
		int c = type;
		string line;
		while( file.get() >> line )
		{
			if( c == 0 )
			{
				point = con::stoi( line );
				// printf( "%d\n", point );
				break;
			}
			
			c--;
		}
	}
	file.free();
	
	// Set foe point.
	file.load( "data/txt/scores/foes.txt" );
	if( file.is_good() )
	{
		int c = type;
		string line;
		while( file.get() >> line )
		{
			if( c == 0 )
			{
				foe_point = con::stoi( line );
				break;
			}
			
			c--;
		}
	}
	file.free();
}

void Scores::draw( sf::RenderWindow* &window )
{
	window->draw( text.get() );
}

void Scores::positioning( int chance )
{
	point += point *(static_cast <float> (chance) /100);
	foe_point += foe_point *(static_cast <float> (chance) /100);
}

void Scores::mechanics()
{
	if( result != last_result )
	{
		last_result = result;
		text.setText( con::itos( result ) );
		text.reloadPosition();
	}
	
	if( scale > scale_bot )
	{
		scale -= scale_vel;
		text.setScale( scale, scale );
		text.setPosition( screen_w /2 -text.getWidth() /2, 5 );
	}
}



void Scores::fadein( int v, int max )
{
	text.fadein( v, max *0.6 );
}

void Scores::fadeout( int v, int min )
{
	text.fadeout( v, min );
}



void Scores::addPoint()
{
	result += rand()%(point /2) +(point /2);
	scale = point_scale_top;
}

void Scores::addFoePoint()
{
	result += rand()%(foe_point /2) +(foe_point /2);
	scale = foe_point_scale_top;
}

int Scores::getScores()
{
	return result;
}