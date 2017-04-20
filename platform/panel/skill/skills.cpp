/**
    skills.h
    Purpose: class Skills as a skills panel in play state.

    @author Adrian Michalek
    @version 2016.03.06
	@email adrmic98@gmail.com
*/

#include "skills.h"
#include "file/file.h"


Skills::Skills()
{
	free();
}

Skills::~Skills()
{
	free();
}

void Skills::free()
{
	grey.free();
	
	if( !pictures.empty() )
	{
		for( auto &it :pictures )
		{
			it->free();
		}
		
		pictures.clear();
	}

	curtain.free();
	label_one.free();
	
	if( !label_two.empty() )
	{
		for( auto &it :label_two )
		{
			it->free();
		}
		
		label_two.clear();
	}
	
	if( !names.empty() )
	{
		for( auto &it :names )
		{
			it->free();
		}
		
		names.clear();
	}
	
	if( !nr.empty() )
	{
		for( auto &it :nr )
		{
			it->free();
		}
		
		nr.clear();
	}
	
	if( !skills.empty() )
	{
		for( auto &it :skills )
		{
			it->free();
		}
		
		skills.clear();
	}
	
	if( !actions.empty() )
	{
		actions = std::stack <int> ();
	}
	
	if( !levels.empty() )
	{
		levels.clear();
	}
	
	if( !gold.empty() )
	{
		gold.clear();
	}
	
	skill_effect.free();
}

void Skills::reset()
{
	if( !skills.empty() )
	{
		for( auto &it :skills )
		{
			it->reset();
		}
	}
	
	skill_effect.reset();
}



void Skills::load( unsigned FPS, int screen_w, int screen_h )
{
	free();
	
	skill_effect.load( FPS, screen_w, screen_h );
	
	grey.setName( "skills-grey" );
	grey.load( "data/platform/panel/grey/grey_square.png" );
	
	curtain.setName( "skills-curtain" );
	curtain.create( grey.getWidth(), 1 );
	curtain.setColor( sf::Color( 0x00, 0x00, 0x00 ) );
	
	
	int startY = grey.getHeight() *3;
	int x = 5;

	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		pictures.push_back( new MySprite() );
		pictures[ pictures.size() -1 ]->setName( "skills-shuriken" );
		pictures[ pictures.size() -1 ]->load( "data/platform/panel/skill/" +con::itos( i ) +".png" );
		pictures[ pictures.size() -1 ]->center( x, startY +(grey.getHeight() *i) +2*i, grey.getWidth(), grey.getHeight() );
	}
	
	MyFile file;
	// Load curtain txt.
	file.load( "data/txt/skill/curtain.txt" );
	if( file.is_good() )
	{
		string line;
		while( file.get() >> line )
		{
			skills.push_back( new Skill() );
			int size = skills.size() -1;
			skills[ size ]->setPosition( x, startY +(grey.getHeight() *size) +2*size );
			skills[ size ]->setLine( static_cast <int> (static_cast <float> (FPS) *con::stof( line.c_str() )) );
			// printf( "SKILLS. %d\n", static_cast <int> (static_cast <float> (FPS) *con::stof( line )) );
		}
	}
	file.free();

	
	
	// Load names.
	file.load( "data/txt/skill/skill_name_shortcut.txt" );
	if( file.is_good() )
	{
		string line;
		while( file.get() >> line )
		{
			names.push_back( new MyText() );
			names[ names.size() -1 ]->setName( "skills-names" );
			names[ names.size() -1 ]->setFont( "data/initialization/Jaapokki-Regular.otf", 14, 0x00, 0x00, 0x00 );
			names[ names.size() -1 ]->setText( line );
			names[ names.size() -1 ]->setPosition( x +1, skills[ names.size() -1 ]->getY() -1 );
		}
	}
	file.free();
	
	
	// Load nr.
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		nr.push_back( new MyText() );
		nr[ nr.size() -1 ]->setName( "skills-nr" );
		nr[ nr.size() -1 ]->setFont( "data/initialization/Jaapokki-Regular.otf", 10, 0x00, 0x00, 0x00 );
		if( i > 1 )
			nr[ nr.size() -1 ]->setText( con::itos( i -1 ) );
		else
			nr[ nr.size() -1 ]->setText( " " );
		nr[ nr.size() -1 ]->setPosition( skills[ nr.size() -1 ]->getX() +grey.getWidth() -6, skills[ nr.size() -1 ]->getY() +grey.getHeight() -11 );
	}
	
	// Load label_one.
	label_one.setName( "skills-label_one" );
	label_one.setFont( "data/initialization/Jaapokki-Regular.otf", 14, 0x38, 0x2E, 0x1C );
	label_one.setText( "lv" );
	
	// Load max levels temporary
	vector <string> max_levels;
	file.load( "data/txt/skill/skill_max.txt" );
	if( file.is_good() )
	{
		string line;
		while( file.get() >> line )
		{
			max_levels.push_back( line );
		}
	}
	file.free();
	
	// Load label_two.
	file.load( "data/txt/skill/level_current.txt" );
	if( file.is_good() )
	{
		string line;
		int counter = 0;
		while( file.get() >> line )
		{
			levels.push_back( con::stof( line.c_str() ) );
			label_two.push_back( new MyText() );
			label_two[ label_two.size() -1 ]->setName( "skills-label_two" );
			label_two[ label_two.size() -1 ]->setFont( "data/initialization/Jaapokki-Regular.otf", 14, 0x45, 0x38, 0x23 );
			if( line == max_levels[ counter ] )
			{
				gold.push_back( true );
				label_two[ label_two.size() -1 ]->setText( " " );
			}
			else
			{
				gold.push_back( false );
				label_two[ label_two.size() -1 ]->setText( line );
			}
			
			label_two[ label_two.size() -1 ]->setPosition( x +16, skills[ label_two.size() -1 ]->getY() +grey.getHeight() -16 );
			counter ++;
		}
	}
	file.free();
	max_levels.clear();
	
	actions.push( USUAL );
}

