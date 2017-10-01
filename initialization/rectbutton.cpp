#include "rectbutton.h"


Rectbutton::Rectbutton()
{
	text_one = NULL;
	text_two = NULL;
	free();
}

Rectbutton::~Rectbutton()
{
	free();
}

void Rectbutton::free()
{
	alpha = 0;
	alphaBorders = 0;
	
	focus = false;
	clicked = false;
	state = 0;
	
	if( text_one != NULL )
	{
		text_one->free();
		delete text_one;
		text_one = NULL;
	}
	
	if( text_two != NULL )
	{
		text_two->free();
		delete text_two;
		text_two = NULL;
	}
	
	if( !rects.empty() )
	{
		for( auto &it :rects )
		{
			delete it;
		}
		
		rects.clear();
	}
}

void Rectbutton::setIdentity( string identity )
{
	text_one = new MyText();
	text_two = new MyText();
	text_one->setIdentity( identity );
	text_two->setIdentity( identity );
}

const string& Rectbutton::getIdentity() const
{
	return text_one->getIdentity();
}



void Rectbutton::setFont( string path )
{
	text_one->setFont( path );
	text_two->setFont( path );
}
/*
void Rectbutton::setFontByFont( sf::Font* &font )
{
	text_one->setFontByFont( font );
	text_two->setFontByFont( font );
}

sf::Font* &Rectbutton::getFont()
{
	return text_one->getFont();
}
*/


void Rectbutton::create( string line, int size, int ply )
{
	// 1. Create text.
	text_one->setText( line );
	text_two->setText( line );
	text_one->setSize( size );
	text_two->setSize( size );
	
	// 2. Set lines.
	float w = text_one->getWidth() +text_one->getWidth()/5;
	float h = text_one->getHeight() *2 +text_one->getHeight()/5;
	
	try
	{
		if( w < 1 || h < 1 || ply < 1 )
		{
			throw "Dimension is less than 1";
		}
	}
	catch( string msg )
	{
		cerr << msg << endl;
	}
	
	for( unsigned i = 0; i < 5; i++ )
	{
		rects.push_back( new sf::RectangleShape );
	}
	
	rects[ 0 ]->setSize( sf::Vector2f( w +ply*2, ply ) );
	rects[ 1 ]->setSize( sf::Vector2f( ply, h ) );
	rects[ 2 ]->setSize( sf::Vector2f( w +ply*2, ply ) );
	rects[ 3 ]->setSize( sf::Vector2f( ply, h ) );
	rects[ 4 ]->setSize( sf::Vector2f( w, h ) );
	
	setPosition( 0, 0 );
	sf::Color newColor( rects[ rects.size() -1 ]->getFillColor() );
	newColor.a = 0;
	for( auto &it :rects )
	{
		it->setFillColor( newColor );
	}
}

void Rectbutton::handle( sf::Event& event )
{
	if( state == 1 )
	{
		if( event.type == sf::Event::MouseMoved )
		{
			if( checkCollision( event.mouseMove.x, event.mouseMove.y ) )
			{	
				focus = true;
			}
			else
			{
				focus = false;
			}
		}
		else if( event.type == sf::Event::MouseButtonPressed )
		{
			if( event.mouseButton.button == sf::Mouse::Left )
			{
				if( checkCollision( event.mouseButton.x, event.mouseButton.y ) )
				{	
					// printf( "%f %f\n", alpha, alphaBorders );
					if( alpha > 0xFF /2 && alphaBorders > 0xFF /2 )
					{
						focus = true;
						clicked = true;
					}
				}
			}
		}
		else if( event.type == sf::Event::MouseButtonReleased )
		{
			focus = false;
		}
	}
}

void Rectbutton::draw( sf::RenderWindow* &window )
{
	// Background.
	window->draw( text_two->get() );
	
	// Frame.
	for( auto &it :rects )
	{
		window->draw( *it );
	}
	
	// Front.
	window->draw( text_one->get() );
}

void Rectbutton::mechanics( double elapsedTime )
{
	if( state == 1 )
	{
		float value = elapsedTime *0xFF *6;
		
		if( focus )
		{
			fadein( value );
			text_one->fadein( value );
			text_two->fadeout( value );
		}
		else
		{
			fadeout( value );
			text_one->fadeout( value );
			text_two->fadein( value );
		}
	}
}




void Rectbutton::fadein( float v, int max )
{
	if( alpha < max )
	{
		alpha += v;
		
		if( alpha > max )
		{
			alpha = max;
		}
		
		sf::Color newColor( rects[ rects.size() -1 ]->getFillColor() );
		newColor.a = alpha;
		rects[ rects.size() -1 ]->setFillColor( newColor );
	}
}

void Rectbutton::fadeinBorders( float v, int max )
{
	if( alphaBorders < max )
	{
		alphaBorders += v;
		
		if( alphaBorders > max )
		{
			alphaBorders = max;
		}
		
		sf::Color newColor( rects[ 0 ]->getFillColor() );
		newColor.a = alphaBorders;
		for( unsigned i = 0; i < rects.size() -1; i++ )
		{
			rects[ i ]->setFillColor( newColor );
		}
	}
}

void Rectbutton::fadeinGlobal( float v, int max )
{
	if( state == 0 )
	{
		fadeinBorders( v );
		text_two->fadein( v );
		if( alphaBorders == max )
		{
			state = 1;
		}
	}
}

