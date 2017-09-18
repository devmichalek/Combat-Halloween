#include "hatchfoe.h"
#include "own/file.h"

Block::Block( sf::Uint8 w, sf::Uint8 n, float x, float y )
{
	this->w = w;
	this->n = n;
	this->x = x;
	this->y = y;
}

Block::~Block()
{
	w = 0;
	n = 0;
	x = 0;
	y = 0;
}

HatchFoe::HatchFoe( sf::Uint8 w, sf::Uint8 n, float x, float y )
{
	this->w = w;
	this->n = n;
	this->x = x;
	this->y = y;
	
	armour = 0;
	damage = 1;
	velocity = 10;
	heartpoints = 1;
}

HatchFoe::~HatchFoe()
{
	w = 0;
	n = 0;
	x = 0;
	y = 0;
	
	armour = 0;
	damage = 1;
	velocity = 10;
	heartpoints = 1;
	
	if( !texts.empty() )
	{
		texts.clear();
	}
}


HatchFoeVisible::HatchFoeVisible()
{
	free();
}

HatchFoeVisible::~HatchFoeVisible()
{
	free();
}

void HatchFoeVisible::free()
{
	table.free();
	infobutton.free();
	plusbutton.free();
	minusbutton.free();
	doublebutton.free();
	
	if( !minimums.empty() )
	{
		minimums.clear();
	}
	
	if( !maximums.empty() )
	{
		maximums.clear();
	}
	
	if( !features.empty() )
	{
		features.clear();
	}
	
	if( !pluspressed.empty() )
	{
		pluspressed.clear();
	}
	
	if( !minuspressed.empty() )
	{
		minuspressed.clear();
	}
	
	if( !texts.empty() )
	{
		for( auto &it :texts )
		{
			it->free();
			delete it;
			it = NULL;
		}
		
		texts.clear();
	}
	
	if( !formTexts.empty() )
	{
		for( auto &it :formTexts )
		{
			it->free();
			delete it;
			it = NULL;;
		}
		
		formTexts.clear();
	}
	
	type = -1;
	visible = false;
	wasminus = false;
}



void HatchFoeVisible::load( float screen_w, float screen_h )
{
	free();
	
	// Sprites.
	table.setIdentity( "hatchFoeVisible-table" );
	infobutton.setIdentity( "hatchFoeVisible-infobutton" );
	plusbutton.setIdentity( "hatchFoeVisible-plusbutton" );
	minusbutton.setIdentity( "hatchFoeVisible-minusbutton" );
	doublebutton.setIdentity( "hatchFoeVisible-doublebutton" );
	
	table.load( "images/menu/table.png" );
	infobutton.load( "images/editor/info.png", 3 );
	plusbutton.load( "images/menu/plus.png", 3 );
	minusbutton.load( "images/menu/minus.png", 3 );
	doublebutton.load( "images/editor/disagree.png", 3 );
	
	table.setScale( 0.25, 0.25 );
	infobutton.setScale( 0.2, 0.2 );
	plusbutton.setScale( 0.4, 0.4 );
	minusbutton.setScale( 0.4, 0.4 );
	doublebutton.setScale( 0.165, 0.165 );
	
	
	// Maximums, minimums.
	minimums.push_back( 0 );
	minimums.push_back( 1 );
	minimums.push_back( 10 );
	minimums.push_back( 1 );
	
	maximums.push_back( 995 );
	maximums.push_back( 10000 );
	maximums.push_back( 300 );
	maximums.push_back( 1000 );
	
	features.push_back( 0 );
	features.push_back( 1 );
	features.push_back( 10 );
	features.push_back( 1 );
	
	
	// Texts.
	for( unsigned i = 0; i < ADD_TEXT; i++ )
	{
		pluspressed.push_back( false );
		minuspressed.push_back( false );
		
		texts.push_back( new MyText() );
		texts[ i ]->setIdentity( "hatchFoeVisible-texts" );
		texts[ i ]->setFont( "fonts/jcandlestickextracond.ttf" );
	}
	
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		formTexts.push_back( new MyText() );
		formTexts[ i ]->setIdentity( "hatchFoeVisible-formTexts" );
		formTexts[ i ]->setFont( "fonts/jcandlestickextracond.ttf" );
	}
	
	texts[ ARMOUR ]->setText( "0" );
	texts[ DAMAGE ]->setText( "1" );
	texts[ VEL ]->setText( "10" );
	texts[ HP ]->setText( "1" );
	
	formTexts[ ARMOUR ]->setText( "armour: " );
	formTexts[ DAMAGE ]->setText( "damage: " );
	formTexts[ VEL ]->setText( "velocity: " );
	formTexts[ HP ]->setText( "heartpoints: " );
	formTexts[ ADD_TEXT ]->setText( "click to add comment" );
	
	int size = 22;
	for( unsigned i = 0; i < ADD_TEXT; i++ )
	{
		texts[ i ]->setAlpha( 0xFF );
		texts[ i ]->setSize( size );
	}
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		formTexts[ i ]->setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
		formTexts[ i ]->setAlpha( 0xFF );
		formTexts[ i ]->setSize( size );
	}
}

