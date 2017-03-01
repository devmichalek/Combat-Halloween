#include "money_panel.h"
#include <fstream>

Money_panel::Money_panel()
{
	base = 0;
	bank = 0;
	
	offset = 0;
	delay = 0;
	line = 0;
}

Money_panel::~Money_panel()
{
	free();
}

void Money_panel::free()
{
	grey.free();
	coin.free();
	text.free();
	
	base = 0;
	bank = 0;
	
	offset = 0;
	delay = 0;
	line = 0;
}

void Money_panel::reset()
{
	offset = 0;
	bank = base;
	setText();
}

void Money_panel::load( int screen_w )
{
	free();
	
	loadMoney();
	
	offset = 0;
	delay = 8;
	line = 10;
	
	grey.setName( "money_panel-grey" );
	grey.load( "data/04_platform/panel/grey/grey.png" );
	grey.setScale( 0.5, 0.5 );
	grey.setPosition( screen_w -grey.getWidth() -5, 5 );
	
	coin.setName( "money_panel-coin" );
	coin.load( "data/04_platform/panel/coin/0.png", line );
	coin.setScale( 0.65, 0.65 );
	coin.setPosition( screen_w -coin.getWidth() -15, grey.getY() +grey.getHeight()/2 -coin.getHeight()/2 );
	
	text.setName( "money_panel-text" );
	text.setFont( "data/02_menu/BADABB__.TTF", 33, 0xD9, 0xD9, 0xD9 );

	setText();
}

void Money_panel::draw( sf::RenderWindow* &window )
{
	window->draw( grey.get() );
	window->draw( text.get() );
	
	offset ++;
	if( offset == line*delay )
	{
		offset = 0;
	}
	
	coin.setOffset( offset /delay );
	window->draw( coin.get() );
}


void Money_panel::fadein( int v, int max )
{
	grey.fadein( v, max );
	coin.fadein( v, max );
	text.fadein( v, max );
}

void Money_panel::fadeout( int v, int min )
{
	grey.fadeout( v, min );
	coin.fadeout( v, min );
	text.fadeout( v, min );
}



void Money_panel::setText()
{
	sf::Uint8 max = 8;
	
	if( to_string( bank ).size() > max )
	{
		bank = 99999999;
		text.setText( to_string( bank ) );
	}
	else
	{
		string additional = "";
		for( unsigned i = 0; i < max -to_string( bank ).size(); i++ )
		{
			additional += '0';
		}
		
		text.setText( additional +to_string( bank ) );
	}
	
	text.setPosition( coin.getX() -text.getWidth() -15, grey.getY() +4 );
}

void Money_panel::saveMoney()
{
	
}

void Money_panel::loadMoney()
{
	fstream file;
	
	file.open( "data/txt/money/bank.txt" );
	if( file.bad() )
	{
		printf( "Something went wrong with data/txt/money/bank.txt\n" );
	}
	else
	{
		string line;
		file >> line;
		base = strToInt( line );
		bank = base;
	}
	
	file.close();
}

void Money_panel::add( int amount )
{
	bank += amount;
	setText();
}

int Money_panel::strToInt( string s )
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