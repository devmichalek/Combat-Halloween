#include "knight_specs.h"
#include "own/file.h"

Knight_specs::Knight_specs()
{
	free();
}

Knight_specs::~Knight_specs()
{
	free();
}

void Knight_specs::free()
{
	animation.free();
	if( !parts.empty() )
	{
		for( auto &it :parts )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		parts.clear();
	}
	if( !blocks.empty() )
	{
		for( auto &it :blocks )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		blocks.clear();
	}
	
	chosen = -1;
	lastChosen = -1;
	x = y = 0;
	
	offset = 0;
	line = 0;
}



void Knight_specs::load( float screen_w, float screen_h )
{
	free();
	
	line = 10;
	animation.setIdentity( "Knight_specs-animation" );
	animation.load( "images/knight/0.png", line );
	animation.setScale( screen_w /2560, screen_h /1440 );
	animation.setPosition( screen_w /7, screen_h -screen_h/72 -animation.getHeight() );
	
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		parts.push_back( new MySprite );
		parts[ i ]->setIdentity( "Knight_specs-parts" );
		parts[ i ]->load( "images/knight/parts/" +con::itos(i) +".png" );
		parts[ i ]->setScale( screen_w /2560, screen_h /1440 );
		
		blocks.push_back( new MySprite );
		blocks[ i ]->setIdentity( "Knight_specs-blocks" );
		blocks[ i ]->create( parts[ i ]->getWidth(), parts[ i ]->getHeight() );
		blocks[ i ]->setColor( sf::Color( 0x7C, 0x47, 0x11 ) );
	}
	
	parts[ HELMET ]->setPosition( screen_w /5.5, screen_h /1.8 );
	parts[ BODY ]->setPosition( screen_w /4.6, screen_h /1.25 );
	parts[ SHIELD ]->setPosition( screen_w /5.9, screen_h /1.2 );
	parts[ SWORD ]->setPosition( screen_w /3.65, screen_h /1.3 );
	parts[ BOOTS ]->setPosition( screen_w /5.8, screen_h -screen_h/72 -parts[ BOOTS ]->getHeight() );
	
	for( unsigned i = 0; i < parts.size(); i++ )
	{
		blocks[ i ]->setPosition( parts[ i ]->getX(), parts[ i ]->getY() );
	}
	
	x = screen_w /10;
	y = screen_h /3;
}

void Knight_specs::handle( sf::Event& event )
{
	if( event.type == sf::Event::MouseButtonPressed )
	{
		if( event.mouseButton.button == sf::Mouse::Left )
		{
			if( lastChosen == -1 )
			{
				bool clear = true;
				for( unsigned i = 0; i < parts.size(); i++ )
				{
					if( parts[ i ]->checkCollision( event.mouseButton.x, event.mouseButton.y ) && chosen != i )
					{
						clear = false;
						lastChosen = chosen;
						chosen = i;
						break;
					}
				}
				
				if( clear )
				{
					lastChosen = chosen;
					chosen = -1;
				}
			}
		}
	}
}

void Knight_specs::draw( sf::RenderWindow* &window )
{
	window->draw( animation.get() );
	
	if( chosen != -1 )
	{
		window->draw( parts[ chosen ]->get() );
		window->draw( blocks[ chosen ]->get() );
	}
	
	if( lastChosen != -1 )
	{
		window->draw( parts[ lastChosen ]->get() );
		window->draw( blocks[ lastChosen ]->get() );
	}
}

void Knight_specs::mechanics( double elapsedTime )
{
	offset += elapsedTime *25;
	if( offset > line )
	{
		offset = 0;
	}
	animation.setOffset( offset );
	
	float vel = elapsedTime *2;
	
	if( chosen != -1 )
	{
		if( parts[ chosen ]->getY() > y || parts[ chosen ]->getX() > x )
		{
			parts[ chosen ]->move( (x -blocks[ chosen ]->getX()) *vel, (y -blocks[ chosen ]->getY()) *vel );
		}
	}
	
	if( lastChosen != -1 && (chosen == -1 || lastChosen != chosen) )
	{
		if( parts[ lastChosen ]->getY() < blocks[ lastChosen ]->getY() || parts[ lastChosen ]->getX() < blocks[ lastChosen ]->getX() )
		{
			parts[ lastChosen ]->move( (blocks[ lastChosen ]->getX() -x) *vel, (blocks[ lastChosen ]->getY() -y) *vel );
		}
		else
		{
			lastChosen = -1;
		}
	}
}



void Knight_specs::fadein( float v, int max )
{
	animation.fadein( v, max );
	
	for( auto &it :parts )
	{
		it->fadein( v, max );
	}
	
	for( auto &it :blocks )
	{
		it->fadein( v, max /3 );
	}
}

void Knight_specs::fadeout( float v, int min )
{
	animation.fadeout( v, min );
	
	for( auto &it :parts )
	{
		it->fadeout( v, min );
	}
	
	for( auto &it :blocks )
	{
		it->fadeout( v, min );
	}
}