void HatchFoeVisible::handle( sf::Event& event )
{
	if( visible )
	{
		if( event.type == sf::Event::MouseButtonReleased )
		{
			for( unsigned i = 0; i < pluspressed.size(); i++ )
			{
				pluspressed[ i ] = false;
				minuspressed[ i ] = false;
			}
		}
		
		if( event.type == sf::Event::MouseButtonPressed )
		{
			bool collision = false;
			float mouse_x = event.mouseButton.x;
			float mouse_y = event.mouseButton.y;
			
			if( event.mouseButton.button == sf::Mouse::Left )
			{
				for( unsigned i = 0; i < texts.size(); i++ )
				{
					minusbutton.setPosition( table.getRight(), texts[ i ]->getY() );
					plusbutton.setPosition( minusbutton.getRight(), texts[ i ]->getY() );
					doublebutton.setPosition( plusbutton.getRight(), texts[ i ]->getY() );
					
					if( minusbutton.checkCollision( mouse_x, mouse_y ) )
					{
						collision = true;
						wasminus = true;
						minuspressed[ i ] = true;
						break;
					}
					else if( plusbutton.checkCollision( mouse_x, mouse_y ) )
					{
						collision = true;
						wasminus = false;
						pluspressed[ i ] = true;
						break;
					}
					else if( doublebutton.checkCollision( mouse_x, mouse_y ) )
					{
						collision = true;
						// printf( "%d\n", i );
						
						if( wasminus )	features[ i ] /= 2;
						else			features[ i ] *= 2;
						
						if( features[ i ] > maximums[ i ] )			features[ i ] = maximums[ i ];
						else if( features[ i ] < minimums[ i ] )	features[ i ] = minimums[ i ];
						
						texts[ i ]->setText( con::itos( static_cast <int> (features[ i ]) ) );
						texts[ i ]->setPosition( formTexts[ HP ]->getRight() +3, formTexts[ i ]->getY() );
						break;
					}
				}
			}
			
			if( table.checkCollision( mouse_x, mouse_y ) )
			{
				collision = true;
			}
			
			if( !collision )
			{
				clear();
			}
		}
	}
}

