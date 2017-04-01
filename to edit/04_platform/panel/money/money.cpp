/**
    money.h
    Purpose: class Money responsible for drawing coins, coin mechanis etc.

    @author Adrian Michalek
    @version 2017.02.14
	@email adrmic98@gmail.com
*/

#include "money.h"
#include "file/file.h"

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
	
	offset = 0;
	delay = 8;
	line = 10;
	
	grey.setName( "money-grey" );
	grey.load( "data/04_platform/panel/grey/grey.png" );
	grey.setScale( 0.5, 0.5 );
	grey.setPosition( screen_w -grey.getWidth() -5, 5 );
	
	coin.setName( "money-coin" );
	coin.load( "data/04_platform/panel/coin/0.png", line );
	coin.setScale( 0.65, 0.65 );
	coin.setPosition( screen_w -coin.getWidth() -15, grey.getY() +grey.getHeight()/2 -coin.getHeight()/2 );
	
	text.setName( "money-text" );
	text.setFont( "data/00_loading/Jaapokki-Regular.otf", 32, 0xD9, 0xD9, 0xD9 );
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
	text.fadein( v, max *0.6 );
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
	sf::Uint8 max = 6;
	
	if( con::itos( bank ).size() > max )
	{
		bank = 999999;
		text.setText( con::itos( bank ) );
	}
	else
	{
		string additional = "";
		for( unsigned i = 0; i < max -con::itos( bank ).size(); i++ )
		{
			additional += '0';
		}
		
		text.setText( additional +con::itos( bank ) );
	}
	
	text.setPosition( coin.getX() -text.getWidth() -27, grey.getY() +5 );
}

void Money::saveMoney()
{
	MyFile file;
	
	file.load( "data/txt/money/bank.txt", std::ios::out );
	if( file.is_good() )
	{
		string line;
		file.get() << con::itos( bank );
	}
	
	file.free();
}

void Money::loadMoney()
{
	MyFile file;
	
	file.load( "data/txt/money/bank.txt" );
	if( file.is_good() )
	{
		string line;
		file.get() >> line;
		base = con::stoi( line );
		bank = base;
	}
	file.free();
}

void Money::add( int amount )
{
	bank += amount;
	setText();
}