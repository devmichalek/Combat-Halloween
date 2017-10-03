#include "lightpoint.h"
#include "own/file.h"
#include <sstream>

LightPoint::LightPoint( float x, float y )
{
	this->x = x;
	this->y = y;
	radius = 100;
	velocity = 100;
	color = sf::Color::White;
	
	if( !points.empty() )
	{
		points.clear();
	}
}

LightPoint::~LightPoint()
{
	x = 0;
	y = 0;
	radius = 0;
	velocity = 0;
	color = sf::Color::White;
	
	if( !points.empty() )
	{
		points.clear();
	}
}




LightPointVisible::LightPointVisible()
{
	free();
}

LightPointVisible::~LightPointVisible()
{
	free();
}

void LightPointVisible::free()
{
	table.free();
	button.free();
	
	if( !texts.empty() )
	{
		for( auto &it :texts )
		{
			it->free();
			delete it;
			it = NULL;
		}
	}
	
	if( !texts_value.empty() )
	{
		for( auto &it :texts_value )
		{
			it->free();
			delete it;
			it = NULL;
		}
	}
	
	if( !valueStrs.empty() )
	{
		valueStrs.clear();
	}
	
	if( !mins.empty() )
	{
		mins.clear();
	}
	
	if( !maxs.empty() )
	{
		maxs.clear();
	}
	
	if( !pressed.empty() )
	{
		pressed.clear();
	}
	
	chosen = -1;
	active = 0;
	
	type = -1;
	radius = 100;
	velocity = 100;
	color = sf::Color::White;
	
	written = "";
	arrow_counter = 0;
	arrow_line = 0.5;
	
	if( !points.empty() )
	{
		points.clear();
	}
}



void LightPointVisible::load( float screen_w, float screen_h )
{
	free();
	
	table.setIdentity( "lightPointVisible-table" );
	table.load( "images/menu/table.png" );
	table.setScale( 0.3, 0.22 );
	
	button.setIdentity( "lightPointVisible-button" );
	button.load( "images/editor/specs.png", 3 );
	button.setScale( 0.4, 0.4 );
	
	rectColor.setSize( sf::Vector2f( table.getWidth(), table.getHeight() *0.22 ) );
	rectColor.setFillColor( sf::Color::White );
	
	// Load texts.
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		texts.push_back( new MyText );
		texts[ texts.size() -1 ]->setIdentity( "lightPointVisible-texts" );
		texts[ texts.size() -1 ]->setFont( "fonts/jcandlestickextracond.ttf" );
	}
	
	// Load value texts.
	for( unsigned i = 0; i < AMOUNT_VALUE; i++ )
	{
		texts_value.push_back( new MyText );
		texts_value[ texts_value.size() -1 ]->setIdentity( "lightPointVisible-texts_value" );
		texts_value[ texts_value.size() -1 ]->setFont( "fonts/jcandlestickextracond.ttf" );
		
		pressed.push_back( false );
	}
	
	// Set strs.
	valueStrs.push_back( "FFFFFF" );
	valueStrs.push_back( "100" );
	valueStrs.push_back( "100" );
	
	// Set mins and maxs.
	mins.push_back( 100 );
	mins.push_back( 100 );
	maxs.push_back( 500 );
	maxs.push_back( 300 );
	
	// Set texts.
	texts[ CURRENT ]->setText( "CURRENT LIGHT COLOR" );
	texts[ COLOR ]->setText( "COLOR:      #" );
	texts[ RADIUS ]->setText( "RADIUS: " );
	texts[ RADIUS_UNIT ]->setText( "px" );
	texts[ VEL ]->setText( "VELOCITY: " );
	texts[ VEL_UNIT ]->setText( "px/sec" );
	texts[ ARROW ]->setText( "|" );
	
	// Set texts in texts_value
	texts_value[ COLOR_VALUE ]->setText( valueStrs[ COLOR_VALUE ] );
	texts_value[ RADIUS_VALUE ]->setText( valueStrs[ RADIUS_VALUE ]  );
	texts_value[ VEL_VALUE ]->setText( valueStrs[ VEL_VALUE ]  );
	texts_value[ LINES ]->setText( "CLICK TO DRAW PATH" );
	
	int size = 22;
	for( unsigned i = 0; i < AMOUNT; i++ )
	{
		texts[ i ]->setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
		texts[ i ]->setAlpha( 0xFF );
		texts[ i ]->setSize( size );
	}
	
	for( unsigned i = 0; i < AMOUNT_VALUE; i++ )
	{
		texts_value[ i ]->setColor( sf::Color( 0xFF, 0xFF, 0xFF ) );
		texts_value[ i ]->setAlpha( 0xFF );
		texts_value[ i ]->setSize( size );
	}
	
	// In addition.
	texts[ CURRENT ]->setSize( size +2 );
	texts_value[ LINES ]->setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
}

