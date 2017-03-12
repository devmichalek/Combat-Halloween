/**
    money.h
    Purpose: class Money responsible for drawing coins, coin mechanis etc.

    @author Adrian Michalek
    @version 2017.02.14
	@email adrmic98@gmail.com
*/

#include "money.h"
#include <fstream>

Money::Money()
{
	free();
}

Money::~Money()
{
	free();
}

void Money::free()
{
	text.free();
	grey.free();
	coin.free();
	
	base = 0;
	bank = 0;
	
	offset = 0;
	delay = 0;
	line = 0;
}

void Money::reset()
{
	offset = 0;
	bank = base;
	setText();
}



void Money::load( int screen_w )
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
	text.setFont( "data/04_platform/panel/coin/Silver Age Queens.ttf", 28, 0xD9, 0xD9, 0xD9 );

	setText();
}

void Money::draw( sf::RenderWindow* &window )
{
	window->draw( text.get() );
	window->draw( grey.get() );
	
	offset ++;
	if( offset == line*delay )
	{
		offset = 0;
	}
	
	coin.setOffset( offset /delay );
	window->draw( coin.get() );
}


void Money::fadein( int v, int max )
{
	text.fadein( v, max /2 );
	grey.fadein( v, max /2 );
	coin.fadein( v, max /2 );
}

void Money::fadeout( int v, int min )
{
	grey.fadeout( v, min );
	coin.fadeout( v, min );
	text.fadeout( v, min );
}



void Money::setText()
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
	
	text.setPosition( coin.getX() -text.getWidth() -15, grey.getY() +10 );
}

void Money::saveMoney()
{
	fstream file;
	
	string path = "data/txt/money/bank.txt";
	file.open( path, std::ios::out );
	if( file.bad() )
	{
		printf( "Something went wrong with %s\n", path.c_str() );
	}
	else
	{
		string line;
		file << to_string( bank );
	}
	
	file.close();
}

void Money::loadMoney()
{
	fstream file;
	
	string path = "data/txt/money/bank.txt";
	file.open( path );
	if( file.bad() )
	{
		printf( "Something went wrong with %s\n", path.c_str() );
	}
	else
	{
		string line;
		file >> line;
		base = stoi( line );
		bank = base;
	}
	
	file.close();
}

void Money::add( int amount )
{
	bank += amount;
	setText();
}