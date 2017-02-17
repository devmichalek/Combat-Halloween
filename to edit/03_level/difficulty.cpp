#include "difficulty.h"

Difficulty::Difficulty()
{
	offset = 0;
	delay = 0;
	state = 0;
	
	result = 0;
	
	range = 0;
	keep = false;
}

Difficulty::~Difficulty()
{
	free();
}

void Difficulty::free()
{
	poi.free();
	graph.free();
	
	if( !text.empty() )
	{
		for( auto &i :text )
		{
			i->free();
		}
		
		text.clear();
	}
	
	offset = 0;
	delay = 0;
	state = 0;
	
	result = 0;
	
	range = 0;
	keep = false;
}

void Difficulty::reset( int left, int bot )
{
	graph.setPosition( left +200, bot +20 );
	poi.setPosition( graph.getX(), graph.getY() );
	
	text[ 0 ]->setPosition( graph.getX(), graph.getBot() +5 );
	text[ 1 ]->setPosition( text[ 0 ]->getRight() +40, graph.getBot() +5 );
	text[ 2 ]->setPosition( text[ 1 ]->getRight() +73, graph.getBot() +5 );
	text[ 3 ]->setPosition( text[ 2 ]->getRight() +45, graph.getBot() +5 );
	
	setDifficulty( 45 );
}

void Difficulty::load( int left, int bot )
{
	free();
	
	delay = 7;
	state = 20;
	
	poi.setName( "difficulty-poi" );
	poi.load( "data/sprites/level/poi.png", state );
	
	graph.setName( "difficulty-graph" );
	graph.load( "data/sprites/level/graph.png" );
	
	int nr = 4;
	for( int i = 0; i < nr; i++ )
	{
		text.push_back( new MyText() );
		text[ text.size() -1 ]->setFont( "data/fonts/Jaapokki-Regular.otf", 20, 255, 255, 255 );
	}
	
	text[ 0 ]->setText( "chicken" );
	text[ 1 ]->setText( "normal" );
	text[ 2 ]->setText( "hard" );
	text[ 3 ]->setText( "bad-ass" );
	
	reset( left, bot );
	
	
	click.setID( "worldsize-click" );
	click.load( "data/sounds/click.wav", 50 );
}

void Difficulty::handle( sf::Event &event )
{
	if( graph.getAlpha() == 0xFF )
	{
		if( event.type == sf::Event::MouseButtonPressed )
		{
			int x, y;
			
			x = event.mouseButton.x;
			y = event.mouseButton.y;
				
			if( graph.checkCollision( x, y ) )
			{
				if( play )
				{
					click.play();
				}
				
				int v = (x -graph.getX()) *100 /graph.getWidth();
				
				setDifficulty( v );
			}
		}
	}
}

void Difficulty::draw( sf::RenderWindow &window )
{
	window.draw( graph.get() );
	
	offset ++;
	if( offset == state *delay )
		offset = 0;
	
	poi.setOffset( offset /delay );
	window.draw( poi.get() );
	
	for( auto &i :text )
	{
		window.draw( i->get() );
	}
}

void Difficulty::fadein( int j, int max )
{
	graph.fadein( j +2, max );
	poi.fadein( j, max );
	
	for( auto &i :text )
	{
		i->fadein( j +2, max );
	}
}

void Difficulty::fadeout( int j, int min )
{
	graph.fadeout( j, min );
	poi.fadeout( j +2, min );
	
	for( auto &i :text )
	{
		i->fadeout( j, min );
	}
}


void Difficulty::setDifficulty( int value )
{
	result = value;
	float v = static_cast <float> (value) /100;
	int newX = graph.getX() +graph.getWidth() *v -poi.getWidth()/2;
	
	if( newX < graph.getX() )
	{
		newX = graph.getX();
	}
	else if( newX +poi.getWidth() > graph.getRight() )
	{
		newX = graph.getRight() -poi.getWidth();
	}
	
	poi.setPosition( newX, poi.getY() );
}

int Difficulty::getDifficulty()
{
	return result;
}


bool Difficulty::move( int vel, int scope )
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
		
		poi.setPosition( poi.getX() +vel, poi.getY() );
		graph.setPosition( graph.getX() +vel, graph.getY() );
		
		for( auto &i :text )
		{
			i->setPosition( i->getX() +vel, i->getY() );
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