void Rectbutton::fadeout( float v, int min )
{
	if( alpha > min )
	{
		alpha -= v;
		
		if( alpha < min )
		{
			alpha = min;
		}
		
		sf::Color newColor( rects[ rects.size() -1 ]->getFillColor() );
		newColor.a = alpha;
		rects[ rects.size() -1 ]->setFillColor( newColor );
	}
}

void Rectbutton::fadeoutBorders( float v, int min )
{
	if( alphaBorders > min )
	{
		alphaBorders -= v;
		
		if( alphaBorders < min )
		{
			alphaBorders = min;
		}
		
		sf::Color newColor( rects[ 0 ]->getFillColor() );
		newColor.a = alphaBorders;
		for( unsigned i = 0; i < rects.size() -1; i++ )
		{
			rects[ i ]->setFillColor( newColor );
		}
	}
}

void Rectbutton::fadeoutGlobal( float v, int min )
{
	if( state == 1 )
	{
		fadeout( v );
		fadeoutBorders( v );
		text_one->fadeout( v );
		text_two->fadeout( v );
		if( alphaBorders == min )
		{
			state = 2;
		}
	}
}




void Rectbutton::move( float x, float y )
{
	text_one->move( x, y );
	text_two->move( x, y );
	for( auto &it :rects )
	{
		it->move( x, y );
	}
}

void Rectbutton::setPosition( float x, float y )
{
	rects[ 0 ]->setPosition( x, y );
	rects[ 1 ]->setPosition( x +rects[ 0 ]->getSize().x -rects[ 0 ]->getSize().y, y +rects[ 0 ]->getSize().y );
	rects[ 2 ]->setPosition( x, y +rects[ 0 ]->getSize().y +rects[ 3 ]->getSize().y );
	rects[ 3 ]->setPosition( x, y +rects[ 0 ]->getSize().y );
	rects[ 4 ]->setPosition( x +rects[ 0 ]->getSize().y, y +rects[ 0 ]->getSize().y );
	text_one->center( rects[ 4 ]->getPosition().x, rects[ 4 ]->getPosition().y, rects[ 4 ]->getSize().x, rects[ 4 ]->getSize().y /1.5 );
	text_two->center( rects[ 4 ]->getPosition().x, rects[ 4 ]->getPosition().y, rects[ 4 ]->getSize().x, rects[ 4 ]->getSize().y /1.5 );
}

void Rectbutton::center( float x, float y, int w, int h )
{
	// Two times x.
	setPosition( x +w/2 -rects[ 0 ]->getSize().x/2, y +h/2 -rects[ 0 ]->getSize().x/2 );
}

void Rectbutton::setColor( sf::Color color )
{
	sf::Color newColor( rects[ 0 ]->getFillColor() );
	newColor.r = color.r;
	newColor.g = color.g;
	newColor.b = color.b;
	for( unsigned i = 0; i < rects.size() -1; i++ )
	{
		rects[ i ]->setFillColor( newColor );
	}
	text_two->setColor( newColor );
	
	newColor.a = rects[ rects.size() -1 ]->getFillColor().a;
	newColor.r = color.r;
	newColor.g = color.g;
	newColor.b = color.b;
	rects[ rects.size() -1 ]->setFillColor( newColor );
}

void Rectbutton::setColorText( sf::Color color )
{
	text_one->setColor( color );
}

void Rectbutton::setAlpha( float alpha )
{
	if( this->alpha != alpha )
	{
		this->alpha = alpha;
		sf::Color newColor( rects[ rects.size() -1 ]->getFillColor() );
		newColor.a = alpha;
		rects[ rects.size() -1 ]->setFillColor( newColor );
	}
}

void Rectbutton::setAlphaBorders( float alpha )
{
	if( this->alphaBorders != alpha )
	{
		this->alphaBorders = alpha;
		sf::Color newColor( rects[ 0 ]->getFillColor() );
		newColor.a = this->alphaBorders;
		for( unsigned i = 0; i < rects.size() -1; i++ )
		{
			rects[ i ]->setFillColor( newColor );
		}
	}
}




float Rectbutton::getAlpha()
{
	return alpha;
}

float Rectbutton::getAlphaBorders()
{
	return alphaBorders;
}

sf::Uint8& Rectbutton::getState()
{
	return state;
}

bool& Rectbutton::getFocus()
{
	return focus;
}

bool& Rectbutton::getClicked()
{
	return clicked;
}




const float& Rectbutton::getX() const
{
	return rects[ 0 ]->getPosition().x;
}

const float& Rectbutton::getY() const
{
	return rects[ 0 ]->getPosition().y;
}

const float Rectbutton::getWidth() const
{
	return rects[ 0 ]->getSize().x;
}

const float Rectbutton::getHeight() const
{
	return rects[ 0 ]->getSize().y *2 +rects[ rects.size() -1 ]->getSize().y;
}

const float& Rectbutton::getLeft() const
{
	return rects[ 0 ]->getPosition().x;
}

const float Rectbutton::getRight() const
{
	return rects[ 0 ]->getPosition().x +rects[ 0 ]->getSize().x;
}

const float& Rectbutton::getTop() const
{
	return rects[ 0 ]->getPosition().y;
}

const float Rectbutton::getBot() const
{
	return rects[ 0 ]->getPosition().y +rects[ rects.size() -1 ]->getSize().y +(rects[ 0 ]->getSize().y *2);
}




bool Rectbutton::checkCollision( float x, float y, float w, float h )
{
	if( y + h <= getTop() )
        return false;

    if( y >= getBot() )
        return false;

    if( x + w <= getLeft() )
        return false;

    if( x >= getRight() )
        return false;

    return true;
}