#include "02_menu/development/headdeck.h"
#include <fstream>

Headdeck::Headdeck()
{
	free();
}

Headdeck::~Headdeck()
{
	free();
}

void Headdeck::free()
{
	wallet = 0;
	change = false;
	
	line.free();
	
	if( !texts.empty() )
	{
		for( auto &it :texts )
		{
			it->free();
		}
		
		texts.clear();
	}
	
	if( !heads.empty() )
	{
		for( auto &it :heads )
		{
			it->free();
		}
		
		heads.clear();
	}
}



void Headdeck::load( int y, int screen_h )
{
	free();
	
	// Set line.
	line.setName( "headdeck-line" );
	line.create( 2, 420 );
	line.setPosition( 725, y );
	
	// Set texts.
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		texts.push_back( new MyText() );
		texts[ texts.size() -1 ]->setName( "headdeck-text nr" +to_string( i ) );
		if( i == WALLET )	texts[ texts.size() -1 ]->setFont( "data/00_loading/Jaapokki-Regular.otf", 30, 0xFF, 0xFF, 0xFF );
		else if( i == MONEY )	texts[ texts.size() -1 ]->setFont( "data/00_loading/Jaapokki-Regular.otf", 27, 0xFF, 0xD8, 0x00 );
		else				texts[ texts.size() -1 ]->setFont( "data/00_loading/Jaapokki-Regular.otf", 35, 0xFF, 0xFF, 0xFF );
	}
	texts[ TYPE ]->setText( "Type" );
	texts[ TYPE ]->setPosition( 100, y -50 );
	texts[ SPECS ]->setText( "Specs" );
	texts[ SPECS ]->setPosition( 400, y -50 );
	texts[ COST ]->setText( "Cost/Status" );
	texts[ COST ]->setPosition( 760, y -50 );
	texts[ WALLET ]->setText( "Wallet: " );
	texts[ WALLET ]->setPosition( 10, screen_h -40 );
	texts[ MONEY ]->setText( " " );
	texts[ MONEY ]->setPosition( texts[ WALLET ]->getRight() +20, screen_h -37 );
	
	// Set heads.
	for( int i = 0; i < 4; i++ )
	{
		heads.push_back( new Head() );
		heads[ i ]->load( i, 100*i +y );
	}
	
	// Reload.
	reloadText();
}

void Headdeck::draw( sf::RenderWindow* &window )
{
	for( auto &it :texts )
	{
		window->draw( it->get() );
	}
	
	for( auto &it :heads )
	{
		it->draw( window );
	}
}

void Headdeck::reloadText()
{
	fstream file;
	file.open( "data/txt/money/bank.txt" );
	if( file.bad() )
	{
		printf( "Something went wrong\n" );
	}
	else
	{
		string line;
		file >> line;
		wallet = stoi( line );
	}
	file.close();

	texts[ MONEY ]->setText( to_string( wallet ) );
	texts[ MONEY ]->reloadPosition();
	
	for( auto &it :heads )
	{
		it->reloadText();
	}
}

void Headdeck::handle( sf::Event &event )
{
	for( auto &it :heads )
	{
		if( it->getCost() <= wallet && !it->sellOut() )
		{
			it->unlock();
		}
		else
		{
			it->lock();
		}
	}
	
	for( auto &it :heads )
	{
		it->handle( event );
		if( it->sellOut() )
		{
			wallet -= it->getCost();
			texts[ MONEY ]->setText( to_string( wallet ) );
			texts[ MONEY ]->reloadPosition();
			it->makeNought();
			change = true;
			
			// save file
			fstream file;
			file.open( "data/txt/money/bank.txt", std::ios::out );
			if( file.bad() )
			{
				printf( "Cannot open file\n" );
			}
			else
			{
				file << to_string( wallet ) << "\n";
			}
			file.close();
		}
	}
}



void Headdeck::fadein( int i, int max )
{
	line.fadein( i, max );
	
	for( auto &it :texts )
	{
		it->fadein( i, max );
	}
	
	for( auto &it :heads )
	{
		it->fadein( i, max );
	}
}

void Headdeck::fadeout( int i, int min )
{
	line.fadeout( i, min );
	
	for( auto &it :texts )
	{
		it->fadeout( i, min );
	}
	
	for( auto &it :heads )
	{
		it->fadeout( i, min );
	}
}



void Headdeck::setVolume( int volume )
{
	for( auto &it :heads )
	{
		it->setVolume( volume );
	}
}

void Headdeck::turn()
{
	for( auto &it :heads )
	{
		it->turn();
	}
}



bool Headdeck::isChange()
{
	if( change )
	{
		change = false;
		return true;
	}
	
	return false;
}

void Headdeck::setWallet( int money )
{
	wallet = money;
	texts[ MONEY ]->setText( to_string( wallet ) );
	texts[ MONEY ]->reloadPosition();
}

int Headdeck::getWallet()
{
	return wallet;
}