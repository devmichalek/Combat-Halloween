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
	table.free();
	gear_top.free();
	gear_bot.free();
	moving_state = 0;
	x1 = x2 = 0;
	
	knight.free();
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
	if( !rects.empty() )
	{
		rects.clear();
	}
	
	chosen = -1;
	lastChosen = -1;
	
	offset = 0;
	line = 0;
	
	click.free();
}



void Knight_specs::load( float screen_w, float screen_h )
{
	free();
	
	click.setIdentity( "link_button-chunk" );
	click.load( "sounds/click.wav" );
	
	line = 10;
	knight.setIdentity( "knight_specs-animation" );
	knight.load( "images/knight/0.png", line );
	knight.setScale( screen_w /2560, screen_h /1440 );
	knight.setPosition( screen_w /7, screen_h -screen_h/72 -knight.getHeight() );
	
	x2 = -screen_w /128;	
	table.setIdentity( "knight_specs-table" );
	table.load( "images/menu/table.png" );
	table.setScale( screen_w /2560, screen_h /1440 );
	x1 = -table.getWidth() +screen_w /128;
	table.setPosition( x1, screen_h /5.5 );
	
	x = screen_w /64;
	y = screen_h /5 +table.getHeight() /2.5;
	
	gear_top.setIdentity( "knight_specs-gear_top" );
	gear_top.load( "images/menu/gear.png" );
	gear_top.setOrigin( gear_top.getWidth() *0.5, gear_top.getHeight() *0.5 );
	gear_top.setScale( screen_w /2560, screen_h /1440 );
	gear_top.setPosition( 0, table.getTop() );
	
	gear_bot.setIdentity( "knight_specs-gear_bot" );
	gear_bot.load( "images/menu/gear.png" );
	gear_bot.setOrigin( gear_bot.getWidth() *0.5, gear_bot.getHeight() *0.5 );
	gear_bot.setScale( screen_w /2560, screen_h /1440 );
	gear_bot.setPosition( 0, table.getBot() );
	
	
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		parts.push_back( new MySprite );
		parts[ i ]->setIdentity( "knight_specs-parts" );
		parts[ i ]->load( "images/knight/parts/" +con::itos(i) +".png" );
		parts[ i ]->setScale( screen_w /2560, screen_h /1440 );
		
		rects.push_back( new sf::Vector2f );
	}
	
	parts[ HELMET ]->setPosition( screen_w /5.5, screen_h /1.8 );
	parts[ BODY ]->setPosition( screen_w /4.6, screen_h /1.25 );
	parts[ SHIELD ]->setPosition( screen_w /5.9, screen_h /1.2 );
	parts[ SWORD ]->setPosition( screen_w /3.65, screen_h /1.3 );
	parts[ BOOTS ]->setPosition( screen_w /5.8, screen_h -screen_h/72 -parts[ BOOTS ]->getHeight() );
	
	for( unsigned i = 0; i < parts.size(); i++ )
	{
		rects[ i ]->x = parts[ i ]->getX();
		rects[ i ]->y = parts[ i ]->getY();
	}
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
					if( parts[ i ]->checkCollision( event.mouseButton.x, event.mouseButton.y ) && chosen != static_cast <int> (i) )
					{
						if( playable )
						{
							click.play();
						}
						
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
	window->draw( knight.get() );
	window->draw( table.get() );
	window->draw( gear_top.get() );
	window->draw( gear_bot.get() );
	
	if( chosen != -1 && moving_state == 0 )
	{
		window->draw( parts[ chosen ]->get() );
		
		if( parts[ chosen ]->getY() < y -parts[ chosen ]->getHeight()/2 || parts[ chosen ]->getX() < x )
		{
			parts[ chosen ]->setPosition( x, y -parts[ chosen ]->getHeight()/2 );
		}
	}
	
	if( lastChosen != -1 && moving_state == 0 )
	{
		window->draw( parts[ lastChosen ]->get() );
		
		if( parts[ lastChosen ]->getY() > rects[ lastChosen ]->y || parts[ lastChosen ]->getX() > rects[ lastChosen ]->x )
		{
			parts[ lastChosen ]->setPosition( rects[ lastChosen ]->x, rects[ lastChosen ]->y );
		}
	}
}

void Knight_specs::mechanics( double elapsedTime )
{
	offset += elapsedTime *25;
	if( offset > line )
	{
		offset = 0;
	}
	knight.setOffset( offset );
	
	float vel = elapsedTime *2;
	
	if( chosen != -1 && moving_state == 0 )
	{
		if( parts[ chosen ]->getY() > y -parts[ chosen ]->getHeight()/2 || parts[ chosen ]->getX() > x )
		{
			parts[ chosen ]->move( (x -rects[ chosen ]->x) *vel, (y -rects[ chosen ]->y -parts[ chosen ]->getHeight()/2) *vel );
			// printf( "%f\n", parts[ chosen ]->getX() );
		}
	}
	
	if( lastChosen != -1 && (chosen == -1 || lastChosen != chosen) )
	{
		if( parts[ lastChosen ]->getY() < rects[ lastChosen ]->y || parts[ lastChosen ]->getX() < rects[ lastChosen ]->x )
		{
			parts[ lastChosen ]->move( (rects[ lastChosen ]->x -x) *vel, (rects[ lastChosen ]->y -y +parts[ lastChosen ]->getHeight()/2) *vel );
		}
		else
		{
			lastChosen = -1;
		}
	}
	
	float rotation = elapsedTime *0xFF;
	if( (lastChosen == -1 && chosen == -1) && table.getX() > x1 )
	{
		gear_top.setRotation( gear_top.getRotation() -rotation );
		gear_bot.setRotation( gear_bot.getRotation() -rotation );
		moving_state = -elapsedTime *0xFF;
	}
	else if( (lastChosen != -1 || chosen != -1) && table.getX() < x2 )
	{
		gear_top.setRotation( gear_top.getRotation() +rotation );
		gear_bot.setRotation( gear_bot.getRotation() +rotation );
		moving_state = elapsedTime *0xFF;
	}
	else
	{
		moving_state = 0;
	}
	
	if( moving_state != 0 )
	{
		table.move( moving_state, 0 );
	}
	
	if( table.getX() < x1 )
	{
		table.setPosition( x1, table.getY() );
	}
	else if( table.getX() > x2 )
	{
		table.setPosition( x2, table.getY() );
	}
}



void Knight_specs::fadein( float v, int max )
{
	knight.fadein( v, max );
	table.fadein( v, max );
	gear_top.fadein( v, max );
	gear_bot.fadein( v, max );
	
	for( auto &it :parts )
	{
		it->fadein( v, max );
	}
}

void Knight_specs::fadeout( float v, int min )
{
	knight.fadeout( v, min );
	table.fadeout( v, min );
	gear_top.fadeout( v, min );
	gear_bot.fadeout( v, min );
	
	for( auto &it :parts )
	{
		it->fadeout( v, min );
	}
}

void Knight_specs::setPlayable( bool playable )
{
	this->playable = playable;
}

void Knight_specs::setVolume( float volume )
{
	click.setVolume( volume );
}