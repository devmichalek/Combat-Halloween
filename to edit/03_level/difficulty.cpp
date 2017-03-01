#include "difficulty.h"

Difficulty::Difficulty()
{
	result = 0;
	alpha_line = 0;
	
	range = 0;
	keep = false;
}

Difficulty::~Difficulty()
{
	free();
}

void Difficulty::free()
{
	corruption.free();
	
	if( !texts.empty() )
	{
		for( auto &i :texts )
		{
			i->free();
		}
		
		texts.clear();
	}
	
	if( !sprites.empty() )
	{
		for( auto &i :sprites )
		{
			i->free();
		}
		
		sprites.clear();
	}
	
	result = 0;
	alpha_line = 0;
	
	range = 0;
	keep = false;
}

void Difficulty::reset( int left, int bot )
{
	corruption.setPosition( left +350, bot +50 );
	
	texts[ 0 ]->setPosition( corruption.getX() -texts[ 0 ]->getWidth() -54, corruption.getBot() +texts[ 0 ]->getHeight() );
	texts[ 1 ]->setPosition( texts[ 0 ]->getRight() +texts[ 1 ]->getWidth(), texts[ 0 ]->getY() );
	texts[ 2 ]->setPosition( texts[ 1 ]->getRight() +texts[ 1 ]->getWidth(), texts[ 0 ]->getY() );
	
	int y = texts[ 0 ]->getY() -sprites[ 0 ]->getHeight()/7;
	for( unsigned i = 0; i < sprites.size(); i++ )
	{
		sprites[ i ]->setPosition( texts[ i ]->getX() -sprites[ i ]->getWidth(), y );
	}
}



void Difficulty::load( int left, int bot )
{
	free();
	
	corruption.setName( "difficulty-corruption" );
	corruption.setFont( "data/00_loading/Jaapokki-Regular.otf", 25, 255, 255, 255 );
	corruption.setText( "Corruption" );
	
	
	int nr = 3;
	for( int i = 0; i < nr; i++ )
	{
		texts.push_back( new MyText() );
		texts[ texts.size() -1 ]->setFont( "data/00_loading/Jaapokki-Regular.otf", 25, 255, 255, 255 );
		
		sprites.push_back( new MySprite() );
		sprites[ sprites.size() -1 ]->load( "data/03_level/" +to_string( i ) +".png" );
	}
	
	texts[ 0 ]->setText( "low" );
	texts[ 1 ]->setText( "medium" );
	texts[ 2 ]->setText( "high" );
	
	reset( left, bot );
	alpha_line = 100;
	result = 33;
	sprites[ 0 ]->setAlpha( 0xFF );
	
	
	click.setID( "difficulty-click" );
	click.load( "data/02_menu/click.wav", 50 );
}

void Difficulty::handle( sf::Event &event )
{
	if( corruption.getAlpha() == 0xFF )
	{
		if( event.type == sf::Event::MouseButtonPressed )
		{
			int x, y;
			
			x = event.mouseButton.x;
			y = event.mouseButton.y;
			
			for( unsigned i = 0; i < sprites.size(); i++ )
			{
				if( sprites[ i ]->checkCollision( x, y ) || texts[ i ]->checkCollision( x, y ) )
				{
					for( auto &i :sprites )
					{
						i->setAlpha( alpha_line );
					}
					
					if( play )
					{
						click.play();
					}
					
					sprites[ i ]->setAlpha( 0xFF );
					result = 33 *( i +1 );
				}
			}
		}
	}
}

void Difficulty::draw( sf::RenderWindow &window )
{
	window.draw( corruption.get() );
	
	for( auto &i :texts )
	{
		window.draw( i->get() );
	}
	
	for( auto &i :sprites )
	{
		window.draw( i->get() );
	}
}



void Difficulty::fadein( int j, int max )
{
	corruption.fadein( j, max );
	
	for( auto &i :texts )
	{
		i->fadein( j, max );
	}
	
	for( auto &i :sprites )
	{
		i->fadein( j, alpha_line );
	}
}

void Difficulty::fadeout( int j, int min )
{
	corruption.fadeout( j, min );
	
	for( auto &i :texts )
	{
		i->fadeout( j, min );
	}
	
	for( auto &i :sprites )
	{
		i->fadeout( j, min );
	}
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
		
		corruption.setPosition( corruption.getX() +vel, corruption.getY() );

		for( auto &i :texts )
		{
			i->setPosition( i->getX() +vel, i->getY() );
		}
		
		for( auto &i :sprites )
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
