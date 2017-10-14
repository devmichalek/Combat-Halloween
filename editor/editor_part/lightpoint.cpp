#include "lightpoint.h"
#include "own/file.h"
#include <sstream>

LightPoint::LightPoint( float x, float y )
{
	this->x = x;
	this->y = y;
	radius = 100;
	velocity = 50;
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
	minusbutton.free();
	deletebutton.free();
	
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
	velocity = 50;
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
	
	minusbutton.setIdentity( "lightPointVisible-minusbutton" );
	minusbutton.load( "images/menu/minus.png", 3 );
	minusbutton.setScale( 0.4, 0.4 );
	
	deletebutton.setIdentity( "lightPointVisible-deletebutton" );
	deletebutton.load( "images/editor/disagree.png", 3 );
	deletebutton.setScale( 0.17, 0.17 );
	
	rectColor.setSize( sf::Vector2f( table.getWidth() /7, table.getHeight() /5 ) );
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
	valueStrs.push_back( "50" );
	
	// Set mins and maxs.
	mins.push_back( 50 );
	mins.push_back( 20 );
	maxs.push_back( 300 );
	maxs.push_back( 100 );
	
	// Set texts.
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
	texts_value[ LINES ]->setText( "PATH MANIPULATION" );
	
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
	texts_value[ LINES ]->setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
	
	// Set vertex.
	vertex.setPrimitiveType( sf::Lines );
}