void HatchFoeVisible::draw( sf::RenderWindow* &window )
{
	if( visible )
	{
		for( unsigned i = 0; i < pluspressed.size(); i++ )
		{
			if( pluspressed[ i ] )
			{
				if( features[ i ] < maximums[ i ] )
				{
					features[ i ] += 0.1;
					if( features[ i ] > maximums[ i ] )
					{
						features[ i ] = maximums[ i ];
					}
					
					texts[ i ]->setText( con::itos( static_cast <int> (features[ i ]) ) );
					texts[ i ]->setPosition( formTexts[ HP ]->getRight() +3, formTexts[ i ]->getY() );
				}
			}
			else if( minuspressed[ i ] )
			{
				if( features[ i ] > minimums[ i ] )
				{
					features[ i ] -= 0.1;
					if( features[ i ] < minimums[ i ] )
					{
						features[ i ] = minimums[ i ];
					}
					
					texts[ i ]->setText( con::itos( static_cast <int> (features[ i ]) ) );
					texts[ i ]->setPosition( formTexts[ HP ]->getRight() +3, formTexts[ i ]->getY() );
				}
			}
		}
		
		window->draw( table.get() );
		window->draw( infobutton.get() );
		
		for( unsigned i = 0; i < formTexts.size(); i++ )
		{
			window->draw( formTexts[ i ]->get() );
		}
		
		for( unsigned i = 0; i < texts.size(); i++ )
		{
			window->draw( texts[ i ]->get() );
			
			minusbutton.setOffset( 0 );
			if( minuspressed[ i ] )	minusbutton.setOffset( 1 );
			minusbutton.setPosition( table.getRight(), texts[ i ]->getY() );
			window->draw( minusbutton.get() );
			
			plusbutton.setOffset( 0 );
			if( pluspressed[ i ] )	plusbutton.setOffset( 1 );
			plusbutton.setPosition( minusbutton.getRight(), texts[ i ]->getY() );
			window->draw( plusbutton.get() );
			
			doublebutton.setPosition( plusbutton.getRight(), texts[ i ]->getY() );
			window->draw( doublebutton.get() );
		}
	}
}



bool HatchFoeVisible::isVisible()
{
	return visible;
}

void HatchFoeVisible::clear()
{
	visible = false;
}



int HatchFoeVisible::getType()
{
	return type;
}

void HatchFoeVisible::setType( int type )
{
	this->type = type;
}

void HatchFoeVisible::setPosition( float x, float y )
{
	visible = true;
	
	// x = middle of foe
	// y = y of foe
	
	table.setPosition( x -table.getWidth()/2,y -table.getHeight() );
	
	// Setting form texts.
	float border = 3;
	float formTextX = table.getX() +border;
	float formTextY = table.getY() +border;
	
	for( unsigned i = 0; i < texts.size(); i++ )
	{
		formTexts[ i ]->setPosition( formTextX, formTextY +(formTexts[ ARMOUR ]->getHeight() +border)*i );
	}
	
	for( unsigned i = 0; i < texts.size(); i++ )
	{
		texts[ i ]->setPosition( formTexts[ HP ]->getRight() +border, formTexts[ i ]->getY() );
	}
	
	// Buttons.
	formTexts[ ADD_TEXT ]->setPosition( formTextX, table.getBot() -formTexts[ ADD_TEXT ]->getHeight() -border*3 );
	infobutton.setPosition( table.getRight(), formTexts[ ADD_TEXT ]->getY() );
}

void HatchFoeVisible::setFeatures( float a, float d, float v, float h )
{
	features[ ARMOUR ] = a;
	features[ DAMAGE ] = d;
	features[ VEL ] = v;
	features[ HP ] = h;
	
	texts[ ARMOUR ]->setText( con::itos( static_cast <int> (a) ) );
	texts[ DAMAGE ]->setText( con::itos( static_cast <int> (d) ) );
	texts[ VEL ]->setText( con::itos( static_cast <int> (v) ) );
	texts[ HP ]->setText( con::itos( static_cast <int> (h) ) );
}



float HatchFoeVisible::getArmour()
{
	return features[ ARMOUR ];
}

float HatchFoeVisible::getDamage()
{
	return features[ DAMAGE ];
}

float HatchFoeVisible::getVelocity()
{
	return features[ VEL ];
}

float HatchFoeVisible::getHeartpoints()
{
	return features[ HP ];
}