void Skills::draw( sf::RenderWindow* &window )
{
	skill_effect.draw( window );
	
	for( unsigned i = 0; i < skills.size(); i++ )
	{
		if( gold[ i ] )
		{
			grey.setColor( sf::Color( 0xFF, 0xD8, 0x00 ) );
		}
		else
		{
			grey.setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
		}
		
		grey.setPosition( skills[ i ]->getX(), skills[ i ]->getY() );
		window->draw( grey.get() );
		
		if( !gold[ i ] )
		{
			label_one.setPosition( skills[ i ]->getX() +2, skills[ i ]->getY() +grey.getHeight() -16 );
			window->draw( label_one.get() );
		}
		
		curtain.setScale( 1, -skills[ i ]->getPercent( grey.getHeight() ) );
		curtain.setPosition( skills[ i ]->getX(), skills[ i ]->getY() +grey.getHeight() );
		window->draw( curtain.get() );
	}
	
	for( auto &it :pictures )
	{
		window->draw( it->get() );
	}
	
	for( auto &it :label_two )
	{
		window->draw( it->get() );
	}

	for( auto &it :names )
	{
		window->draw( it->get() );
	}
	
	for( auto &it :nr )
	{
		window->draw( it->get() );
	}
}



void Skills::fadein( int v, int max )
{
	grey.fadein( v, max /2 );
	curtain.fadein( v, max /2 );
	label_one.fadein( v, max /3 );
	
	for( auto &it :label_two )
	{
		it->fadein( v, max /3 );
	}
	
	for( auto &it :names )
	{
		it->fadein( v, max /3 );
	}
	
	for( auto &it :nr )
	{
		it->fadein( v, max /3 );
	}
	
	for( auto &it :pictures )
	{
		it->fadein( v, max /2 );
	}
}

void Skills::fadeout( int v, int min )
{
	grey.fadeout( v, min );
	curtain.fadeout( v, min );
	label_one.fadeout( v, min );
	
	for( auto &it :label_two )
	{
		it->fadeout( v, min );
	}
	
	for( auto &it :names )
	{
		it->fadeout( v, min );
	}
	
	for( auto &it :nr )
	{
		it->fadeout( v, min );
	}
	
	for( auto &it :pictures )
	{
		it->fadeout( v, min );
	}
}



int Skills::getTop()
{
	if( actions.empty() )
	{
		actions.push( USUAL );
	}
	
	int top = actions.top();

	if( top >= SLOW )
	{
		skills[ top ]->used();
		top --;
	}
	else if( top == USUAL )
	{
		skills[ USUAL ]->isAble();
		skills[ USUAL ]->used();
	}
	
	actions.pop();
	
	return top;
}

void Skills::swordUsed()
{
	actions.push( SWORD );
	skills[ SWORD ]->isAble();
	skills[ SWORD ]->used();
	actions.pop();
}

void Skills::mechanics()
{
	sf::Uint8 num = 26;
	sf::Uint8 numpad = 75;
	
	for( unsigned i = SLOW; i < AMOUNT; i++ )
	{
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key( num +i -1 ) ) ||
		sf::Keyboard::isKeyPressed( sf::Keyboard::Key( numpad +i -1 ) ) )
		{
			if( skills[ i ]->isAble() && levels[ i ] > 0  )
			{
				skill_effect.run( i -2 );
				actions.push( i );
			}
		}
	}
	
	for( auto &it :skills )
	{
		it->mechanics();
	}
}