void LightPointVisible::handle( sf::Event& event, float add_x, float add_y )
{
	if( active > 0 )
	{
		if( event.type == sf::Event::MouseButtonReleased )
		{
			deletebutton.setOffset( 0 );
			minusbutton.setOffset( 0 );
			
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
				if( chosen != -1 )
				{
					textEntered();
				}
				
				if( table.checkCollision( mouse_x, mouse_y ) )
				{
					chosen = -1;
					active = 1;
					collision = true;
				}
				
				if( active < 2 )
				{
					for( unsigned i = 0; i < pressed.size(); i++ )
					{
						button.setPosition( table.getRight(), texts_value[ i ]->getY() +2 );
						if( button.checkCollision( mouse_x, mouse_y ) )
						{
							pressed[ i ] = true;
							if( i != LINES )
							{
								texts[ ARROW ]->setPosition( texts_value[ i ]->getRight(), texts_value[ i ]->getY() );
								chosen = i;
								written = valueStrs[ i ];
							}
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
				else
				{
					if( deletebutton.checkCollision( mouse_x, mouse_y ) )
					{
						deletebutton.setOffset( 1 );
						if( !points.empty() )
						{
							points.clear();
						}
					}
					else if( minusbutton.checkCollision( mouse_x, mouse_y ) )
					{
						minusbutton.setOffset( 1 );
						if( !points.empty() )
						{
							points.pop_back();
						}
					}
					else
					{
						points.push_back( sf::Vector2f( mouse_x -add_x, mouse_y -add_y ) );
					}
				}
			}
			
			if( !collision && active == 1 )
			{
				clear();
			}
		}
		
		if( chosen != -1 )
		{
			if( event.type == sf::Event::TextEntered )
			{
				bool success = false;
				if( chosen == COLOR_VALUE )	success = isPossibleCharColor( event.text.unicode );
				else						success = isPossibleChar( event.text.unicode );
				
				if( success )
				{
					if( chosen == COLOR_VALUE && written.size() < 6 )
					{
						written += event.text.unicode;
						std::transform( written.begin(), written.end(), written.begin(), ::tolower );
					}
					else if( written.size() < 3 )
					{
						written += event.text.unicode;
					}
					
					setWritten();
				}
			}
			
			if( event.type == sf::Event::KeyPressed )
			{
				if( event.key.code == sf::Keyboard::BackSpace )
				{
					if( !written.empty() )
					{
						written.pop_back();
					}
					
					setWritten();
				}
				else if( event.key.code == sf::Keyboard::Return )
				{
					textEntered();
				}
			}
		}
	
		if( event.type == sf::Event::KeyPressed )
		{
			if( event.key.code == sf::Keyboard::Escape )
			{
				if( active == 2 )	active --;
				else				clear();
			}
		}
	}
}

void LightPointVisible::draw( sf::RenderWindow* &window, float add_x, float add_y )
{
	// printf( "%d\n", chosen );
	
	if( active > 0 )
	{
		window->draw( table.get() );
		window->draw( rectColor );
		
		for( unsigned i = 0; i < ARROW; i++ )
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
			
			if( points.empty() )
			{
				minusbutton.setOffset( 2 );
				deletebutton.setOffset( 2 );
			}
			
			window->draw( minusbutton.get() );
			window->draw( deletebutton.get() );
		}
		else				texts_value[ LINES ]->setColor( sf::Color( 0xDD, 0xDD, 0xDD ) );
		
		if( !points.empty() )
		{
			if( points.size() > 1 )
			{
				vertex.resize( 0 );
				for( unsigned i = 0; i < points.size() -1; i++ )
				{
					vertex.resize( vertex.getVertexCount() +1 );
					vertex[ vertex.getVertexCount() -1 ] = sf::Vector2f( points[ i ].x +add_x, points[ i ].y +add_y );
					
					vertex.resize( vertex.getVertexCount() +1 );
					vertex[ vertex.getVertexCount() -1 ] = sf::Vector2f( points[ i+1 ].x +add_x, points[ i+1 ].y +add_y );
				}
				
				window->draw( vertex );
			}
			
			float r = 12;
			circle.setRadius( r /2 );
			for( unsigned i = 1; i < points.size(); i++ )
			{
				circle.setPosition( sf::Vector2f( points[ i ].x -r/2 +add_x, points[ i ].y -r/2 +add_y ) );
				window->draw( circle );
			}
			
			circle.setRadius( r );
			circle.setPosition( sf::Vector2f( points[ 0 ].x -r +add_x, points[ 0 ].y -r +add_y ) );
			window->draw( circle );
		}
		
		if( chosen > -1 )
		{
			if( arrow_counter > arrow_line )
			{
				// printf( "%f\n", arrow_counter );
				window->draw( texts[ ARROW ]->get() );
			}
			
			if( arrow_counter > arrow_line *2 )
			{
				arrow_counter = 0;
			}
		}
		
		// printf( "%d\n", points.size() );
	}
}

void LightPointVisible::mechanics( double elapsedTime )
{
	if( chosen > -1 )
	{
		arrow_counter += elapsedTime;
	}
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
	
	float myX = table.getX() +5;
	texts[ COLOR ]->setPosition( myX, table.getY() +5 );
	texts[ RADIUS ]->setPosition( myX, texts[ COLOR ]->getBot() +5 );
	texts[ VEL ]->setPosition( myX, texts[ RADIUS ]->getBot() +5 );
	
	texts_value[ COLOR_VALUE ]->setPosition( texts[ COLOR ]->getRight(), texts[ COLOR ]->getY() );
	texts_value[ RADIUS_VALUE ]->setPosition( texts[ COLOR ]->getRight(), texts[ RADIUS ]->getY() );
	texts_value[ VEL_VALUE ]->setPosition( texts[ COLOR ]->getRight(), texts[ VEL ]->getY() );
	texts_value[ LINES ]->setPosition( myX, texts[ VEL ]->getBot() +5 );
	
	rectColor.setPosition( sf::Vector2f( texts[ COLOR_VALUE ]->getRight() +75, texts[ COLOR_VALUE ]->getY() +3 ) );
	texts[ RADIUS_UNIT ]->setPosition( table.getRight() -5 -texts[ RADIUS_UNIT ]->getWidth(), texts[ RADIUS ]->getY() );
	texts[ VEL_UNIT ]->setPosition( table.getRight() -5 -texts[ VEL_UNIT ]->getWidth(), texts[ VEL ]->getY() );
	
	// Set that two buttons.
	deletebutton.setPosition( table.getRight() +deletebutton.getWidth(), texts_value[ LINES ]->getY() +2 );
	minusbutton.setPosition( table.getRight() +minusbutton.getWidth() *2, texts_value[ LINES ]->getY() +2 );
}

void LightPointVisible::setSpecs( float radius, float velocity, sf::Color color, vector <sf::Vector2f> points )
{
	this->radius = radius;
	this->velocity = velocity;
	this->color = color;
	this->points = points;
	
	valueStrs[ COLOR_VALUE ] = getTextFromColor( color );
	valueStrs[ RADIUS_VALUE ] = con::itos( radius );
	valueStrs[ VEL_VALUE ] = con::itos( velocity );
	
	texts_value[ COLOR_VALUE ]->setText( valueStrs[ COLOR_VALUE ] );
	texts_value[ RADIUS_VALUE ]->setText( valueStrs[ RADIUS_VALUE ] );
	texts_value[ VEL_VALUE ]->setText( valueStrs[ VEL_VALUE ] );
	
	texts_value[ COLOR_VALUE ]->setPosition( texts[ COLOR ]->getRight(), texts[ COLOR ]->getY() );
	texts_value[ RADIUS_VALUE ]->setPosition( texts[ COLOR ]->getRight(), texts[ RADIUS ]->getY() );
	texts_value[ VEL_VALUE ]->setPosition( texts[ COLOR ]->getRight(), texts[ VEL ]->getY() );
	
	rectColor.setFillColor( color );
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
	chosen = -1;
}

void LightPointVisible::resetType()
{
	type = -1;
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
	std::stringstream().swap( stream );
    stream << green;
    stream >> std::hex >> g;
	
	// Set blue.
	std::stringstream().swap( stream );
    stream << blue;
    stream >> std::hex >> b;
	
	// printf( "%s %s %s\n", red.c_str(), green.c_str(), blue.c_str() );
	// printf( "%d %d %d\n", r, g, b );
	
	return sf::Color( r, g, b, 0xFF );
}

string LightPointVisible::getTextFromColor( sf::Color color )
{
	string r, g, b;
	int red = color.r, green = color.g, blue = color.b;
	
    std::stringstream stream;
	
	// Set red.
    stream << std::hex << red;
    stream >> r;
	
	// Set green.
	std::stringstream().swap( stream );
    stream << std::hex << green;
    stream >> g;
	
	// Set blue.
	std::stringstream().swap( stream );
    stream << std::hex << blue;
    stream >> b;
	
	if( r.size() == 1 )	r = "0" +r;
	if( g.size() == 1 )	g = "0" +g;
	if( b.size() == 1 )	b = "0" +b;
	
	return r +g +b;
}

bool LightPointVisible::isPossibleCharColor( sf::Uint8 code )
{
	if( code >= '0' && code <= '9' )	// 0 ... 9.
	{
		return true;
	}
	else if( code >= 'A' && code <= 'F' )	// A ... F.
	{
		return true;
	}
	else if( code >= 'a' && code <= 'f' )	// a ... f.
	{
		return true;
	}
	
	return false;
}

bool LightPointVisible::isPossibleChar( sf::Uint8 code )
{
	if( code >= '0' && code <= '9' )	// 0 ... 9.
	{
		return true;
	}
	
	return false;
}

void LightPointVisible::setWritten()
{
	texts_value[ chosen ]->setText( written );
	texts_value[ chosen ]->setPosition( texts[ COLOR ]->getRight(), texts[ chosen ]->getY() );
	texts[ ARROW ]->setPosition( texts_value[ chosen ]->getRight(), texts_value[ chosen ]->getY() );
}

void LightPointVisible::textEntered()
{
	if( written.empty() )
	{
		written = valueStrs[ chosen ];
		// printf( "happened\n" );
	}
	else
	{
		if( chosen == COLOR_VALUE )
		{
			if( written.size() < 6 )
			{
				written = valueStrs[ chosen ];
			}
		}
		else
		{
			int newChosen = chosen -1;
			if( con::stoi( written ) < mins[ newChosen ] )	written = con::itos( mins[ newChosen ] );
			else if( con::stoi( written ) > maxs[ newChosen ] )	written = con::itos( maxs[ newChosen ] );
			// printf( "%d\n", mins[ newChosen ] );
		}
	}
	
	setWritten();
	
	valueStrs[ chosen ] = written;
	
	if( chosen == COLOR_VALUE )
	{
		color = getColorFromText( written );
		rectColor.setFillColor( sf::Color( color.r, color.g, color.b, 0xFF ) );
	}
	else if( chosen == RADIUS_VALUE )
	{
		radius = con::stoi( written );
	}
	else if( chosen == VEL_VALUE )
	{
		velocity = con::stoi( written );
	}
}