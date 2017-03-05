#include "02_menu/development/development.h"
#include <fstream>
// #include <iomanip>

Development::Development()
{
	bank = 0;
}

Development::~Development()
{
	free();
}

void Development::free()
{
	if( !develops.empty() )
	{
		for( auto &it :develops )
		{
			it->free();
		}
		
		develops.clear();
	}
	
	if( !levels.empty() )
	{
		levels.clear();
	}
	
	if( !values.empty() )
	{
		values.clear();
	}
	
	if( !costs.empty() )
	{
		costs.clear();
	}
	
	bank = 0;
	
	skill.free();
	level.free();
	value.free();
	upgrade.free();
	
	bank_text.free();
	money.free();
}



void Development::load( int bot, int screen_h )
{
	free();
	
	int space = 70;
	int max = 6;
	
	// set actual levels
	fstream file;
	file.open( "data/txt/skill/level_current.txt" );
	if( file.bad() )
	{
		printf( "Cannot load data/txt/skill/level_current.txt\n" );
	}
	else
	{
		string line;
		while( file >> line )
		{
			levels.push_back( stof( line ) );
		}
	}
	file.close();
	
	// set actual values
	file.open( "data/txt/skill/skill_values.txt" );
	if( file.bad() )
	{
		printf( "Cannot load data/txt/skill/skill_values.txt\n" );
	}
	else
	{
		string line;
		while( file >> line )
		{
			values.push_back( stof( line ) );
		}
	}
	file.close();
	
	
	// load bank
	file.open( "data/txt/money/bank.txt" );
	if( file.bad() )
	{
		printf( "Cannot load data/txt/money/bank.txt\n" );
	}
	else
	{
		string line;
		file >> line;
		bank = stof( line );
	}
	file.close();
	
	// set costs
	file.open( "data/txt/skill/skill_costs.txt" );
	if( file.bad() )
	{
		printf( "Cannot load data/txt/skill/skill_costs.txt\n" );
	}
	else
	{
		string line;
		while( file >> line )
		{
			costs.push_back( stof( line ) );
		}
	}
	file.close();
	
	int main_x = 80;
	
	for( int i = 0; i < max; i++ )
	{
		develops.push_back( new Develop() );
		develops[ develops.size() -1 ]->load( main_x, i, bot +( i*space ) );
		develops[ develops.size() -1 ]->setActual( levels[ i ], multiply( i ) );
		develops[ develops.size() -1 ]->setCost( multiplyCost( i ) );
	}
	
	
	// set other stuff
	int our_bot = bot -80;
	skill.setName( "development-skill" );
	skill.setFont( "data/00_loading/Jaapokki-Regular.otf", 35, 255, 255, 255 );
	skill.setText( "Skill" );
	skill.setPosition( main_x, our_bot );
	
	level.setName( "development-level" );
	level.setFont( "data/00_loading/Jaapokki-Regular.otf", 35, 255, 255, 255 );
	level.setText( "Level" );
	level.setPosition( skill.getRight() +240, our_bot );
	
	value.setName( "development-value" );
	value.setFont( "data/00_loading/Jaapokki-Regular.otf", 35, 255, 255, 255 );
	value.setText( "Value" );
	value.setPosition( level.getRight() +30, our_bot );
	
	upgrade.setName( "development-upgrade" );
	upgrade.setFont( "data/00_loading/Jaapokki-Regular.otf", 35, 255, 255, 255 );
	upgrade.setText( "Upgrade/Cost" );
	upgrade.setPosition( value.getRight() +140, our_bot );
	
	bank_text.setName( "development-bank_text" );
	bank_text.setFont( "data/00_loading/Jaapokki-Regular.otf", 30, 255, 255, 255 );
	bank_text.setText( "Bank: " );
	bank_text.setPosition( 10, screen_h -40 );
	
	money.setName( "development-money" );
	money.setFont( "data/00_loading/Jaapokki-Regular.otf", 27, 255, 255, 255 );
	money.setText( to_string( bank ) );
	money.setColor( 0xFF, 0xD8, 0x00 );
	money.setPosition( bank_text.getRight() +20, screen_h -37 );
}

void Development::draw( sf::RenderWindow* &window )
{
	window->draw( skill.get() );
	window->draw( level.get() );
	window->draw( value.get() );
	window->draw( upgrade.get() );
	window->draw( bank_text.get() );
	window->draw( money.get() );
	
	for( auto &it :develops )
	{
		it->draw( window );
	}
}

void Development::handle( sf::Event &event )
{
	for( unsigned i = 0; i < develops.size(); i++ )
	{
		if( develops[ i ]->ableToUpgrade( bank ) )
		{
			develops[ i ]->handle( event );
			if( develops[ i ]->getLevel() != levels[ i ] )
			{
				levels[ i ] = develops[ i ]->getLevel();
				bank -= develops[ i ]->getCost();
				develops[ i ]->setCost( multiplyCost( i ) );
				develops[ i ]->setActual( levels[ i ], multiply( i ) );
				
				money.setText( to_string( bank ) );
				money.reloadPosition();
				
				// save file
				
				break;
			}
		}
	}
}



void Development::fadein( int i, int max )
{
	skill.fadein( i, max );
	level.fadein( i, max );
	value.fadein( i, max );
	upgrade.fadein( i, max );
	
	bank_text.fadein( i, max );
	money.fadein( i, max );
	
	for( auto &it :develops )
	{
		it->fadein( i, max );
	}
}

void Development::fadeout( int i, int min )
{
	skill.fadeout( i, min );
	level.fadeout( i, min );
	value.fadeout( i, min );
	upgrade.fadeout( i, min );
	
	bank_text.fadeout( i, min );
	money.fadeout( i, min );
	
	for( auto &it :develops )
	{
		it->fadeout( i, min );
	}
}

string Development::multiply( int which )
{
	float value = values[ which ];
	if( levels[ which ] == 0 )
	{
		value = 0;
	}
	
	for( int i = 0; i < levels[ which ] -1; i++ )
	{
		switch( which )
		{
			case 0:	value += (value *value) /3;		break;
			case 1:	value = value *1.8;				break;
			case 2:	value += 10;					break;
			case 3:	value += 10;					break;
			case 4:	value += (value *value) /2.3;	break;
			case 5:	value += (value *value) /3.8;	break;
		}
	}
	
	// precision 3
	string base = to_string( value );
	string newstr = "";
	int counter = -1;
	for( unsigned i = 0; i < base.size(); i++ )
	{
		if( counter == 0 )
		{
			break;
		}
		
		newstr += base[ i ];
		if( base[ i ] == '.' )
		{
			counter = 3;
		}
		
		if( counter > 0 )
		{
			counter --;
		}
	}
	
	if( newstr[ newstr.size() -1 ] == '0' )
	{
		newstr.erase( newstr.size() -1 );
	}
	
	if( newstr[ newstr.size() -1 ] == '0' )
	{
		newstr.erase( newstr.size() -1 );
	}
	
	if( newstr[ newstr.size() -1 ] == '.' )
	{
		newstr.erase( newstr.size() -1 );
		
	}
	
	return newstr;
}

float Development::multiplyCost( int which )
{
	float value = costs[ which ];
	
	for( int i = 0; i < levels[ which ]; i++ )
	{
		value *= 2.1;
	}
	
	return value;
}

void Development::setVolume( int volume )
{
	for( auto &it :develops )
	{
		it->setVolume( volume );
	}
}

void Development::turn()
{
	for( auto &it :develops )
	{
		it->turn();
	}
}