void LightPointVisible::handle( sf::Event& event )
{
	if( active > 0 )
	{
		if( event.type == sf::Event::MouseButtonReleased )
		{
			for( unsigned i = 0; i < pressed.size(); i++ )
			{
				pressed[ i ] = false;
			}
		}
		else if( event.type == sf::Event::MouseButtonPressed )
		{
			button.setOffset( 1 );
			
			bool collision = false;
			float mouse_x = event.mouseButton.x;
			float mouse_y = event.mouseButton.y;
			
			if( event.mouseButton.button == sf::Mouse::Left )
			{
				if( active < 2 )
				{
					for( unsigned i = 0; i < pressed.size(); i++ )
					{
						button.setPosition( table.getRight(), texts_value[ i ]->getY() +2 );
						if( button.checkCollision( mouse_x, mouse_y ) )
						{
							chosen = i;
							pressed[ i ] = true;
							if( i != LINES )	written = valueStrs[ i ];
							else
							{
								chosen = -1;
								active = 2;
							}
							collision = true;
							break;
						}
					}
				}
				
				if( table.checkCollision( mouse_x, mouse_y ) )
				{
					chosen = -1;
					collision = true;
				}
			}
			
			if( !collision )
			{
				clear();
			}
		}
		
		else if( event.type == sf::Event::TextEntered )
		{
			bool success = false;
			if( chosen == 1 )	success = isPossibleCharColor( event.text.unicode );
			else				success = isPossibleChar( event.text.unicode );
			
			if( success )
			{
				
			}
		}
		
		if( event.type == sf::Event::KeyPressed )
		{
			if( event.key.code == sf::Keyboard::BackSpace )
			{
				if( !written.empty() )
				{
					
				}
			}
			else if( event.key.code == sf::Keyboard::Return )
			{
				
			}
		}
	}
}

void LightPointVisible::draw( sf::RenderWindow* &window )
{
	if( active > 0 )
	{
		window->draw( table.get() );
		window->draw( rectColor );
		
		for( unsigned i = 0; i < texts.size(); i++ )
		{
			if( i < LINES )
			{
				texts[ i ]->setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
				if( i == chosen )
				{
					texts[ i ]->setColor( sf::Color( 0xFF, 0, 0xFF ) );
				}
			}
			
			window->draw( texts[ i ]->get() );
		}
		
		for( unsigned i = 0; i < texts_value.size(); i++ )
		{
			window->draw( texts_value[ i ]->get() );
			if( pressed [ i ] )	button.setOffset( 1 );
			else				button.setOffset( 0 );
			button.setPosition( table.getRight(), texts_value[ i ]->getY() +2 );
			window->draw( button.get() );
		}
		
		if( active == 2 )
		{
			texts_value[ LINES ]->setColor( sf::Color( 0xFF, 0, 0xFF ) );
		}
		else
		{
			texts_value[ LINES ]->setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
		}
		
		if( arrow_counter > arrow_line && chosen > 0 )
		{
			window->draw( texts[ ARROW ]->get() );
		}
		
		if( arrow_counter > arrow_line *2 )
		{
			arrow_counter = 0;
		}
	}
}

