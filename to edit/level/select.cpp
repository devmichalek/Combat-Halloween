#include "select.h"
#include <stdio.h>
#include <fstream>

Select::Select()
{
	money = 0;
	level = NULL;
	nr = 0;
	
	counter = 0;
}

Select::~Select()
{
	money = 0;
	counter = 0;

	if( level != NULL )
	{
		delete [] level;
		level = NULL;
		
		nr = 0;
	}
	
	level_name.free();
	cost.free();
	coin.free();
	wallet.free();
	info.free();
}

void Select::load( int screen_w, int screen_h )
{
	// load money
	fstream file;
	file.open( "level select/money.map", std::ios::in );
	if( file.bad() )
	{
		printf( "Can not load file %s\n", "level select/money.map" );
		money = 0;
	}
	else
	{
		file >> money;
	}
	file.close();
	
	// load open levels
	file.open( "level select/levels.map", std::ios::in );
	if( file.bad() )
	{
		printf( "Can not load file %s\n", "level select/levels.map" );
	}
	else
	{
		int box;
		while( file >> box )
		{
			open.push_back( box );
		}
	}
	file.close();
	
	nr = 16;
	level = new Level [ nr ];
	
	level[ 0 ].load( "Alone", 25 );
	level[ 1 ].load( "First Time Again", 35 );
	level[ 2 ].load( "Welcome to the Tombs", 60 );	// groby
	level[ 3 ].load( "Claimed", 90 );
	
	level[ 4 ].load( "Too Far Gone", 220 );
	level[ 5 ].load( "The Distance", 320 );
	level[ 6 ].load( "After", 480 );
	level[ 7 ].load( "Infected", 800 );
	
	level[ 8 ].load( "Conquer", 1600 );
	level[ 9 ].load( "Dead Weight", 3400 );
	level[ 10 ].load( "Welcome to the Jungle", 5700 );
	level[ 11 ].load( "Crossed", 9000 );
	
	level[ 12 ].load( "The Next World", 21000 );
	level[ 13 ].load( "No Way Out", 62000 );
	level[ 14 ].load( "Start to Finish", 73200 );
	level[ 15 ].load( "Last Day on Earth", 240000 );
	
	
	int wPos = ( screen_w - ( level[ 0 ].getWidth()*4 ) -80*3 ) / 2;
	int hei = 2;
	level[ 0 ].setXY( wPos, 240 );
	
	for( int i = 1; i < nr; i++ )
	{
		if( i%4 == 0 )
		{
			hei = i/4 +2;
			level[ i ].setXY( wPos, 120*hei );
		}
		else if( i < 4 )
			level[ i ].setXY( level[ i -1 ].getX() + level[ i -1 ].getWidth() + 80, 240*(hei-1) );
		else
			level[ i ].setXY( level[ i -1 ].getX() + level[ i -1 ].getWidth() + 80, 120*hei );	
	}
	
	// open levels
	for( unsigned i = 0; i < open.size(); i++ )
	{
		level[ open[ i ] ].unlock();
	}
	
	level_name.setID( "select-level_name" );
	level_name.setFont( "intro/Jaapokki-Regular.otf", 25, 0xFF, 0xFF, 0xFF );
	level_name.setText( "Name: -" );
	level_name.setPosition( 10, 10 );
	
	cost.setID( "select-cost" );
	cost.setFont( "intro/Jaapokki-Regular.otf", 25, 0xFF, 0xFF, 0xFF );
	cost.setText( "Cost: 0" );
	cost.setPosition( 10, level_name.getBot() + 10 );
	
	coin.setName( "select-coin" );
	coin.load( "level select/coin.png" );
	coin.setScale( 0.7, 0.7 );
	coin.setPosition( cost.getRight() + 10, cost.getTop() );
	
	info.setID( "select-info" );
	info.setFont( "intro/Jaapokki-Regular.otf", 25, 0xFF, 0xFF, 0xFF );
	info.setText( "Info: -" );
	info.setPosition( 500, 10 );
	
	wallet.setID( "select-wallet" );
	wallet.setFont( "intro/Jaapokki-Regular.otf", 25, 0xFF, 0xFF, 0xFF );
	wallet.setText( "Wallet: "  + to_string( money ) );
	wallet.setPosition( 500, info.getBot() + 10 );
}

void Select::draw( sf::RenderWindow* &window )
{
	for( int i = 0; i < nr; i++ )
	{
		level[ i ].draw( window );
	}
	
	window->draw( level_name.get() );
	window->draw( cost.get() );
	window->draw( info.get() );
	window->draw( wallet.get() );
	
	coin.setPosition( wallet.getRight() + 10, wallet.getTop() );
	window->draw( coin.get() );
	coin.setPosition( cost.getRight() + 10, cost.getTop() );
	window->draw( coin.get() );
}

void Select::handle( sf::Event &event )
{
	level_name.setText( "Name: -" );
	cost.setText( "Cost: 0" );
	info.setText( "Info: -" );
	
	for( int i = 0; i < nr; i++ )
	{
		if( level[ i ].handle( event, money ) == 1 )
		{
			level_name.setText( "Name: " + level[ i ].getName() );
			cost.setText( "Cost: " + to_string( level[ i ].getCost() ) );
			
			if( level[ i ].getCost() <= money )
				info.setText( "Info: Click to buy!" );
			else
				info.setText( "Info: You don't have enough money!" );
		}
		else if( level[ i ].handle( event, money ) == 2 )
		{
			level_name.setText( "Name: " + level[ i ].getName() );
			if( level[ i ].getCost() == 0 )
				info.setText( "Info: You bought it!" );
			else if( level[ i ].getCost() > money )
			{
				info.setText( "Info: You don't have enough money!" );
				cost.setText( "Cost: " + to_string( level[ i ].getCost() ) );
			}
				
		}
	}
	
	level_name.reloadPosition();
	cost.reloadPosition();
	coin.setPosition( cost.getRight() + 10, level_name.getBot() + 9 );
	info.reloadPosition();
	
	wallet.setText( "Wallet: "  + to_string( money ) );
	wallet.reloadPosition();
}

	
void Select::fadein( int i, int max )
{
	level[ counter ].fadein( i +12, max );
	
	if( level[ counter ].getAlpha() == 255 && counter <= nr -1 )
		counter ++;
		
	level_name.fadein( i, max );
	cost.fadein( i, max );
	coin.fadein( i, max );
	info.fadein( i, max );
	wallet.fadein( i, max );
}

void Select::fadeout( int i, int min )
{
	for( int j = 0; j < nr; j++ )
	{
		level[ j ].fadeout( i, min );
	}
	
	level_name.fadeout( i, min );
	cost.fadeout( i, min );
	coin.fadeout( i, min );
	info.fadeout( i, min );
	wallet.fadeout( i, min );
}

	
void Select::turn()
{
	for( int j = 0; j < nr; j++ )
	{
		level[ j ].turn();
	}
}

void Select::setVolume( sf::Uint8 volume )
{
	for( int j = 0; j < nr; j++ )
	{
		level[ j ].setVolume( volume );
	}
}
