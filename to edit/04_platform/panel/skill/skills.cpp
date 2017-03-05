#include "skills.h"
#include <fstream>


Skills::Skills()
{
	
}

Skills::~Skills()
{
	free();
}

void Skills::free()
{
	grey.free();
	
	if( !shuriken.empty() )
	{
		for( auto &it :shuriken )
		{
			it->free();
		}
		
		shuriken.clear();
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
}



void Skills::load( int FPS )
{
	grey.setName( "skills-grey" );
	grey.load( "data/04_platform/panel/grey/grey_square.png" );
	
	curtain.setName( "skills-curtain" );
	curtain.create( grey.getWidth(), 1 );
	
	
	
	int startY = grey.getHeight() *2;
	int x = 5;

	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		shuriken.push_back( new MySprite() );
		shuriken[ shuriken.size() -1 ]->setName( "skills-shuriken" );
		shuriken[ shuriken.size() -1 ]->load( "data/04_platform/panel/skill/" +to_string( i ) +".png" );
		shuriken[ shuriken.size() -1 ]->center( x, startY +(grey.getHeight() *i) +2*i, grey.getWidth(), grey.getHeight() );
	}
	
	// file
	fstream file;
	
	// load curtain for skill vector
	file.open( "data/txt/skill/curtain.txt" );
	if( file.bad() )
	{
		printf( "Cannot load data/txt/skill/curtain.txt\n" );
	}
	else
	{
		string line;
		while( file >> line )
		{
			skills.push_back( new Skill() );
			int a = skills.size() -1;
			skills[ a ]->setPosition( x, startY +(grey.getHeight() *a) +2*a );
			skills[ a ]->setLine( FPS *strToInt( line ) );
		}
	}
	file.close();

	
	
	// load names
	file.open( "data/txt/skill/names.txt" );
	if( file.bad() )
	{
		printf( "Cannot load data/txt/skill/names.txt\n" );
	}
	else
	{
		string line;
		while( file >> line )
		{
			names.push_back( new MyText() );
			names[ names.size() -1 ]->setName( "skills-names" );
			names[ names.size() -1 ]->setFont( "data/00_loading/Jaapokki-Regular.otf", 14, 0x00, 0x00, 0x00 );
			names[ names.size() -1 ]->setText( line );
			names[ names.size() -1 ]->setPosition( x +1, skills[ names.size() -1 ]->getY() -1 );
		}
	}
	file.close();
	
	// load nr
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		nr.push_back( new MyText() );
		nr[ nr.size() -1 ]->setName( "skills-nr" );
		nr[ nr.size() -1 ]->setFont( "data/00_loading/Jaapokki-Regular.otf", 10, 0x00, 0x00, 0x00 );
		nr[ nr.size() -1 ]->setText( to_string( i ) );
		nr[ nr.size() -1 ]->setPosition( skills[ nr.size() -1 ]->getX() +grey.getWidth() -6, skills[ nr.size() -1 ]->getY() +grey.getHeight() -11 );
	}
	
	// load label_one
	label_one.setName( "skills-label_one" );
	label_one.setFont( "data/00_loading/Jaapokki-Regular.otf", 14, 0x38, 0x2E, 0x1C );
	label_one.setText( "lv" );
	
	// load label_two
	file.open( "data/txt/skill/level_current.txt" );
	if( file.bad() )
	{
		printf( "Cannot load data/txt/skill/level_current.txt\n" );
	}
	else
	{
		string line;
		int counter = AMOUNT;
		while( file >> line )
		{
			counter --;
			if( counter == 0 )
				break;
			label_two.push_back( new MyText() );
			label_two[ label_two.size() -1 ]->setName( "skills-label_two" );
			label_two[ label_two.size() -1 ]->setFont( "data/00_loading/Jaapokki-Regular.otf", 14, 0x45, 0x38, 0x23 );
			label_two[ label_two.size() -1 ]->setText( line );
			label_two[ label_two.size() -1 ]->setPosition( x +16, skills[ label_two.size() -1 ]->getY() +grey.getHeight() -16 );
		}
	}
	file.close();
}

void Skills::draw( sf::RenderWindow* &window )
{
	for( auto &it :skills )
	{
		grey.setPosition( it->getX(), it->getY() );
		window->draw( grey.get() );
		
		label_one.setPosition( it->getX() +2, it->getY() +grey.getHeight() -16 );
		window->draw( label_one.get() );
		
		curtain.setScale( 1, it->getPercent() );
		curtain.setPosition( it->getX(), it->getY() +grey.getHeight() );
		window->draw( curtain.get() );
	}
	
	for( auto &it :shuriken )
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
	
	for( auto &it :shuriken )
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
	
	for( auto &it :shuriken )
	{
		it->fadeout( v, min );
	}
}

int Skills::strToInt( string s )
{
    bool m = false;
    int tmp = 0;
    unsigned i = 0;
	
    if( s[ 0 ] == '-' )
    {
          i++;
          m = true;
    }
	
    while( i < s.size() )
    {
      tmp = 10*tmp +s[ i ] -48;
      i++;
    }
	
    return m ? -tmp : tmp;   
}