void LightPointVisible::mechanics( double elapsedTime )
{
	arrow_counter += elapsedTime;
}



void LightPointVisible::setType( int type )
{
	if( active == 0 )
	{
		active = 1;
	}
	
	this->type = type;
}

void LightPointVisible::setPosition( float x, float y )
{
	y -= table.getHeight();
	
	table.setPosition( x, y );
	
	rectColor.setPosition( sf::Vector2f( table.getX(), table.getY() -rectColor.getSize().y ) );
	texts[ CURRENT ]->setPosition( table.getX() +table.getWidth() /2 -texts[ CURRENT ]->getWidth()/2, rectColor.getPosition().y -2 );
	
	float myX = table.getX() +5;
	texts[ COLOR ]->setPosition( myX, table.getY() +5 );
	texts[ RADIUS ]->setPosition( myX, texts[ COLOR ]->getBot() +5 );
	texts[ VEL ]->setPosition( myX, texts[ RADIUS ]->getBot() +5 );
	
	texts_value[ COLOR_VALUE ]->setPosition( texts[ COLOR ]->getRight(), texts[ COLOR ]->getY() );
	texts_value[ RADIUS_VALUE ]->setPosition( texts[ COLOR ]->getRight(), texts[ RADIUS ]->getY() );
	texts_value[ VEL_VALUE ]->setPosition( texts[ COLOR ]->getRight(), texts[ VEL ]->getY() );
	texts_value[ LINES ]->setPosition( myX, texts[ VEL ]->getBot() +5 );
	
	texts[ RADIUS_UNIT ]->setPosition( table.getRight() -5 -texts[ RADIUS_UNIT ]->getWidth(), texts[ RADIUS ]->getY() );
	texts[ VEL_UNIT ]->setPosition( table.getRight() -5 -texts[ VEL_UNIT ]->getWidth(), texts[ VEL ]->getY() );
}

void LightPointVisible::setSpecs( float radius, float velocity, sf::Color color, vector <sf::Vector2f> points )
{
	this->radius = radius;
	this->velocity = velocity;
	this->color = color;
	this->points = points;
}



int LightPointVisible::getType()
{
	return type;
}

float LightPointVisible::getRadius()
{
	return radius;
}

float LightPointVisible::getVelocity()
{
	return velocity;
}

sf::Color LightPointVisible::getColor()
{
	return color;
}

vector <sf::Vector2f> LightPointVisible::getPoints()
{
	return points;
}

bool LightPointVisible::isVisible()
{
	if( active > 0 )
	{
		return true;
	}
	
	return false;
}

void LightPointVisible::clear()
{
	active = 0;
	type = -1;
	chosen = -1;
}



sf::Color LightPointVisible::getColorFromText( string line )
{
	int r, g, b;
	string red = "", green = "", blue = "";
	
	red += line[ 0 ];
	red += line[ 1 ];
	green += line[ 2 ];
	green += line[ 3 ];
	blue += line[ 4 ];
	blue += line[ 5 ];
	
    std::stringstream stream;
	
	// Set red.
    stream << red;
    stream >> std::hex >> r;
	
	// Set green.
    stream << green;
    stream >> std::hex >> g;
	
	// Set blue.
    stream << blue;
    stream >> std::hex >> b;
	
	return sf::Color( r, g, b );
}

bool LightPointVisible::isPossibleCharColor( sf::Uint8 code )
{
	if( code >= 48 && code <= 57 )	// 0 ... 9.
	{
		return true;
	}
	else if( code >= 65 && code <= 70 )	// A ... F.
	{
		return true;
	}
	else if( code >= 97 && code <= 102 )	// a ... f.
	{
		return true;
	}
	
	return false;
}

bool LightPointVisible::isPossibleChar( sf::Uint8 code )
{
	if( code >= 48 && code <= 57 )	// 0 ... 9.
	{
		return true;
	}
	
	return false;
}

void LightPointVisible::setWritten()
{
	
}